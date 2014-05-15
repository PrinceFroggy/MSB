#pragma once
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
	/// Summary for Form2
	/// </summary>
	public ref class Form2 : public System::Windows::Forms::Form
	{
	public:
		Form2(void)
		{
			InitializeComponent();

			ActiveControl = groupBox1;

			ComboBox_SetCueBannerText((HWND)comboBox1->Handle.ToPointer(), (LPARAM)L"Key...");
			ComboBox_SetCueBannerText((HWND)comboBox2->Handle.ToPointer(), (LPARAM)L"Key...");
			ComboBox_SetCueBannerText((HWND)comboBox3->Handle.ToPointer(), (LPARAM)L"Key...");
			ComboBox_SetCueBannerText((HWND)comboBox4->Handle.ToPointer(), (LPARAM)L"Key...");
			ComboBox_SetCueBannerText((HWND)comboBox5->Handle.ToPointer(), (LPARAM)L"Key...");

			SendMessage((HWND)textBox1->Handle.ToPointer(), EM_SETCUEBANNER, (WPARAM)FALSE, (LPARAM)L"Delay...");
			SendMessage((HWND)textBox2->Handle.ToPointer(), EM_SETCUEBANNER, (WPARAM)FALSE, (LPARAM)L"Value...");
			SendMessage((HWND)textBox3->Handle.ToPointer(), EM_SETCUEBANNER, (WPARAM)FALSE, (LPARAM)L"Value...");
			SendMessage((HWND)textBox4->Handle.ToPointer(), EM_SETCUEBANNER, (WPARAM)FALSE, (LPARAM)L"Delay...");
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
		~Form2()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  groupBox1;
	protected: 

	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;


	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::TextBox^  textBox2;


	private: System::Windows::Forms::ComboBox^  comboBox3;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::TextBox^  textBox3;


	private: System::Windows::Forms::ComboBox^  comboBox4;

	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::ComboBox^  comboBox5;
	private: System::ComponentModel::IContainer^  components;

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
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox5 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->checkBox1);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(144, 76);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Automated attack";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->checkBox1->Location = System::Drawing::Point(123, 49);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(15, 14);
			this->checkBox1->TabIndex = 1;
			this->toolTip1->SetToolTip(this->checkBox1, L"Check for hold method.");
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(6, 46);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(111, 20);
			this->textBox1->TabIndex = 1;
			this->toolTip1->SetToolTip(this->textBox1, L"Enter delay in miliseconds here.");
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form2::textBox1_KeyPress);
			// 
			// comboBox1
			// 
			this->comboBox1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(45) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
				L"8", L"9", L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", 
				L"T", L"U", L"V", L"W", L"X", L"Y", L"Z", L"SHIFT", L"CTRL", L"ALT", L"PAGE UP", L"PAGE DOWN", L"END", L"HOME", L"INS", L"DEL"});
			this->comboBox1->Location = System::Drawing::Point(6, 19);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(132, 21);
			this->comboBox1->TabIndex = 0;
			this->toolTip1->SetToolTip(this->comboBox1, L"Select key.");
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form2::comboBox1_SelectedIndexChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->comboBox2);
			this->groupBox2->Location = System::Drawing::Point(12, 94);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(144, 52);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Automated loot";
			// 
			// comboBox2
			// 
			this->comboBox2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(45) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
				L"8", L"9", L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", 
				L"T", L"U", L"V", L"W", L"X", L"Y", L"Z", L"SHIFT", L"CTRL", L"ALT", L"PAGE UP", L"PAGE DOWN", L"END", L"HOME", L"INS", L"DEL"});
			this->comboBox2->Location = System::Drawing::Point(6, 19);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(132, 21);
			this->comboBox2->TabIndex = 0;
			this->toolTip1->SetToolTip(this->comboBox2, L"Select key.");
			this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &Form2::comboBox2_SelectedIndexChanged);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->textBox2);
			this->groupBox3->Controls->Add(this->comboBox3);
			this->groupBox3->Location = System::Drawing::Point(12, 152);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(144, 76);
			this->groupBox3->TabIndex = 2;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Automated health";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(6, 46);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(132, 20);
			this->textBox2->TabIndex = 1;
			this->toolTip1->SetToolTip(this->textBox2, L"Enter value here.");
			this->textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form2::textBox2_KeyPress);
			// 
			// comboBox3
			// 
			this->comboBox3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(45) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
				L"8", L"9", L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", 
				L"T", L"U", L"V", L"W", L"X", L"Y", L"Z", L"SHIFT", L"CTRL", L"ALT", L"PAGE UP", L"PAGE DOWN", L"END", L"HOME", L"INS", L"DEL"});
			this->comboBox3->Location = System::Drawing::Point(6, 19);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(132, 21);
			this->comboBox3->TabIndex = 0;
			this->toolTip1->SetToolTip(this->comboBox3, L"Select key.");
			this->comboBox3->SelectedIndexChanged += gcnew System::EventHandler(this, &Form2::comboBox3_SelectedIndexChanged);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->textBox3);
			this->groupBox4->Controls->Add(this->comboBox4);
			this->groupBox4->Location = System::Drawing::Point(12, 234);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(144, 76);
			this->groupBox4->TabIndex = 3;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Automated mana";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(6, 46);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(132, 20);
			this->textBox3->TabIndex = 1;
			this->toolTip1->SetToolTip(this->textBox3, L"Enter value here.");
			this->textBox3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form2::textBox3_KeyPress);
			// 
			// comboBox4
			// 
			this->comboBox4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->comboBox4->FormattingEnabled = true;
			this->comboBox4->Items->AddRange(gcnew cli::array< System::Object^  >(45) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
				L"8", L"9", L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", 
				L"T", L"U", L"V", L"W", L"X", L"Y", L"Z", L"SHIFT", L"CTRL", L"ALT", L"PAGE UP", L"PAGE DOWN", L"END", L"HOME", L"INS", L"DEL"});
			this->comboBox4->Location = System::Drawing::Point(6, 19);
			this->comboBox4->Name = L"comboBox4";
			this->comboBox4->Size = System::Drawing::Size(132, 21);
			this->comboBox4->TabIndex = 0;
			this->toolTip1->SetToolTip(this->comboBox4, L"Select key.");
			this->comboBox4->SelectedIndexChanged += gcnew System::EventHandler(this, &Form2::comboBox4_SelectedIndexChanged);
			// 
			// button1
			// 
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->Location = System::Drawing::Point(12, 405);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(144, 20);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Assign keys";
			this->toolTip1->SetToolTip(this->button1, L"Save information.");
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form2::button1_Click);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(6, 46);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(132, 20);
			this->textBox4->TabIndex = 1;
			this->toolTip1->SetToolTip(this->textBox4, L"Enter delay in seconds here.");
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->textBox4);
			this->groupBox5->Controls->Add(this->comboBox5);
			this->groupBox5->Location = System::Drawing::Point(12, 316);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(144, 76);
			this->groupBox5->TabIndex = 5;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Automated skill";
			// 
			// comboBox5
			// 
			this->comboBox5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->comboBox5->FormattingEnabled = true;
			this->comboBox5->Items->AddRange(gcnew cli::array< System::Object^  >(45) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
				L"8", L"9", L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", 
				L"T", L"U", L"V", L"W", L"X", L"Y", L"Z", L"SHIFT", L"CTRL", L"ALT", L"PAGE UP", L"PAGE DOWN", L"END", L"HOME", L"INS", L"DEL"});
			this->comboBox5->Location = System::Drawing::Point(6, 19);
			this->comboBox5->Name = L"comboBox5";
			this->comboBox5->Size = System::Drawing::Size(132, 21);
			this->comboBox5->TabIndex = 0;
			this->comboBox5->SelectedIndexChanged += gcnew System::EventHandler(this, &Form2::comboBox5_SelectedIndexChanged);
			// 
			// Form2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(168, 404);
			this->ControlBox = false;
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(184, 475);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(184, 442);
			this->Name = L"Form2";
			this->Opacity = 0.9;
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"Settings";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
		 {
			 if(!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
				 e->Handled = true;
		 }
private: System::Void comboBox2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void textBox2_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
		 {
			 if(!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
				 e->Handled = true;
		 }
private: System::Void comboBox3_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void textBox3_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
		 {
			 if(!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
				 e->Handled = true;
		 }
private: System::Void comboBox4_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void comboBox5_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
};
}
