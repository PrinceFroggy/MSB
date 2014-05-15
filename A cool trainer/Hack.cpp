#include "Hack.h"
#include "Macro.h"
#include "Packet.h"

#pragma region MapleStory memory

static const DWORD msCHATLOG_ADD = 0x00491C90;
static const DWORD msSetData = 0x00502000;

static const DWORD msFMA = 0x007D6F19;

static const DWORD msGodmode = 0x007D64FC;

static const DWORD msSilence1 = 0x007CC225;
static const DWORD msSilence2 = 0x007CC24E;
static const DWORD msSilence3 = 0x007CC273;
static const DWORD msSilence4 = 0x007CC2A4;
static const DWORD msSilence5 = 0x007A83E2;
static const DWORD msSilence6 = 0x007D1971;
static const DWORD msSilence7 = 0x007CCB21;

static const DWORD msFusionAttack = 0x007D6F19;
static const DWORD msFusionAttackReturn1 = 0x007D6F1D;
static const DWORD msFusionAttackReturn2 = 0x007D6F33;

DWORD *const pdwItemFilterPointer = reinterpret_cast<DWORD *const>(0x12ED8A4);
const DWORD dwOriginal = 0x00970620;
const DWORD dwThing1 = 0x0040AFC0;
const DWORD dwThing2 = 0x0040B060;
const DWORD dwReturn = 0x005B883E;

DWORD *const pdwVariantInitPointer = reinterpret_cast<DWORD *const>(0x01010304);
const DWORD dwVariantInit = reinterpret_cast<DWORD>(GetProcAddress(LoadLibrary(TEXT("OLEAUT32.dll")), TEXT("VariantInit")));
const DWORD dwCall1 = reinterpret_cast<DWORD>(GetProcAddress(GetModuleHandle(NULL), TEXT("ZtlTaskMemFreeImp")));
const DWORD dwCall2 = reinterpret_cast<DWORD>(GetProcAddress(LoadLibrary(TEXT("OLEAUT32.dll")), TEXT("VariantClear")));
const DWORD dwReturn1 = 0x00779ECE;
const DWORD dwReturn2 = 0x00779EDA;

static const DWORD alertBase = 0x013017C4;
static const WORD alertHealth = 0x50;
static const WORD alertMana = 0x54;

static const DWORD serverBase = 0x012FCF80;
static const DWORD serverChannel = 0x20AC;

static const DWORD peopleBase = 0x013017C8;
static const WORD peopleDot = 0x18;

static const DWORD characterBase = 0x012FCF84;
static const DWORD characterX = 0x9074;
static const DWORD characterY = 0x9078;

static const DWORD teleportToggle = 0x7E6C;
static const DWORD teleportX = 0x7E90;
static const DWORD teleportY = 0x7E84;

static const DWORD guiBase = 0x013018A0;
static const DWORD guiHealth = 0x2200;
static const DWORD guiMana = 0x2204;

static const DWORD wallBase = 0x01301738;
static const WORD leftWall = 0x1C;
static const WORD topWall = 0x20; 
static const WORD rightWall = 0x24;
static const WORD bottomWall = 0x28;

static const DWORD monsterBase = 0x013017CC;
static const WORD monsterCount = 0x10;
static const WORD monster1 = 0x28;
static const BYTE monster2 = 0x4;
static const DWORD monster3 = 0x170;
static const WORD monster4 = 0x24;
static const WORD monsterX = 0x58;
static const WORD monsterY = 0x5C;
static const WORD monsterDeath = 0x568;

#pragma endregion

#pragma region Windows and Detour functions

BOOL SetHook ( __in BOOL bState, __inout PVOID* ppPointer, __in PVOID pDetour )
{
	if ( ! DetourTransactionBegin()
	  && ! DetourUpdateThread(GetCurrentThread())
	  && ! (bState ? DetourAttach : DetourDetach)(ppPointer, pDetour)
	  && ! DetourTransactionCommit() )
		return TRUE;

	return FALSE;
}

DWORD ReadPointer(DWORD dwBase, DWORD dwOffset)
{
	__try
	{
		return *(PDWORD)(*(PDWORD)dwBase + dwOffset);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return 0;
	}
}

bool WritePointer(DWORD dwBase, DWORD dwOffset, DWORD dwValue)
{
	__try
	{
		*(PDWORD)(*(PDWORD)dwBase + dwOffset) = dwValue;
		return true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}
}

DWORD GetValue(DWORD dwBase, DWORD dwOffset)
{
	__try
	{
		return *(PDWORD)(dwBase + dwOffset);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return 0;
	}
}

#pragma endregion

#pragma region Structure

template <typename T>
struct ZXString
{
	T* _m_pStr;
};

#pragma endregion

#pragma region API

typedef void (__cdecl* CHATLOG_ADD_t)(ZXString<char> *sString, unsigned short nType);
CHATLOG_ADD_t CHATLOG_ADD = reinterpret_cast<CHATLOG_ADD_t>(msCHATLOG_ADD);

typedef BOOL ( WINAPI* LPFNINTERSECTRECT )( LPRECT, const RECT*, const RECT* );
LPFNINTERSECTRECT _fnIntersectRect;

typedef void (__fastcall* TSecType_long___SetData_t)(void* lpvEcx, void* lpvEdx, const int data);
TSecType_long___SetData_t _TSecType_long___SetData = reinterpret_cast<TSecType_long___SetData_t>(msSetData);

#pragma endregion

#pragma region Variables

std::vector<DWORD> vReturnAddresses;

bool bGodmodeEnabled = false;
bool bFMAEnabled = false;
bool bFusionAttackEnabled = false;
bool bHookedIntersectRect = false;
bool kamiSwitch = false;

std::vector<DWORD> vBlacklist(1, 0);

#pragma endregion

#pragma region Pointer Functions

int UpdateHealth()
{
	return (int)ReadPointer(guiBase, guiHealth);
}

int UpdateMana()
{
	return (int)ReadPointer(guiBase, guiMana);
}

bool UpdatePeople()
{
	return (int)ReadPointer(peopleBase, peopleDot) > 0;
}

int GetChannel()
{
	return (int)ReadPointer(serverBase, serverChannel);
}

bool leftWallLocation(int X)
{
    return ((int)ReadPointer(wallBase, leftWall) <= X);
}

bool topWallLocation(int Y)
{
    return ((int)ReadPointer(wallBase, topWall) <= Y);
}

bool rightWallLocation(int X)
{
    return ((int)ReadPointer(wallBase, rightWall) >= X);
}

bool bottomWallLocation(int Y)
{
    return ((int)ReadPointer(wallBase, bottomWall) >= Y);
}

int GetCharacterX()
{
	return (int)ReadPointer(characterBase, characterX); 
}

int GetCharacterY()
{
	return (int)ReadPointer(characterBase, characterY);
}

int GetMonsterX(DWORD dwMonster)
{
	return (int)ReadPointer(monsterBase, monsterX);
}

int GetMonsterY(DWORD dwMonster)
{
	return (int)ReadPointer(monsterBase, monsterY);
}

int GetMonsterCount()
{
	return (int)ReadPointer(monsterBase, monsterCount);
}

POINT GetMonsterLocation()
{
	POINT MobLoc;

	for(int iMonsterIndex = ReadPointer(monsterBase, monsterCount); iMonsterIndex > -1; --iMonsterIndex)
	{
		DWORD dwMobStruct = ReadPointer(monsterBase, monster1);
		if(iMonsterIndex > 0)
		{
			dwMobStruct = GetValue(dwMobStruct, -12);
			for (int i = 0; i < iMonsterIndex; ++i)
			{
				dwMobStruct = GetValue(dwMobStruct, 4);
			}
			dwMobStruct = GetValue(dwMobStruct, 0x14);
		}
		else { dwMobStruct = GetValue(dwMobStruct,monster2); }

		if(GetValue(dwMobStruct, monsterDeath))
		{
			dwMobStruct = GetValue(GetValue(dwMobStruct, monster3), monster4);
			int x = GetValue(dwMobStruct, monsterX);
			int y = GetValue(dwMobStruct, monsterY);

			if(x != 0 && y !=0)
			{
				MobLoc.x = x;	
				MobLoc.y = y;
				return MobLoc;
			}
		}
	}
	return MobLoc;
}

#pragma endregion

#pragma region Hacks and Threads

__declspec(naked) void FusionAttack()
{
	__asm
	{
		test eax, eax
		je Return1
		mov eax, dword ptr [esp+0x18]
		mov ecx, dword ptr [esp+0x60]
Thing:
		mov dword ptr [ecx+eax*4], ebp
		inc eax
		cmp eax, dword ptr [esp+0x64]
		jl Thing
		jmp dword ptr [msFusionAttackReturn2]
Return1:
		jmp dword ptr [msFusionAttackReturn1]
	}
}

__declspec(noinline) BOOL WINAPI IntersectRect_Hook(_Out_ PRECT prcDst, _In_ const RECT *prcSrc1, _In_ const RECT *prcSrc2)
{
	DWORD dwRetAddress;

	__asm
	{
		push eax
		mov eax, dword ptr [ebp+4]
		mov dword ptr [dwRetAddress], eax
		pop eax
	}

	if (bGodmodeEnabled && (dwRetAddress == msGodmode || dwRetAddress == msSilence1 || dwRetAddress == msSilence2 || dwRetAddress == msSilence3 || dwRetAddress == msSilence4 || dwRetAddress == msSilence5 || dwRetAddress == msSilence6 || dwRetAddress == msSilence7))
	{
		return FALSE;
	}
	else if (bFMAEnabled && dwRetAddress == msFMA)
	{
		return TRUE;
	}
	else if (bFusionAttackEnabled && dwRetAddress == msFusionAttack)
	{
		__asm
		{
			mov dword ptr [ebp+4], offset FusionAttack
		}
	}
	return _fnIntersectRect(prcDst, prcSrc1, prcSrc2);
}

BOOL HookIntersectRect(__in BOOL bState)
{
	bHookedIntersectRect = true;
	if (bState)
	{
		_fnIntersectRect = reinterpret_cast<LPFNINTERSECTRECT>(GetProcAddress(GetModuleHandle(TEXT("user32.dll")), TEXT("IntersectRect")));
	}
	return SetHook(bState, (PVOID *)&_fnIntersectRect, &IntersectRect_Hook);
}

__declspec(naked) void ItemFilter()
{
	__asm
	{
		cmp dword ptr [esp+0x58], 0x005B8809
		jne Return
		mov dword ptr [esp+0x58], offset PreItemFilter
Return:
		jmp dword ptr [dwOriginal]
PreItemFilter:
		mov eax, dword ptr [esp+0x64]
		mov esi, dword ptr [esp+0x70]
		mov byte ptr [esi+0x1C], al
		cmp eax, 1
		je JMP1
		cmp eax, 2
		je JMP1
		xor al, al
		jmp JMP2
JMP1:
		mov al, 1
JMP2:
		mov byte ptr [esi+0x1D], al
		mov ecx, ebx
		mov dword ptr [esi+0x20], edi
		call dword ptr [dwThing1]
		movzx ecx, al
		mov ecx, ebx
		mov dword ptr [esi+0x30], eax
		call dword ptr [dwThing2]
		mov ecx, dword ptr [vBlacklist]
ItemFilterLoop:
		cmp dword ptr [ecx], 0
		je Return2
		cmp eax, dword ptr [ecx]
		je Filter
		add ecx, 4
		jmp ItemFilterLoop
Filter:
		xor eax, eax
Return2:
		jmp dword ptr [dwReturn]
	}
}

__declspec(naked) void VariantInitHook()
{
	__asm
	{
		cmp dword ptr [esp+0x2C], 0x00779E6B
		jne Return
		mov dword ptr [esp+0x2C], offset Callback
Return:
		jmp dword ptr [dwVariantInit]
Callback:
		add esp, 0x08
		cmp word ptr [ebp-0x5C], 0x08
		mov ebx, eax
		mov byte ptr [ebp-0x04], 0x07
		jne offset JMP1
		xor eax, eax
		mov word ptr [ebp-0x5C], ax
		mov eax, dword ptr [ebp-0x54]
		test eax, eax
		je offset JMP2
		add eax, 0xFC
		push eax
		call dword ptr [dwCall1]
		jmp offset JMP2
JMP1:
		lea ecx, dword ptr [ebp-0x5C]
		push ecx
		call dword ptr [dwCall2]
JMP2:
		cmp ebx, 0x01
		jne offset JMP4
		cmp byte ptr [ebp-0x11], 0x00
		jne offset JMP5
JMP3:
		push 0x00
		push 0x00
		push 0x00
		push 0x00
		push 0x00
		push 0xFF
		push ecx
		mov eax, esp
		mov dword ptr [eax], esi
		mov ecx, dword ptr [esi]
		mov edx, dword ptr [ecx+0x04]
		mov dword ptr [ebp-0x24], esp
		push esi
		call edx
		mov ecx, dword ptr [ebp-0x28]
		jmp dword ptr [dwReturn1]
JMP4:
		cmp ebx, 0x02
		jne offset JMP3
		cmp byte ptr [ebp-0x11], 0x00
		jne offset JMP3
JMP5:
		mov edx, dword ptr [esi]
		mov eax, dword ptr [edx+0x08]
		push esi
		mov byte ptr [ebp-0x04], 0x03
		call eax
		jmp dword ptr [dwReturn2]
	}
}

static const DWORD dwGetTickCount = reinterpret_cast<DWORD>(GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), TEXT("GetTickCount")));
static const DWORD dwGND = 0x01010114;
static const DWORD dwJMP3 = 0x00D0EFBD;
static const DWORD dwGNDCall1 = 0x00492C00;
static const DWORD dwJMP1 = 0x00D1B725;
static const DWORD dwGNDCall2 = 0x00CD2A40;
static const DWORD dwCall3 = 0x0045B480;
static const DWORD dwCall4 = 0x005DEFD0;
static const DWORD dwCall5 = 0x00CC2A20;
static const DWORD dwCall6 = 0x008B0000;
static const DWORD dwCall7 = 0x008AD310;
static const DWORD dwCall8 = 0x00406E90;
static const DWORD dwCall9 = 0x008B6460;
static const DWORD dwCall10 = 0x00406E90;
static const DWORD dwCall11 = 0x008B6460;
static const DWORD dwCall12 = 0x00431FF0;
static const DWORD dwCall13 = 0x00433DD0;
static const DWORD dwCall14 = 0x00432000;
static const DWORD dwCall15 = 0x00433A20;
static const DWORD dwCall16 = 0x00503600;
static const DWORD dwCall17 = 0x00975630;
static const DWORD dwCall18 = 0x004318C0;
static const DWORD dwCall19 = 0x00491C90;
static const DWORD dwCall20 = 0x004181D0;
static const DWORD dwCall21 = 0x0067F750;
static const DWORD dwCall22 = 0x0067F350;
static const DWORD dwCall23 = 0x0067F360;
static const DWORD dwCall24 = 0x0067F330;
static const DWORD dwCall25 = 0x0067F360;
static const DWORD dwCall26 = 0x0067F320;
static const DWORD dwCall27 = 0x0067F360;
static const DWORD dwCall28 = 0x0067F6F0;
static const DWORD dwCall29 = 0x0067F340;
static const DWORD dwCall30 = 0x0067F680;
static const DWORD dwCall31 = 0x004BD360;
static const DWORD dwCall32 = 0x005AB2E0;
static const DWORD dwCall33 = 0x004A8E40;
static const DWORD dwCall34 = 0x00492750;
static const DWORD dwCall35 = 0x008AF220;
static const DWORD dwCall36 = 0x00914F30;
static const DWORD dwJMP2 = 0x00D0EFB1;

__declspec(naked) void GetTickCountHook()
{
	__asm
	{
			cmp dword ptr [esp], 0x00D0EC25
			jne Return
			mov dword ptr [esp], offset Callback
Return:
			jmp dword ptr [dwGetTickCount]
Callback:
			mov ecx, dword ptr [ebp-0x00003038]
			mov dword ptr [ecx+0x00009068], eax
			mov ecx, dword ptr [ebp-0x00003038]
			add ecx, 0x90
			call dword ptr [dwGNDCall1]
			test eax, eax
			je JMP1
			xor eax, eax
			jmp dword ptr [dwJMP1]
JMP1:
			cmp dword ptr [ebp+0x08], 0
			je JMP2
			mov edx, dword ptr [ebp+0x08]
			mov eax, dword ptr [edx]
			mov dword ptr [ebp-0x0000303C], eax
			jmp JMP3
JMP2:
			mov dword ptr [ebp-0x0000303C], 0
JMP3:
			mov ecx, dword ptr [ebp-0x0000303C]
			mov dword ptr [ebp-0x000001D0], ecx
			mov edx, dword ptr [ebp-0x000001D0]
			push edx
			mov ecx, dword ptr [ebp-0x00003038]
			call dword ptr [dwGNDCall2]
			test eax, eax
			jne JMP4
			xor eax, eax
			jmp dword ptr [dwJMP1]
JMP4:
			call dword ptr [dwCall3]
			mov ecx, eax
			call dword ptr [dwCall4]
			test eax, eax
			jne JMP5
			mov ecx, dword ptr [ebp-0x00003038]
			call dword ptr [dwCall5]
			movzx eax, al
			test eax, eax
			je JMP6
JMP5:
			mov ecx, dword ptr [ebp-0x000001D0]
			push ecx
			call dword ptr [dwCall6]
			add esp, 04
			test eax, eax
			je JMP6
			xor eax, eax
			jmp dword ptr [dwJMP1]
JMP6:
			mov edx, dword ptr [ebp-0x000001D0]
			push edx
			call dword ptr [dwCall7]
			add esp, 4
			test eax, eax
			jne JMP7
			cmp dword ptr [ebp-0x000001D0], 0x0050DF27
			je JMP7
			cmp dword ptr [ebp-0x000001D0], 0x019DD253
			jne JMP8
JMP7:
			cmp dword ptr [ebp+0x20], 0
			jne JMP8
			xor eax, eax
			jmp dword ptr [dwJMP1]
JMP8:
			cmp dword ptr [ebp-0x000001D0], 0x0040684F
			jne JMP9
			mov eax, dword ptr [ebp-0x00003038]
			cmp dword ptr [eax+0x0000597C], 0
			je JMP9
			xor eax,eax
			jmp dword ptr [dwJMP1]
JMP9:
			push 0x000F462D
			call dword ptr [dwCall8]
			mov ecx, eax
			call dword ptr [dwCall9]
			mov dword ptr [ebp-0x14], eax
			push 0x00A7DCAB
			call dword ptr [dwCall10]
			mov ecx, eax
			call dword ptr [dwCall11]
			mov dword ptr [ebp-0x00000168], eax
			call dword ptr [dwCall12]
			mov dword ptr [ebp-0x30], eax
			lea ecx, dword ptr [ebp-0x00000F9C]
			push ecx
			mov ecx, dword ptr [ebp-0x30]
			call dword ptr [dwCall13]
			mov dword ptr [ebp-0x00003040], eax
			mov ecx, dword ptr [ebp-0x00003040]
			call dword ptr [dwCall14]
			mov dword ptr [ebp-0x60], eax
			lea ecx, dword ptr [ebp-0x00000F9C]
			call dword ptr [dwCall15]
			mov ecx, dword ptr [ebp-0x30]
			call dword ptr [dwCall16]
			test eax, eax
			je JMP10
			push 0x0000009D
			lea edx, dword ptr [ebp-0x00000FA0]
			push edx
			call dword ptr [dwCall17]
			mov ecx, eax
			call dword ptr [dwCall18]
			mov dword ptr [ebp-0x00003044], eax
			mov eax, dword ptr [ebp-0x00003044]
			mov dword ptr [ebp-0x00003048], eax
			mov dword ptr [ebp-0x04], 0
			push 0x0C
			mov ecx, dword ptr [ebp-0x00003048]
			push ecx
			call dword ptr [dwCall19]
			add esp, 8
			mov dword ptr [ebp-0x04], 0xFFFFFFFF
			lea ecx, dword ptr [ebp-0x00000FA0]
			call dword ptr [dwCall20]
			xor eax,eax
			jmp dword ptr [dwJMP1]
JMP10:
			lea edx, dword ptr [ebp-0x00000BD8]
			push edx
			mov ecx, dword ptr [ebp-0x00003038]
			call dword ptr [dwCall21]
			mov dword ptr [ebp-0x04], 1
			mov dword ptr [ebp-0x000001E8], 0
			lea ecx, dword ptr [ebp-0x00000BD8]
			call dword ptr [dwCall22]
			test eax,eax
			je JMP11
			lea ecx, dword ptr [ebp-0x00000BD8]
			call dword ptr [dwCall23]
			mov eax, dword ptr [eax+0x00000114]
			mov dword ptr [ebp-0x000001E8], eax
			lea ecx, dword ptr [ebp-0x00000BE0]
			call dword ptr [dwCall24]
			mov byte ptr [ebp-0x04], 2
			lea ecx, dword ptr [ebp-0x00000BD8]
			call dword ptr [dwCall25]
			add eax, 0x00000164
			mov ecx, eax
			call dword ptr [dwCall26]
			test eax, eax
			jne JMP12
			lea ecx, dword ptr [ebp-0x00000BE0]
			push ecx
			lea edx, dword ptr [ebp-0x000001D0]
			push edx
			lea ecx, dword ptr [ebp-0x00000BD8]
			call dword ptr [dwCall27]
			add eax, 0x00000164
			mov ecx, eax
			call dword ptr [dwCall28]
			test eax, eax
			je JMP12
			lea ecx, dword ptr [ebp-0x00000BE0]
			call dword ptr [dwCall29]
			mov ecx, dword ptr [ebp-0x000001E8]
			add ecx, dword ptr [eax+0x28]
			mov dword ptr [ebp-0x000001E8], ecx
JMP12:
			mov byte ptr [ebp-0x04], 1
			lea ecx, dword ptr [ebp-0x00000BE0]
			call dword ptr [dwCall30]
JMP11:
			mov edx, dword ptr [ebp-0x00003038]
			mov eax, dword ptr [edx]
			mov ecx, dword ptr [ebp-0x00003038]
			mov edx, dword ptr [eax+0x58]
			call edx
			push eax
			call dword ptr [dwCall31]
			add esp, 4
			test eax, eax
			je JMP13
			mov eax, dword ptr [ebp-0x000001D0]
			push eax
			mov ecx, dword ptr [ebp-0x60]
			call dword ptr [dwCall32]
			test eax, eax
			je JMP13
			mov dword ptr [ebp-0x0000304C], 1
			jmp JMP14
JMP13:
			mov dword ptr [ebp-0x0000304C], 0
JMP14:
			mov ecx, dword ptr [ebp-0x0000304C]
			mov [ebp-0x44], ecx
			cmp dword ptr [ebp+0x10], 0
			je JMP15
			mov edx, dword ptr [ebp+0x10]
			mov dword ptr [edx], 0x41
JMP15:
			mov eax, dword ptr [ebp-0x60]
			mov dword ptr [ebp-0x00000084], eax
			mov ecx, dword ptr [ebp-0x30]
			call dword ptr [dwCall33]
			mov dword ptr [ebp-0x00000BD0], eax
			mov ecx, dword ptr [ebp-0x30]
			call dword ptr [dwCall34]
			mov dword ptr [ebp-0x00000208], eax
			mov ecx, dword ptr [ebp-0x00000208]
			call dword ptr [dwCall35]
			neg eax
			sbb eax, eax
			neg eax
			mov dword ptr [ebp-0x000001E4], eax
			mov ecx, dword ptr [ebp-0x00000208]
			call dword ptr [dwCall36]
			test eax, eax
			je JMP16
			cmp dword ptr [ebp-0x000001D0], 0x00E6935E
			je JMP16
			mov dword ptr [ebp-0x00003050], 1
			jmp JMP17
JMP16:
			mov dword ptr [ebp-0x00003050], 0
JMP17:
			mov ecx, dword ptr [ebp-0x00003050]
			mov dword ptr [ebp-0x00000204], ecx
			cmp dword ptr [ebp-0x000001D0], 0
			je Other
			mov edx, dword ptr [ebp-0x00003038]
			mov eax, dword ptr [ebp-0x000001D0]
			cmp eax, dword ptr [edx+0x00007E04]
			je Other
			jmp dword ptr [dwJMP2]
Other:
			jmp dword ptr [dwJMP3]
	}
}

void Teleport(int X, int Y)
{
	if (leftWallLocation(X) && rightWallLocation(X) && topWallLocation(Y) && bottomWallLocation(Y))
	{
		void* base = *reinterpret_cast<void**>(characterBase);
		_TSecType_long___SetData(reinterpret_cast<unsigned char*>(base) + teleportX, NULL, X);
		_TSecType_long___SetData(reinterpret_cast<unsigned char*>(base) + teleportY, NULL, Y);
		_TSecType_long___SetData(reinterpret_cast<unsigned char*>(base) + teleportToggle, NULL, 1);
	}
}

void Kami()
{
	while (kamiSwitch)
	{
		if (GetMonsterCount() == 0)
		{
			continue;
		}

		POINT loc = GetMonsterLocation();

		int nDistanceX = loc.x - GetCharacterX();
		int nDistanceY = loc.y - GetCharacterY();

		if (nDistanceX < 0 || nDistanceX > 50 || nDistanceY < 0 || nDistanceY > 50)
		{
			Teleport(loc.x - 25, loc.y - 10);
		}

		Sleep(100);
	}
	return;
}

void ChangeChannel()
{
	byte iChannel;
	std::string strError;
	char buffer[26];

	do
	{
		iChannel = rand() % 10;
	} 
	while (iChannel == GetChannel());

	sprintf(buffer, "45 00 %02x ** ** ** **", iChannel);

	do
	{
		SendPacket((std::string)buffer, strError);
		Sleep(3000);
	} 
	while (GetChannel() != iChannel);

	MacroBlock(false);
}

#pragma endregion

#pragma region General Functions

void ToggleKami(bool bEnable)
{
	if (bEnable)
	{
		kamiSwitch = true;

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&Kami, NULL , 0, NULL );
	}
	else
	{
		kamiSwitch = false;
	}
}

void ToggleGodmode(bool bEnable)
{
	if (!bHookedIntersectRect)
	{
		HookIntersectRect(TRUE);
	}
	bGodmodeEnabled = bEnable;
}

void ToggleFusionAttack(bool bEnable)
{
	if (!bHookedIntersectRect)
	{
		HookIntersectRect(TRUE);
	}
	bFusionAttackEnabled = bEnable;
}

static const DWORD dwKiFastSystemCall = reinterpret_cast<DWORD>(GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), TEXT("KiFastSystemCall")));

bool IsWow64()
{
	static bool bAlready = false;
	typedef BOOL (WINAPI *pfnIsWow64Process)(HANDLE, PBOOL);
	static const pfnIsWow64Process fnIsWow64Process = reinterpret_cast<pfnIsWow64Process>(GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), TEXT("IsWow64Process")));
	static BOOL bIsX64 = FALSE;
	if (!bAlready)
	{
		bAlready = true;
		if (fnIsWow64Process != NULL)
		{
			fnIsWow64Process(GetCurrentProcess(), &bIsX64);
		}
	}
	return bIsX64;
}

__declspec(naked) NTSTATUS NTAPI NtProtectVirtualMemory(IN HANDLE hProcess, IN OUT PVOID pAddress, IN OUT DWORD *pdwNumberOfBytesToProtect, IN DWORD dwNewAccessProtection, OUT DWORD *pdwOldAccessProtection)
{
	__asm
	{
		mov eax, 0x000000D7
		call dword ptr [dwKiFastSystemCall]
		ret 0x0014
	}
}

bool ToggleGND(bool bEnable)
{
	DWORD dwOldProtect;
	DWORD dwNumberOfBytesToProtect = sizeof(DWORD);
	if (IsWow64())
	{
		if (VirtualProtect((PVOID)dwGND, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &dwOldProtect))
		{
			*reinterpret_cast<DWORD *>(dwGND) = bEnable ? (DWORD)GetTickCountHook : dwGetTickCount;
			VirtualProtect((PVOID)dwGND, sizeof(DWORD), dwOldProtect, &dwOldProtect);
			return true;
		}
	}
	else
	{
		if (NtProtectVirtualMemory(GetCurrentProcess(), (PVOID)dwGND, &dwNumberOfBytesToProtect, PAGE_EXECUTE_READWRITE, &dwOldProtect) == 0x00000000)
		{
			*reinterpret_cast<DWORD *>(dwGND) = bEnable ? (DWORD)GetTickCountHook : dwGetTickCount;
			NtProtectVirtualMemory(GetCurrentProcess(), (PVOID)dwGND, &dwNumberOfBytesToProtect, dwOldProtect, &dwOldProtect);
			return true;
		}
	}
	return false;
}

void ToggleFMA(bool bEnable)
{
	if (!bHookedIntersectRect)
	{
		HookIntersectRect(TRUE);
	}
	bFMAEnabled = bEnable;
}

void ToggleItemFilter(bool bEnable)
{
	*pdwItemFilterPointer = bEnable ? (DWORD)ItemFilter : dwOriginal;
}

bool ToggleCPUHack(bool bEnable)
{
    DWORD dwOldProtect = 0;
	DWORD dwNumberOfBytesToProtect = sizeof(DWORD);
	if (IsWow64())
	{
		if (VirtualProtect((PVOID)pdwVariantInitPointer, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &dwOldProtect))
		{
			*reinterpret_cast<DWORD *>(pdwVariantInitPointer) = bEnable ? (DWORD)VariantInitHook : dwVariantInit;
			VirtualProtect((PVOID)pdwVariantInitPointer, sizeof(DWORD), dwOldProtect, &dwOldProtect);
			return true;
		}
	}
	else
	{
		if (NtProtectVirtualMemory(GetCurrentProcess(), (PVOID)pdwVariantInitPointer, &dwNumberOfBytesToProtect, PAGE_EXECUTE_READWRITE, &dwOldProtect) == 0x00000000)
		{
			*reinterpret_cast<DWORD *>(pdwVariantInitPointer) = bEnable ? (DWORD)VariantInitHook : dwVariantInit;
			NtProtectVirtualMemory(GetCurrentProcess(), (PVOID)pdwVariantInitPointer, &dwNumberOfBytesToProtect, dwOldProtect, &dwOldProtect);
			return true;
		}
	}
	return false;
}

void ToggleAlert(bool bEnable)
{
	if (bEnable)
	{
		WritePointer(alertBase, alertHealth, 20);
		WritePointer(alertBase, alertMana, 20);
	}
	else
	{
		WritePointer(alertBase, alertHealth, 19);
		WritePointer(alertBase, alertMana, 19);
	}
}

void AddItemToBlacklist(DWORD dwItem)
{
	vBlacklist.insert(vBlacklist.begin(), dwItem);
}

void RemoveItemFromBlacklist(int index)
{
	vBlacklist.erase(vBlacklist.end() - index - 2);
}

void ClearBlacklist()
{
	vBlacklist.clear();
	vBlacklist.push_back(0);
}

void ShowMessage(std::string const& strMessage, MessageType nType)
{
	ZXString<char> str;
	str._m_pStr = const_cast<char*>(strMessage.c_str());
	CHATLOG_ADD(&str, static_cast<unsigned short>(nType));
}

#pragma endregion