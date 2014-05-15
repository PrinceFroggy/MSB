#include "Form2.h"
#include "Macro.h"

using namespace Acooltrainer;

#pragma region Variables

int nTemp;
int nIndex;

#pragma endregion

#pragma region Functions

void GetKey()
{
	switch(nIndex)
	{
	case 0:
		nTemp = 0x30;
		break;
	case 1:
		nTemp = 0x31;
		break;
	case 2:
		nTemp = 0x32;
		break;
	case 3:
		nTemp = 0x33;
		break;
	case 4:
		nTemp = 0x34;
		break;
	case 5:
		nTemp = 0x35;
		break;
	case 6:
		nTemp = 0x36;
		break;
	case 7:
		nTemp = 0x37;
		break;
	case 8:
		nTemp = 0x38;
		break;
	case 9:
		nTemp = 0x39;
		break;
	case 10:
		nTemp = 0x41;
		break;
	case 11:
		nTemp = 0x42;
		break;
	case 12:
		nTemp = 0x43;
		break;
	case 13:
		nTemp = 0x44;
		break;
	case 14:
		nTemp = 0x45;
		break;
	case 15:
		nTemp = 0x46;
		break;
	case 16:
		nTemp = 0x47;
		break;
	case 17:
		nTemp = 0x48;
		break;
	case 18:
		nTemp = 0x49;
		break;
	case 19:
		nTemp = 0x4A;
		break;
	case 20:
		nTemp = 0x4B;
		break;
	case 21:
		nTemp = 0x4C;
		break;
	case 22:
		nTemp = 0x4D;
		break;
	case 23:
		nTemp = 0x4E;
		break;
	case 24:
		nTemp = 0x4F;
		break;
	case 25:
		nTemp = 0x50;
		break;
	case 26:
		nTemp = 0x51;
		break;
	case 27:
		nTemp = 0x52;
		break;
	case 28:
		nTemp = 0x53;
		break;
	case 29:
		nTemp = 0x54;
		break;
	case 30:
		nTemp = 0x55;
		break;
	case 31:
		nTemp = 0x56;
		break;
	case 32:
		nTemp = 0x57;
		break;
	case 33:
		nTemp = 0x58;
		break;
	case 34:
		nTemp = 0x59;
		break;
	case 35:
		nTemp = 0x5A;
		break;
	case 36:
		nTemp = 0x10;
		break;
	case 37:
		nTemp = 0x11;
		break;
	case 38:
		nTemp = 0x12;
		break;
	case 39:
		nTemp = 0x21;
		break;
	case 40:
		nTemp = 0x22;
		break;
	case 41:
		nTemp = 0x23;
		break;
	case 42:
		nTemp = 0x24;
		break;
	case 43:
		nTemp = 0x2D;
		break;
	case 44:
		nTemp = 0x2E;
	}
	KeyAvailable(nTemp);
}

#pragma endregion

#pragma region Form Events

void Form2::comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = groupBox1;

	ClearKey(0);

	nIndex = comboBox1->SelectedIndex;
	
	GetKey();
	
	if (KeyAvailable(nTemp))
	{
		AssignKey(0, nTemp);
	}
	else
	{
		::MessageBox(0, "Key is already assigned.", "Failed to assign key.", MB_OK | MB_ICONERROR);

		comboBox1->SelectedIndexChanged -= gcnew System::EventHandler(this, &Form2::comboBox1_SelectedIndexChanged);

		comboBox1->SelectedIndex = -1;

		comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form2::comboBox1_SelectedIndexChanged);
	}
}

void Form2::comboBox2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = groupBox1;

	ClearKey(1);

	nIndex = comboBox2->SelectedIndex;
	
	GetKey();
	
	if (KeyAvailable(nTemp))
	{
		AssignKey(1, nTemp);
	}
	else
	{
		::MessageBox(0, "Key is already assigned.", "Failed to assign key.", MB_OK | MB_ICONERROR);

		comboBox2->SelectedIndexChanged -= gcnew System::EventHandler(this, &Form2::comboBox2_SelectedIndexChanged);

		comboBox2->SelectedIndex = -1;

		comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &Form2::comboBox2_SelectedIndexChanged);
	}
}

void Form2::comboBox3_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = groupBox1;

	ClearKey(2);

	nIndex = comboBox3->SelectedIndex;
	
	GetKey();
	
	if (KeyAvailable(nTemp))
	{
		AssignKey(2, nTemp);
	}
	else
	{
		::MessageBox(0, "Key is already assigned.", "Failed to assign key.", MB_OK | MB_ICONERROR);

		comboBox3->SelectedIndexChanged -= gcnew System::EventHandler(this, &Form2::comboBox3_SelectedIndexChanged);

		comboBox3->SelectedIndex = -1;

		comboBox3->SelectedIndexChanged += gcnew System::EventHandler(this, &Form2::comboBox3_SelectedIndexChanged);
	}
}

void Form2::comboBox4_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = groupBox1;

	ClearKey(3);

	nIndex = comboBox4->SelectedIndex;
	
	GetKey();
	
	if (KeyAvailable(nTemp))
	{
		AssignKey(3, nTemp);
	}
	else
	{
		::MessageBox(0, "Key is already assigned.", "Failed to assign key.", MB_OK | MB_ICONERROR);

		comboBox4->SelectedIndexChanged -= gcnew System::EventHandler(this, &Form2::comboBox4_SelectedIndexChanged);

		comboBox4->SelectedIndex = -1;

		comboBox4->SelectedIndexChanged += gcnew System::EventHandler(this, &Form2::comboBox4_SelectedIndexChanged);
	}
}

void Form2::comboBox5_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = groupBox1;

	ClearKey(4);

	nIndex = comboBox5->SelectedIndex;
	
	GetKey();
	
	if (KeyAvailable(nTemp))
	{
		AssignKey(4, nTemp);
	}
	else
	{
		::MessageBox(0, "Key is already assigned.", "Failed to assign key.", MB_OK | MB_ICONERROR);

		comboBox5->SelectedIndexChanged -= gcnew System::EventHandler(this, &Form2::comboBox5_SelectedIndexChanged);

		comboBox5->SelectedIndex = -1;

		comboBox5->SelectedIndexChanged += gcnew System::EventHandler(this, &Form2::comboBox5_SelectedIndexChanged);
	}
}

void Form2::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = groupBox1;

	if (textBox1->Text != "")
	{
		AssignIntegers(0, Convert::ToInt32(textBox1->Text));
	}

	AssignKeyMethod(checkBox1->Checked);

	if (textBox2->Text != "")
	{
		AssignIntegers(1, Convert::ToInt32(textBox2->Text));
	}

	if (textBox3->Text != "")
	{
		AssignIntegers(2, Convert::ToInt32(textBox3->Text));
	}

	if (textBox4->Text != "")
	{
		AssignIntegers(3,  Convert::ToInt32(textBox4->Text) * 1000);
	}
}

#pragma endregion