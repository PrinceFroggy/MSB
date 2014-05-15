#ifndef MACROS_H
#define MACROS_H

#include <windows.h>
#include <map>
#include <string>

void initializeKeys();

BOOL CheckMethod(__in INT nKey);
BOOL KeyAvailable(__in INT nTemp);

void ClearKey(int keyValue);
void AssignKey(int keyValue, int key);
void AssignIntegers(int selection, int integer);
void AssignKeyMethod(bool bEnable);

void Attack(bool bEnable);
void Loot(bool bEnable);
void Health(bool bEnable);
void Mana(bool bEnable);
void Channel(bool bEnable);
void Skill(bool bEnable);

void MacroBlock(bool bEnable);

#endif