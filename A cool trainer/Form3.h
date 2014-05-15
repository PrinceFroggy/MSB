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
	/// Summary for Form3
	/// </summary>
	public ref class Form3 : public System::Windows::Forms::Form
	{
	public:
		Form3(void)
		{
			InitializeComponent();

			ActiveControl = panel1;

			SendMessage((HWND)textBox1->Handle.ToPointer(), EM_SETCUEBANNER, (WPARAM)FALSE, (LPARAM)L"Enter unformatted packet to inject here...");
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
				case HTBOTTOM:
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
		~Form3()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 


	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  receiveToolStripMenuItem;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::ToolStripMenuItem^  spamToolStripMenuItem;
	private: System::Windows::Forms::Panel^  panel1;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form3::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->receiveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->spamToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->contextMenuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(382, 20);
			this->textBox1->TabIndex = 1;
			this->toolTip1->SetToolTip(this->textBox1, L"Enter packet here.");
			// 
			// button1
			// 
			this->button1->ContextMenuStrip = this->contextMenuStrip1;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button1.Image")));
			this->button1->Location = System::Drawing::Point(400, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(32, 20);
			this->button1->TabIndex = 2;
			this->toolTip1->SetToolTip(this->button1, L"Inject packet.");
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form3::button1_Click);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->receiveToolStripMenuItem, 
				this->spamToolStripMenuItem});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(115, 48);
			// 
			// receiveToolStripMenuItem
			// 
			this->receiveToolStripMenuItem->CheckOnClick = true;
			this->receiveToolStripMenuItem->Name = L"receiveToolStripMenuItem";
			this->receiveToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->receiveToolStripMenuItem->Text = L"Receive";
			this->receiveToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form3::receiveToolStripMenuItem_Click);
			// 
			// spamToolStripMenuItem
			// 
			this->spamToolStripMenuItem->CheckOnClick = true;
			this->spamToolStripMenuItem->Name = L"spamToolStripMenuItem";
			this->spamToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->spamToolStripMenuItem->Text = L"Spam";
			this->spamToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form3::spamToolStripMenuItem_Click);
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(420, 20);
			this->panel1->TabIndex = 3;
			// 
			// Form3
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(444, 44);
			this->ControlBox = false;
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->panel1);
			this->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(460, 82);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(460, 82);
			this->Name = L"Form3";
			this->Opacity = 0.9;
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"Packets";
			this->contextMenuStrip1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void spamToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void receiveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 ActiveControl = panel1;
		 }
};
}
