#include "Packet.h"

#pragma region Maplestory memory

#define RECV_RETURN_ADDRESS 0x00507681

#pragma endregion

#pragma region Variables

std::vector<std::string> vBlockedPackets;

bool bSpam = false;

#pragma endregion

#pragma region API

typedef void (__fastcall *pfnFreePacket)(PVOID pPacket);
const PVOID *ppCClientSocket = reinterpret_cast<const PVOID*>(0x012FD054);
const pfnFreePacket FreePacket = reinterpret_cast<pfnFreePacket>(0x0043B820);

DWORD *const pdwInterlockedIncrement = reinterpret_cast<DWORD *>(0x01010094);
const DWORD dwInterlockedIncrement = reinterpret_cast<DWORD>(GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), TEXT("InterlockedIncrement")));

#pragma endregion

#pragma region Functions

template <typename T>
struct HexTo
{
	T value;

	operator T() const
	{
		return value;
	}

	friend std::istream& operator>>(std::istream &in, HexTo &out)
	{
		in >> std::hex >> out.value;
		return in;
	}
};

void ParsePacket(std::string &strPacket, std::vector<BYTE> &vData)
{
	typedef boost::tokenizer<boost::char_separator<char>> Tokenizer;

	vData.clear();

	boost::trim(strPacket);

	static std::tr1::uniform_int<BYTE> gen(0, 15);
	static std::tr1::mt19937 engine;

	static const char szDigits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	for (std::size_t index = 0; index < strPacket.length(); ++index)
	{
		if (strPacket[index] == '*')
		{
			strPacket[index] = szDigits[gen(engine)];
		}
	}

	Tokenizer Tokens(strPacket);

	for (Tokenizer::const_iterator iterate = Tokens.begin(), end = Tokens.end(); iterate != end; ++iterate)
	{
		vData.push_back(static_cast<BYTE>(boost::lexical_cast<HexTo<UINT>>(*iterate)));
	}
}

void BlockSpam(bool bEnable)
{
	bSpam = bEnable;
}

bool CheckSpam()
{
	return bSpam;
}

#pragma endregion

#pragma region Packet functions

bool SendPacket(std::string &strPacket, std::string &strError)
{
	strError.clear();
	boost::trim(strPacket);

	if (strPacket.empty())
	{
		strError = "Please enter a packet.";
		return false;
	}
	std::vector<BYTE> vData;
	try
	{
		ParsePacket(strPacket, vData);
	}
	catch (std::exception &exc)
	{
		strError = exc.what();
		return false;
	}
	catch (...)
	{
		strError = "Unknown error (send)!";
		return false;
	}

	COutPacket *pPacket = new COutPacket();
	SecureZeroMemory(pPacket, sizeof(COutPacket));
	pPacket->dwSize = vData.size();
	pPacket->pData = vData.data();

	try
	{
		InjectPacket(pPacket);
	}
	catch (...)
	{
		strError = "Internal error (send)!";
		return false;
	}
	return true;
}

bool SendPacket(std::vector<BYTE> vData)
{
	COutPacket *pPacket = new COutPacket();
	SecureZeroMemory(pPacket, sizeof(COutPacket));
	
	pPacket->dwSize = vData.size();
	pPacket->pData = vData.data();

	try
	{
		InjectPacket(pPacket);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool RecvPacket(std::string &strPacket, std::string &strError)
{
	strError.clear();
	boost::trim(strPacket);

	if (strPacket.empty())
	{
		strError = "Please enter a packet.";
		return false;
	}
	std::vector<BYTE> vData;
	try
	{
		ParsePacket(strPacket, vData);
	}
	catch (std::exception &exc)
	{
		strError = exc.what();
		return false;
	}
	catch (...)
	{
		strError = "Unknown error (send)!";
		return false;
	}

	static std::tr1::uniform_int<DWORD> gen;
	static std::tr1::mt19937 engine;

	DWORD dwHeader = gen(engine);

	for (int i = 0; i < sizeof(DWORD); ++i)
	{
		vData.insert(vData.begin(), static_cast<BYTE>(dwHeader >> (i * 8)));
	}

	CInPacket *pPacket = new CInPacket();
	pPacket->fLoopback = 0;
	pPacket->iState = 2;
	pPacket->pData = vData.data();
	pPacket->dwTotalLength = vData.size();
	pPacket->dwUnknown = 0;
	pPacket->dwValidLength = pPacket->dwValidLength - 4;
	pPacket->uOffset = 4;

	try
	{
		InjectPacket(pPacket);
	}
	catch (...)
	{
		strError = "Internal error!";
		return false;
	}
	return true;
} 

bool RecvPacket(std::vector<BYTE> vData)
{
	static std::tr1::uniform_int<DWORD> gen;
	static std::tr1::mt19937 engine;

	DWORD dwHeader = gen(engine);

	for (int i = 0; i < sizeof(DWORD); ++i)
	{
		vData.insert(vData.begin(), static_cast<BYTE>(dwHeader >> (i * 8)));
	}

	CInPacket *pPacket = new CInPacket();
	pPacket->fLoopback = 0;
	pPacket->iState = 2;
	pPacket->pData = vData.data();
	pPacket->dwTotalLength = vData.size();
	pPacket->dwUnknown = 0;
	pPacket->dwValidLength = pPacket->dwValidLength - 4;
	pPacket->uOffset = 4;

	try
	{
		InjectPacket(pPacket);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool IsBlueBoxPacket(BYTE *pbData)
{
	return pbData[4] == 0xF5 && pbData[5] == 0x00;
}

#pragma endregion

#pragma region Block functions

__declspec(noinline) void __stdcall RecvCallback(CInPacket *pPacket)
{
	/*
	// change later to block packets (match formatted packets in vBlockedPackets)
	// static const BYTE pHeader[] = {0xF5, 0x00, 0x05};
	BYTE *pbData = reinterpret_cast<BYTE *>(pPacket->pData);
	size_t nSize = pPacket->dwValidLength * 3 + 8;
	TCHAR *szBuffer = new TCHAR[nSize];
	_stprintf_s(szBuffer, pPacket->dwValidLength * 3 + 8, TEXT("Packet:"));
	for (size_t i = 0; i < pPacket->dwValidLength; ++i)
	{
		_stprintf_s(szBuffer, nSize, TEXT("%s %X"), szBuffer, pbData[i + 4]);
	}
	OutputDebugString(szBuffer);
	*/
	if (pPacket->dwValidLength >= 2)
	{
		BYTE *pbData = reinterpret_cast<BYTE *>(pPacket->pData);
		if (IsBlueBoxPacket(pbData))
		{
			OutputDebugString(TEXT("Attempting to block blue box."));
			pbData[4] = 0;
			pbData[5] = 0;
		}
	}
}

__declspec(naked) void RecvPacketHook()
{
	__asm
	{
		cmp dword ptr [esp], RECV_RETURN_ADDRESS
		jne offset Return
		mov dword ptr [esp], offset Hook
Return:
		push dword ptr [dwInterlockedIncrement]
		ret
Hook:
		push dword ptr [esp+0x2C]
		call offset RecvCallback
		push RECV_RETURN_ADDRESS
		ret
	}
}

bool BlockRecv(bool bEnable)
{
	bool bSuccess = false;
	DWORD dwOldProtect;
	if (VirtualProtect((PVOID)pdwInterlockedIncrement, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect))
	{
		__try
		{
			*pdwInterlockedIncrement = bEnable ? (DWORD)RecvPacketHook : dwInterlockedIncrement;
		}
		__finally
		{
			bSuccess = true;
		}
		VirtualProtect((PVOID)pdwInterlockedIncrement, 4, dwOldProtect, &dwOldProtect);
	}
	return bSuccess;
}

void BlockRecvPacket(std::string strPacket)
{
	vBlockedPackets.push_back(strPacket);
}

#pragma endregion

#pragma region Inject functions

void InjectPacket(COutPacket *pPacket)
{
	typedef void (__fastcall *pfnSendPacket)(PVOID pCClientSocket, PVOID pEDX, COutPacket *pPacket);
	typedef DWORD (__fastcall *pfnDecryptData)(PVOID pData);

	static const pfnSendPacket SendPacket = reinterpret_cast<pfnSendPacket>(0x005062E0);
	static const PVOID pReturnAddress = reinterpret_cast<const PVOID>(0x0040CC18);
	static const pfnDecryptData DecryptData = reinterpret_cast<pfnDecryptData>(0x004944E0);
	static const PVOID pLastThreadId = reinterpret_cast<const PVOID>(0x01302060);
	static const DWORD dwRealThreadIdOffset = 0x000006B8;
	
	__writefsdword(dwRealThreadIdOffset, DecryptData(pLastThreadId));

	__asm
	{
		push Next
		push ecx
		mov ecx, dword ptr [ppCClientSocket]
		mov ecx, dword ptr [ecx]
		push dword ptr [pPacket]
		push dword ptr [pReturnAddress]
		jmp dword ptr [SendPacket]
Next:
	}
	FreePacket(reinterpret_cast<PVOID>(pPacket));
}

void InjectPacket(CInPacket *pPacket)
{
	typedef void (__fastcall *pfnRecvPacket)(PVOID pCClientSocket, PVOID pEDX, CInPacket *pPacket);
	typedef void (__fastcall *pfnFreePacket)(CInPacket *pPacket);

	static const pfnRecvPacket RecvPacket = reinterpret_cast<pfnRecvPacket>(0x00507640);

	RecvPacket(*ppCClientSocket, NULL, pPacket);
	FreePacket(reinterpret_cast<PVOID>(pPacket));
}

#pragma endregion