#ifndef HACK_H
#define HACK_H

#include <windows.h>
#include <string>
#include <detours.h>
#include <vector>

#pragma comment(lib, "detours.lib")

enum MessageType
{
        White = 0,
        Green = 1,
        Lightpurple = 2,
        Orange = 3,
        Purple = 4,
        Lightgreen = 5,
        Special_PurpleGrey = 6,
        Grey = 7,
        Yellow = 8,
        Lightyellow = 9,
        Blue = 10,
        Special_BlackWhite = 11,
        Red = 12
};

BOOL HookIntersectRect(__in BOOL bState);
void ToggleKami(bool bEnable);
void ToggleGodmode(bool bEnable);
void ToggleFusionAttack(bool bEnable);
bool ToggleGND(bool bEnable);
void ToggleItemFilter(bool bEnable);
bool ToggleCPUHack(bool bEnable);
void ToggleAlert(bool bEnable);
void AddItemToBlacklist(DWORD dwItem);
void RemoveItemFromBlacklist(int index);
void ClearBlacklist();
void ShowMessage(std::string const &strMessage, MessageType nType);
void ChangeChannel();

int UpdateHealth();
int UpdateMana();
bool UpdatePeople();
int GenerateHealthValue();
int GenerateManaValue();

#endif