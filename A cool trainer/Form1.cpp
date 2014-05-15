#include "Form1.h"
#include "Hack.h"
#include "Macro.h"
#include "Packet.h"

using namespace Acooltrainer;

void Main(void)		
{
	initializeKeys();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Form1);	
	Application::Exit();
}

#pragma region Variables

bool spamPacket = false;
bool buttonSwitch = false;
bool buttonBlock = false;
bool formSwitch = false;
bool packetSwitch = false;
bool packetOpen = false;
bool methodSwitch = false;

#pragma endregion

#pragma region Form Events

void Form1::tabControl1_Selecting(System::Object^  sender, System::Windows::Forms::TabControlCancelEventArgs^  e) 
{
	if (tabControl1->SelectedTab == tabPage1)
	{
		if (_Form2->Visible)
		{
			::MessageBox(0, "Please close the settings dialog.", "Failed to switch tabs.", MB_OK | MB_ICONERROR);

			e->Cancel = true;
		}
		else if (buttonBlock)
		{
			::MessageBox(0, "Please close the information dialog.", "Failed to switch tabs.", MB_OK | MB_ICONERROR);

			e->Cancel = true;
		}
		else
		{
			button2->Text = "Packets";

			toolTip1->SetToolTip(button2, "Open packets dialog.");

			packetSwitch = false;

			Form1::Height = 276;
		}
	}
	else if (tabControl1->SelectedTab == tabPage2)
	{
		if (_Form3->Visible)
		{
			::MessageBox(0, "Please close the packets dialog.", "Failed to switch tabs.", MB_OK | MB_ICONERROR);

			e->Cancel = true;
		}
		else if (buttonBlock)
		{
			::MessageBox(0, "Please close the information dialog.", "Failed to switch tabs.", MB_OK | MB_ICONERROR);

			e->Cancel = true;
		}
		else
		{
			button2->Text = "Settings";

			toolTip1->SetToolTip(button2, "Open settings dialog.");

			packetSwitch = true;

			buttonSwitch = false;

			Form1::Height = 276;
		}
	}
	else
	{
		if (_Form3->Visible)
		{
			::MessageBox(0, "Please close the packets dialog.", "Failed to switch tabs.", MB_OK | MB_ICONERROR);

			e->Cancel = true;
		}
		else if (_Form2->Visible)
		{
			::MessageBox(0, "Please close the settings dialog.", "Failed to switch tabs.", MB_OK | MB_ICONERROR);

			e->Cancel = true;
		}
		else
		{
			button2->Text = "Information";

			toolTip1->SetToolTip(button2, "Open information dialog.");

			packetSwitch = true;

			buttonSwitch = true;

			Form1::Height = 276;
		}
	}
}

void Form1::button2_Click(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = tabControl1->SelectedTab;

	if (!packetSwitch)
	{
		if (CheckSpam())
		{
			::MessageBox(0, "Please disable the packet spam.", "Failed to close packets dialog.", MB_OK | MB_ICONERROR);
		}
		else
		{
			if (packetOpen)
			{
				_Form3->Visible = false;

				toolTip1->SetToolTip(button2, "Open packets dialog.");

				packetOpen = false;
			}
			else
			{
				_Form3->Visible = true;

				toolTip1->SetToolTip(button2, "Close packets dialog.");

				packetOpen = true;
			}
		}
	}
	else
	{
		if (buttonSwitch)
		{
			buttonBlock = true;

			::MessageBox(0, "download.m-84.com", "Information", MB_OK | MB_ICONASTERISK);
		
			buttonBlock = false;
		}
		else
		{
			if (listView2->Items[0]->Checked || listView2->Items[1]->Checked || listView2->Items[2]->Checked || listView2->Items[3]->Checked || listView2->Items[4]->Checked || listView2->Items[5]->Checked)
			{
				::MessageBox(0, "Please disable the macro(s).", "Failed to initiate settings dialog.", MB_OK | MB_ICONERROR);
			}
			else
			{
				if (formSwitch)
				{
					_Form2->Visible = false;

					toolTip1->SetToolTip(button2, "Open settings dialog.");

					formSwitch = false;
				}
				else
				{
					_Form2->Visible = true;

					toolTip1->SetToolTip(button2, "Close settings dialog.");

					formSwitch = true;
				}
			}
		}
	}
}

void Form1::listView1_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e)
{
	if (e->CurrentValue == CheckState::Unchecked)
	{
		switch (e->Index)
		{
		case 0:
			ToggleKami(true);

			listView1->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Bold);

			ShowMessage("[MSB] Kami enabled.", Special_BlackWhite);
			break;

		case 1:
			ToggleGodmode(true);

			listView1->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Bold);

			ShowMessage("[MSB] Godmode enabled.", Special_BlackWhite);
			break;

		case 2:
			ToggleFusionAttack(true);

			listView1->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Bold);

			ShowMessage("[MSB] Fusion attack enabled.", Special_BlackWhite);
			break;

		case 3:
			ToggleItemFilter(true);

			listView1->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Bold);

			button1->Enabled = false;

			listView3->ContextMenuStrip = nullptr;

			ShowMessage("[MSB] Item filter enabled.", Special_BlackWhite);
			break;

		case 4:
			ToggleCPUHack(true);

			listView1->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Bold);

			ShowMessage("[MSB] Background filter enabled.", Special_BlackWhite);
			break;

		case 5:
			ToggleGND(true);

			listView1->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Bold);

			ShowMessage("[MSB] GND & Unlimited MP enabled.", Special_BlackWhite);
			break;
		}
	}
	else if (e->CurrentValue == CheckState::Checked)
	{
		switch (e->Index)
		{
		case 0:
			ToggleKami(false);

			listView1->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Regular);

			ShowMessage("[MSB] Kami disabled.", Special_BlackWhite);
			break;

		case 1:
			ToggleGodmode(false);

			listView1->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Regular);

			ShowMessage("[MSB] Godmode disabled.", Special_BlackWhite);
			break;

		case 2:
			ToggleFusionAttack(false);

			listView1->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Regular);

			ShowMessage("[MSB] Fusion attack disabled.", Special_BlackWhite);
			break;

		case 3:
			ToggleItemFilter(false);

			listView1->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Regular);

			button1->Enabled = true;

			listView3->ContextMenuStrip = contextMenuStrip1;

			ShowMessage("[MSB] Item filter disabled.", Special_BlackWhite);
			break;

		case 4:
			ToggleCPUHack(false);

			listView1->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Regular);

			ShowMessage("[MSB] Background filter disabled.", Special_BlackWhite);
			break;

		case 5:
			ToggleGND(false);

			listView1->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Regular);

			ShowMessage("[MSB] GND & Unlimited MP disabled.", Special_BlackWhite);
			break;
		}
	}
}

void Form1::listView2_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e)
{
	if (formSwitch)
	{
		::MessageBox(0, "Please close the settings dialog.", "Failed to initiate macro.", MB_OK | MB_ICONERROR);

		e->NewValue = CheckState::Unchecked;
	}
	else
	{
		if (CheckMethod(e->Index))
		{
			if (e->CurrentValue == CheckState::Unchecked)
			{
				switch (e->Index)
				{
				case 0:
					Attack(true);

					listView2->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Bold);

					ShowMessage("[MSB] Automated attack enabled.", Blue);
					break;

				case 1:
					Loot(true);

					listView2->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Bold);
			
					ShowMessage("[MSB] Automated loot enabled.", Blue);
					break;

				case 2:
					Health(true);

					listView2->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Bold);
			
					ShowMessage("[MSB] Automated health enabled.", Blue);
					break;

				case 3:
					Mana(true);

					listView2->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Bold);
			
					ShowMessage("[MSB] Automated mana enabled.", Blue);
					break;

				case 4:
					BlockRecv(true);

					Channel(true);

					listView2->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Bold);
			
					ShowMessage("[MSB] Automated channel enabled.", Blue);
					break;

				case 5:
					Skill(true);

					listView2->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Bold);
			
					ShowMessage("[MSB] Automated skill enabled.", Blue);
					break;
				}
			}
			else if (e->CurrentValue == CheckState::Checked)
			{
				switch (e->Index)
				{
				case 0:
					Attack(false);

					listView2->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Regular);
			
					ShowMessage("[MSB] Automated attack disabled.", Blue);
					break;

				case 1:
					Loot(false);

					listView2->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Regular);
			
					ShowMessage("[MSB] Automated loot disabled.", Blue);
					break;

				case 2:
					Health(false);

					listView2->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Regular);
			
					ShowMessage("[MSB] Automated health disabled.", Blue);
					break;

				case 3:
					Mana(false);

					listView2->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Regular);
			
					ShowMessage("[MSB] Automated mana disabled.", Blue);
					break;

				case 4:
					BlockRecv(false);

					Channel(false);

					listView2->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Regular);
			
					ShowMessage("[MSB] Automated channel disabled.", Blue);
					break;

				case 5:
					Skill(false);

					listView2->Items[e->Index]->SubItems[0]->Font = gcnew System::Drawing::Font("Consolas", 8, System::Drawing::FontStyle::Regular);
			
					ShowMessage("[MSB] Automated skill disabled.", Blue);
					break;
				}
			}
		}
		else
		{
			::MessageBox(0, "Please assign all the values to the macro.", "Failed to initiate macro.", MB_OK | MB_ICONERROR);

			e->NewValue = CheckState::Unchecked;
		}
	}
}

void Form1::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = tabControl1->SelectedTab;

	if (textBox1->Text->Length == 0)
	{
		::MessageBox(0, "Please enter a item.", "Failed to add item.", MB_OK | MB_ICONERROR);
	}
	else
	{
		ListViewItem^ item = gcnew ListViewItem();
		item->SubItems->Add(textBox1->Text);
		listView3->Items->Add(item);
		AddItemToBlacklist(Convert::ToUInt32(textBox1->Text, 10));

		listView3->Cursor = Cursors::Hand;
		listView3->ContextMenuStrip = contextMenuStrip1;
	}
}

void Form1::removeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = tabControl1->SelectedTab;

	if (listView3->SelectedItems->Count == 0)
	{
		::MessageBox(0, "Please select data.", "Failed to remove data.", MB_OK | MB_ICONERROR);
	}
	else
	{
		for (int i = 0; i < listView3->Items->Count; i++ )
		{
			if (listView3->Items[i]->Selected)
			{
				RemoveItemFromBlacklist(i);
				listView3->Items[i]->Remove();
				--i;
			}
		}

		if (listView3->Items->Count == 0)
		{
			listView3->Cursor = Cursors::Default;
			listView3->ContextMenuStrip = nullptr;
		}
	}
}

void Form1::clearToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
{
	ActiveControl = tabControl1->SelectedTab;

	if (listView3->Items->Count == 0)
	{
		::MessageBox(0, "Please insert data.", "Failed to clear data.", MB_OK | MB_ICONERROR);
	}
	else
	{
		ClearBlacklist();
		listView3->Items->Clear();
		listView3->Refresh();

		listView3->Cursor = Cursors::Default;
		listView3->ContextMenuStrip = nullptr;
	}
}

#pragma endregion