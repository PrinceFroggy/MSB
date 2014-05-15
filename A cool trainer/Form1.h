#pragma once
#include "Form2.h"
#include "Form3.h"
#include <windows.h>
#include <commctrl.h>

namespace Acooltrainer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form2^ _Form2;
		Form3^ _Form3;

		Form1(void)
		{
			InitializeComponent();
			
			_Form2 = gcnew Form2;
			_Form3 = gcnew Form3;

			ActiveControl = tabControl1->SelectedTab;

			SendMessage((HWND)textBox1->Handle.ToPointer(), EM_SETCUEBANNER, (WPARAM)FALSE, (LPARAM)L"Item...");

			button2->Text = "Packets";

			toolTip1->SetToolTip(button2, "Open packets dialog.");
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		virtual void WndProc(Message% m) override 
		{
			__super::WndProc(m);
			if (m.Msg == WM_NCHITTEST) 
			{
				switch ((int)m.Result) 
				{
				case HTLEFT: 
				case HTRIGHT: 
				case HTTOP: 
                case HTTOPLEFT: 
				case HTTOPRIGHT:
                case HTBOTTOMLEFT: 
				case HTBOTTOMRIGHT:
					m.Result = (IntPtr)HTCLIENT;
				}
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;





	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::ListView^  listView2;
	private: System::Windows::Forms::ColumnHeader^  columnHeader3;
	private: System::Windows::Forms::ColumnHeader^  columnHeader4;
	private: System::Windows::Forms::TextBox^  textBox1;

	private: System::Windows::Forms::ListView^  listView3;
	private: System::Windows::Forms::ColumnHeader^  columnHeader5;

	private: System::Windows::Forms::Button^  button1;

	private: System::Windows::Forms::ColumnHeader^  columnHeader6;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;


	private: System::Windows::Forms::ToolStripMenuItem^  removeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clearToolStripMenuItem;
	private: System::Windows::Forms::Button^  button2;


	private: System::Windows::Forms::ToolTip^  toolTip1;








	private: System::ComponentModel::IContainer^  components;



	protected: 






	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::ListViewGroup^  listViewGroup1 = (gcnew System::Windows::Forms::ListViewGroup(L"General", System::Windows::Forms::HorizontalAlignment::Center));
			System::Windows::Forms::ListViewGroup^  listViewGroup2 = (gcnew System::Windows::Forms::ListViewGroup(L"Anti-Detection", System::Windows::Forms::HorizontalAlignment::Center));
			System::Windows::Forms::ListViewItem^  listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {L"", 
				L"Automated attack"}, -1));
			System::Windows::Forms::ListViewItem^  listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {L"", 
				L"Automated loot"}, -1));
			System::Windows::Forms::ListViewItem^  listViewItem3 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {L"", 
				L"Automated health"}, -1));
			System::Windows::Forms::ListViewItem^  listViewItem4 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {L"", 
				L"Automated mana"}, -1));
			System::Windows::Forms::ListViewItem^  listViewItem5 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {L"", 
				L"Automated channel"}, -1));
			System::Windows::Forms::ListViewItem^  listViewItem6 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {L"", 
				L"Automated skill"}, -1));
			System::Windows::Forms::ListViewGroup^  listViewGroup3 = (gcnew System::Windows::Forms::ListViewGroup(L"Monster", System::Windows::Forms::HorizontalAlignment::Center));
			System::Windows::Forms::ListViewGroup^  listViewGroup4 = (gcnew System::Windows::Forms::ListViewGroup(L"Player", System::Windows::Forms::HorizontalAlignment::Center));
			System::Windows::Forms::ListViewGroup^  listViewGroup5 = (gcnew System::Windows::Forms::ListViewGroup(L"Map", System::Windows::Forms::HorizontalAlignment::Center));
			System::Windows::Forms::ListViewItem^  listViewItem7 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {L"", 
				L"Kami"}, -1));
			System::Windows::Forms::ListViewItem^  listViewItem8 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {L"", 
				L"Godmode"}, -1));
			System::Windows::Forms::ListViewItem^  listViewItem9 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {L"", 
				L"Fusion attack"}, -1));
			System::Windows::Forms::ListViewItem^  listViewItem10 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {L"", 
				L"Item filter"}, -1));
			System::Windows::Forms::ListViewItem^  listViewItem11 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {L"", 
				L"Background filter"}, -1));
			System::Windows::Forms::ListViewItem^  listViewItem12 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {L"", 
				L"GND & Unlimited MP"}, -1));
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->listView2 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->listView3 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader6 = (gcnew System::Windows::Forms::ColumnHeader());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->removeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->tabPage2->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->contextMenuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->listView2);
			this->tabPage2->Cursor = System::Windows::Forms::Cursors::Default;
			this->tabPage2->Location = System::Drawing::Point(4, 19);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(161, 201);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Macro";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// listView2
			// 
			this->listView2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->listView2->CheckBoxes = true;
			this->listView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->columnHeader3, this->columnHeader4});
			this->listView2->Cursor = System::Windows::Forms::Cursors::Hand;
			listViewGroup1->Header = L"General";
			listViewGroup1->HeaderAlignment = System::Windows::Forms::HorizontalAlignment::Center;
			listViewGroup1->Name = L"listViewGroup1";
			listViewGroup2->Header = L"Anti-Detection";
			listViewGroup2->HeaderAlignment = System::Windows::Forms::HorizontalAlignment::Center;
			listViewGroup2->Name = L"listViewGroup2";
			this->listView2->Groups->AddRange(gcnew cli::array< System::Windows::Forms::ListViewGroup^  >(2) {listViewGroup1, listViewGroup2});
			this->listView2->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::None;
			listViewItem1->Group = listViewGroup1;
			listViewItem1->StateImageIndex = 0;
			listViewItem2->Group = listViewGroup1;
			listViewItem2->StateImageIndex = 0;
			listViewItem3->Group = listViewGroup1;
			listViewItem3->StateImageIndex = 0;
			listViewItem4->Group = listViewGroup1;
			listViewItem4->StateImageIndex = 0;
			listViewItem5->Group = listViewGroup2;
			listViewItem5->StateImageIndex = 0;
			listViewItem6->Group = listViewGroup1;
			listViewItem6->StateImageIndex = 0;
			this->listView2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(6) {listViewItem1, listViewItem2, 
				listViewItem3, listViewItem4, listViewItem5, listViewItem6});
			this->listView2->Location = System::Drawing::Point(6, 6);
			this->listView2->Name = L"listView2";
			this->listView2->Scrollable = false;
			this->listView2->Size = System::Drawing::Size(149, 179);
			this->listView2->TabIndex = 0;
			this->listView2->UseCompatibleStateImageBehavior = false;
			this->listView2->View = System::Windows::Forms::View::Details;
			this->listView2->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &Form1::listView2_ItemCheck);
			// 
			// columnHeader3
			// 
			this->columnHeader3->Width = 19;
			// 
			// columnHeader4
			// 
			this->columnHeader4->Width = 130;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->listView1);
			this->tabPage1->Cursor = System::Windows::Forms::Cursors::Default;
			this->tabPage1->Location = System::Drawing::Point(4, 19);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(161, 191);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Cheat";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// listView1
			// 
			this->listView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->listView1->CheckBoxes = true;
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->columnHeader1, this->columnHeader2});
			this->listView1->Cursor = System::Windows::Forms::Cursors::Hand;
			listViewGroup3->Header = L"Monster";
			listViewGroup3->HeaderAlignment = System::Windows::Forms::HorizontalAlignment::Center;
			listViewGroup3->Name = L"listViewGroup1";
			listViewGroup4->Header = L"Player";
			listViewGroup4->HeaderAlignment = System::Windows::Forms::HorizontalAlignment::Center;
			listViewGroup4->Name = L"listViewGroup2";
			listViewGroup5->Header = L"Map";
			listViewGroup5->HeaderAlignment = System::Windows::Forms::HorizontalAlignment::Center;
			listViewGroup5->Name = L"listViewGroup3";
			this->listView1->Groups->AddRange(gcnew cli::array< System::Windows::Forms::ListViewGroup^  >(3) {listViewGroup3, listViewGroup4, 
				listViewGroup5});
			this->listView1->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::None;
			listViewItem7->Group = listViewGroup3;
			listViewItem7->StateImageIndex = 0;
			listViewItem7->Tag = L"";
			listViewItem8->Group = listViewGroup4;
			listViewItem8->StateImageIndex = 0;
			listViewItem8->Tag = L"";
			listViewItem9->Group = listViewGroup4;
			listViewItem9->StateImageIndex = 0;
			listViewItem9->Tag = L"";
			listViewItem10->Group = listViewGroup5;
			listViewItem10->StateImageIndex = 0;
			listViewItem10->Tag = L"";
			listViewItem11->Group = listViewGroup5;
			listViewItem11->StateImageIndex = 0;
			listViewItem12->Group = listViewGroup4;
			listViewItem12->StateImageIndex = 0;
			this->listView1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(6) {listViewItem7, listViewItem8, 
				listViewItem9, listViewItem10, listViewItem11, listViewItem12});
			this->listView1->Location = System::Drawing::Point(6, 6);
			this->listView1->MultiSelect = false;
			this->listView1->Name = L"listView1";
			this->listView1->Scrollable = false;
			this->listView1->Size = System::Drawing::Size(149, 179);
			this->listView1->TabIndex = 0;
			this->listView1->TabStop = false;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			this->listView1->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &Form1::listView1_ItemCheck);
			// 
			// columnHeader1
			// 
			this->columnHeader1->Width = 19;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Width = 130;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->tabControl1->ItemSize = System::Drawing::Size(55, 15);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->Padding = System::Drawing::Point(9, 3);
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(169, 214);
			this->tabControl1->SizeMode = System::Windows::Forms::TabSizeMode::Fixed;
			this->tabControl1->TabIndex = 0;
			this->tabControl1->TabStop = false;
			this->tabControl1->Selecting += gcnew System::Windows::Forms::TabControlCancelEventHandler(this, &Form1::tabControl1_Selecting);
			this->tabControl1->Enter += gcnew System::EventHandler(this, &Form1::tabControl1_Enter);
			this->tabControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::tabControl1_MouseDown);
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->textBox1);
			this->tabPage3->Controls->Add(this->button1);
			this->tabPage3->Controls->Add(this->listView3);
			this->tabPage3->Location = System::Drawing::Point(4, 19);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(161, 201);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Sift";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(10, 163);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(120, 20);
			this->textBox1->TabIndex = 1;
			this->textBox1->TabStop = false;
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->toolTip1->SetToolTip(this->textBox1, L"Enter item here.");
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::textBox1_KeyPress);
			// 
			// button1
			// 
			this->button1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button1.Image")));
			this->button1->Location = System::Drawing::Point(136, 163);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(20, 20);
			this->button1->TabIndex = 2;
			this->button1->TabStop = false;
			this->toolTip1->SetToolTip(this->button1, L"Add item.");
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// listView3
			// 
			this->listView3->AutoArrange = false;
			this->listView3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->listView3->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->columnHeader5, this->columnHeader6});
			this->listView3->Cursor = System::Windows::Forms::Cursors::Default;
			this->listView3->FullRowSelect = true;
			this->listView3->GridLines = true;
			this->listView3->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::None;
			this->listView3->HideSelection = false;
			this->listView3->LabelWrap = false;
			this->listView3->Location = System::Drawing::Point(5, 7);
			this->listView3->Name = L"listView3";
			this->listView3->ShowGroups = false;
			this->listView3->Size = System::Drawing::Size(149, 150);
			this->listView3->TabIndex = 0;
			this->listView3->TabStop = false;
			this->toolTip1->SetToolTip(this->listView3, L"Item list.");
			this->listView3->UseCompatibleStateImageBehavior = false;
			this->listView3->View = System::Windows::Forms::View::Details;
			// 
			// columnHeader5
			// 
			this->columnHeader5->Width = 1;
			// 
			// columnHeader6
			// 
			this->columnHeader6->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->columnHeader6->Width = 129;
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->removeToolStripMenuItem, 
				this->clearToolStripMenuItem});
			this->contextMenuStrip1->Name = L"contextMenuStrip2";
			this->contextMenuStrip1->Size = System::Drawing::Size(118, 48);
			// 
			// removeToolStripMenuItem
			// 
			this->removeToolStripMenuItem->Name = L"removeToolStripMenuItem";
			this->removeToolStripMenuItem->Size = System::Drawing::Size(117, 22);
			this->removeToolStripMenuItem->Text = L"Remove";
			this->removeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::removeToolStripMenuItem_Click);
			// 
			// clearToolStripMenuItem
			// 
			this->clearToolStripMenuItem->Name = L"clearToolStripMenuItem";
			this->clearToolStripMenuItem->Size = System::Drawing::Size(117, 22);
			this->clearToolStripMenuItem->Text = L"Clear";
			this->clearToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::clearToolStripMenuItem_Click);
			// 
			// button2
			// 
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->Location = System::Drawing::Point(12, 241);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(169, 20);
			this->button2->TabIndex = 2;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// Form1
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(193, 238);
			this->ControlBox = false;
			this->Controls->Add(this->button2);
			this->Controls->Add(this->tabControl1);
			this->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(209, 314);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(209, 276);
			this->Name = L"Form1";
			this->Opacity = 0.9;
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MSB";
			this->tabPage2->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->contextMenuStrip1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void tabControl1_Selecting(System::Object^  sender, System::Windows::Forms::TabControlCancelEventArgs^  e);
private: System::Void tabControl1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		 {
			 ActiveControl = tabControl1->SelectedTab; 
		 }
private: System::Void tabControl1_Enter(System::Object^  sender, System::EventArgs^  e)
		 {
			 ActiveControl = tabControl1->SelectedTab;
		 }
private: System::Void listView1_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e);
private: System::Void listView2_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e);
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
		 {
			 if(!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
				 e->Handled = true;
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void removeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void clearToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
};
}
