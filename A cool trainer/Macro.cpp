#include "Hack.h"
#include "Macro.h"

#pragma region Variables

#define AttackKey 0
#define LootKey 1
#define HealthKey 2
#define ManaKey 3
#define SkillKey 4

int nKeys [5];

static enum StringValue { evS1, evS2, evS3, evS4, evS5, evS6, evS7, evS8, evS9, evS10, evS11, evS12, evS13, evS14, evS15, evS16, evS17, evS18, evS19, evS20, evS21, evS22, evS23, evS24, evS25, evS26, evS27, evS28, evS29, evS30, evS31, evS32, evS33, evS34, evS35, evS36, evS37, evS38, evS39, evS40, evS41, evS42, evS43, evS44, evS45};

static std::map<std::string, StringValue> s_mapStringValues;

HWND maplestory;

int healthValue;
int manaValue;

int attackDelay;
int skillDelay;

bool attackSwitch = false;
bool attackMethod = false;
bool lootSwitch = false;
bool healthSwitch = false;
bool manaSwitch = false;
bool channelSwitch = false;
bool skillSwitch = false;

bool macroBlock = false;

#pragma endregion

#pragma region Functions

void initializeKeys()
{
	s_mapStringValues["0"] = evS1;
	s_mapStringValues["1"] = evS2;
	s_mapStringValues["2"] = evS3;
	s_mapStringValues["3"] = evS4;
	s_mapStringValues["4"] = evS5;
	s_mapStringValues["5"] = evS6;
	s_mapStringValues["6"] = evS7;
	s_mapStringValues["7"] = evS8;
	s_mapStringValues["8"] = evS9;
	s_mapStringValues["9"] = evS10;

	s_mapStringValues["A"] = evS11;
	s_mapStringValues["B"] = evS12;
	s_mapStringValues["C"] = evS13;
	s_mapStringValues["D"] = evS14;
	s_mapStringValues["E"] = evS15;
	s_mapStringValues["F"] = evS16;
	s_mapStringValues["G"] = evS17;
	s_mapStringValues["H"] = evS18;
	s_mapStringValues["I"] = evS19;
	s_mapStringValues["J"] = evS20;

	s_mapStringValues["K"] = evS21;
	s_mapStringValues["L"] = evS22;
	s_mapStringValues["M"] = evS23;
	s_mapStringValues["N"] = evS24;
	s_mapStringValues["O"] = evS25;
	s_mapStringValues["P"] = evS26;
	s_mapStringValues["Q"] = evS27;
	s_mapStringValues["R"] = evS28;
	s_mapStringValues["S"] = evS29;
	s_mapStringValues["T"] = evS30;

	s_mapStringValues["U"] = evS31;
	s_mapStringValues["V"] = evS32;
	s_mapStringValues["W"] = evS33;
	s_mapStringValues["X"] = evS34;
	s_mapStringValues["Y"] = evS35;
	s_mapStringValues["Z"] = evS36;

	s_mapStringValues["SHIFT"] = evS37;
	s_mapStringValues["CTRL"] = evS38;
	s_mapStringValues["ALT"] = evS39;
	s_mapStringValues["PAGE UP"] = evS40;
	s_mapStringValues["PAGE DOWN"] = evS41;
	s_mapStringValues["END"] = evS42;
	s_mapStringValues["HOME"] = evS43;
	s_mapStringValues["INS"] = evS44;
	s_mapStringValues["DEL"] = evS45;
}

BOOL CheckMethod(__in INT nKey)
{
	bool returnType = false;

	switch (nKey)
	{
	case 0:
		if (nKeys[AttackKey] != NULL && attackDelay != NULL)
		{
			returnType = true;
		}
		else
		{
			returnType = false;
		}
		break;
	case 1:
		if (nKeys[LootKey] != NULL)
		{
			returnType = true;
		}
		else
		{
			returnType = false;
		}
		break;
	case 2:
		if (nKeys[HealthKey] != NULL && healthValue != NULL)
		{
			returnType = true;
		}
		else
		{
			returnType = false;
		}
		break;
	case 3:
		if (nKeys[ManaKey] != NULL && manaValue != NULL)
		{
			returnType = true;
		}
		else
		{
			returnType = false;
		}
		break;
	case 4:
		returnType = true;
		break;
	case 5:
		if (nKeys[SkillKey] != NULL && skillDelay != NULL)
		{
			returnType = true;
		}
		else
		{
			returnType = false;
		}
		break;
	}
	return returnType;
}

BOOL KeyAvailable(__in INT nTemp)
{
	for (int i = 0; i < _countof(nKeys); i++)
	{
		if (nTemp == nKeys[i])
			return FALSE;
	}
	return TRUE;
}

void ClearKey(int keyValue)
{
	nKeys[keyValue] = NULL;
}

void AssignKey(int keyValue, int key)
{
	nKeys[keyValue] = key;
}

void AssignIntegers(int selection, int integer)
{
	switch (selection)
	{
	case 0:
		attackDelay = integer;
		break;
	case 1:
		healthValue = integer;
		break;
	case 2:
		manaValue = integer;
		break;
	case 3:
		skillDelay = integer;
		break;
	}
}

void AssignKeyMethod(bool bEnable)
{
	attackMethod = bEnable;
}

void maplestoryHandle()
{
	maplestory = FindWindowA("MapleStoryClass", NULL);
}

void PressKey(HWND hWnd, unsigned int key)
{
	LPARAM lparam = (MapVirtualKey(key, 0) << 16) + 1;
	PostMessage(hWnd, WM_KEYDOWN, key, lparam);
	PostMessage(hWnd, WM_KEYUP, key, NULL);
}

void HoldKey(HWND hWnd, unsigned int key)
{
	LPARAM lparam = (MapVirtualKey(key, 0) << 16) + 1;
	PostMessage(hWnd, WM_KEYDOWN, key, lparam);
}

#pragma endregion

#pragma region Threads

VOID autoAttack()
{
	while (attackSwitch)
	{
		if (!macroBlock)
		{
			if (attackMethod)
			{
				HoldKey(maplestory, nKeys[AttackKey]);
			
				Sleep(attackDelay);
			}
			else
			{
				PressKey(maplestory, nKeys[AttackKey]);
				Sleep(attackDelay);
			}
		}
	}
	return;
}

VOID autoLoot()
{
	while (lootSwitch)
	{
		if (!macroBlock)
		{
			HoldKey(maplestory, nKeys[LootKey]);
		
			Sleep(100);
		}
	}
	return;
}

VOID autoHealth()
{
	while (healthSwitch)
	{
		if (UpdateHealth() <= healthValue)
		{
			PressKey(maplestory, nKeys[HealthKey]);
		}
		Sleep(100);
	}
	return;
}

VOID autoMana()
{
	while (manaSwitch)
	{
		if (UpdateMana() <= manaValue)
		{
			PressKey(maplestory, nKeys[ManaKey]);
		}
		Sleep(100);
	}
	return;
}

VOID autoChannel()
{
	while (channelSwitch)
	{
		if (UpdatePeople())
		{
			MacroBlock(true);
			ChangeChannel();
		}
		Sleep(100);
	}
	return;
}

VOID autoSkill()
{
	while (skillSwitch)
	{
		if (!macroBlock)
		{
			MacroBlock(true);

			Sleep(1000);

			PressKey(maplestory, nKeys[SkillKey]);

			Sleep(5000);

			MacroBlock(false);
			
			Sleep(skillDelay);
		}
	}
	return;
}

#pragma endregion

#pragma region Thread Functions

void Attack(bool bEnable)
{
	if (bEnable)
	{
		maplestoryHandle();

		attackSwitch = true;

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&autoAttack, NULL , 0, NULL );
	}
	else
	{
		attackSwitch = false;
	}
}

void Loot(bool bEnable)
{
	if (bEnable)
	{
		maplestoryHandle();

		lootSwitch = true;

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&autoLoot, NULL , 0, NULL );
	}
	else
	{
		lootSwitch = false;
	}
}

void Health(bool bEnable)
{
	if (bEnable)
	{
		maplestoryHandle();

		ToggleAlert(true);

		healthSwitch = true;

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&autoHealth, NULL , 0, NULL );
	}
	else
	{
		ToggleAlert(false);

		healthSwitch = false;
	}
}

void Mana(bool bEnable)
{
	if (bEnable)
	{
		maplestoryHandle();

		ToggleAlert(true);

		manaSwitch = true;

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&autoMana, NULL , 0, NULL );
	}
	else
	{
		ToggleAlert(false);

		manaSwitch = false;
	}
}

void Channel(bool bEnable)
{
	if (bEnable)
	{
		channelSwitch = true;

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&autoChannel, NULL , 0, NULL );
	}
	else
	{
		channelSwitch = false;
	}
}

void Skill(bool bEnable)
{
	if (bEnable)
	{
		maplestoryHandle();

		skillSwitch = true;

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&autoSkill, NULL , 0, NULL );
	}
	else
	{
		skillSwitch = false;
	}
}

#pragma endregion

#pragma region General Functions

void MacroBlock(bool bEnable)
{
	macroBlock = bEnable;
}

#pragma endregion