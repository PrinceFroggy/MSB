#pragma once
#ifndef PACKET_H
#define PACKET_H

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <cassert>
#include <random>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/smart_ptr.hpp>
#pragma pack(push, 1)

struct COutPacket
{
	BOOL fLoopback;
	PVOID pData;
	DWORD dwSize;
	UINT uOffset;
	BOOL fEncrypted;
};

struct CInPacket
{
	BOOL fLoopback;
	int iState;
	PVOID pData;
	DWORD dwTotalLength;
	DWORD dwUnknown;
	DWORD dwValidLength;
	UINT uOffset;
};

void ParsePacket(std::string &strPacket, std::vector<BYTE> &vData);
bool SendPacket(std::string &strPacket, std::string &strError);
bool SendPacket(std::vector<BYTE> vData);
bool RecvPacket(std::string &strPacket, std::string &strError);
bool RecvPacket(std::vector<BYTE> vData);
void InjectPacket(COutPacket *pPacket);
void InjectPacket(CInPacket *pPacket);
bool BlockRecv(bool bEnable);
void BlockSpam(bool bEnable);
bool CheckSpam();

#endif