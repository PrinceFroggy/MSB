#include "Form3.h"
#include "Packet.h"

using namespace Acooltrainer;

#pragma region Variables

std::string packet;

bool methodSwitch2 = false;
bool packetSwitch2 = false;

#pragma endregion

#pragma region Functions

void MarshalString(String ^ s,std::string& os)
{
	using namespace Runtime::InteropServices;

	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();

	os = chars;

	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void ThreadSafeSendPacket()
{
	std::string error;

	if(!SendPacket(packet,error))
	{
		::MessageBox(0, error.c_str(), "Failed to inject packet.", MB_OK | MB_ICONERROR);
	}
}

void ThreadSafeRecvPacket()
{
	std::string error;

	if(!RecvPacket(packet,error))
	{
		::MessageBox(0, error.c_str(), "Failed to inject packet.", MB_OK | MB_ICONERROR);
	}
}

VOID PacketSpam()
{
	while (packetSwitch2)
	{
		if (methodSwitch2)
		{
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&ThreadSafeRecvPacket, NULL, 0, NULL);
		}
		else
		{
			CreateThread(0,0,(LPTHREAD_START_ROUTINE)&ThreadSafeSendPacket,0,0,0);
		}
		
		Sleep(1000);
	}
}

#pragma endregion

#pragma region Form events

void Form3::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = panel1;

	if (receiveToolStripMenuItem->Checked)
	{
		methodSwitch2 = true;

		MarshalString(textBox1->Text,packet);

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&ThreadSafeRecvPacket, NULL, 0, NULL);
	}
	else
	{
		methodSwitch2 = false;

		MarshalString(textBox1->Text,packet);

		CreateThread(0,0,(LPTHREAD_START_ROUTINE)&ThreadSafeSendPacket,0,0,0);
	}
}

void Form3::spamToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = panel1;

	if (spamToolStripMenuItem->Checked)
	{
		if (textBox1->Text != "")
		{
			MarshalString(textBox1->Text,packet);

			textBox1->ReadOnly = true;

			packetSwitch2 = true;

			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&PacketSpam, NULL , 0, NULL );

			BlockSpam(true);
		}
		else
		{
			::MessageBox(0, "Please enter a packet.", "Failed to spam packet.", MB_OK | MB_ICONERROR);

			spamToolStripMenuItem->Checked = false;
		}
	}
	else
	{
		packetSwitch2 = false;

		textBox1->ReadOnly = false;

		BlockSpam(false);
	}
}

#pragma endregion