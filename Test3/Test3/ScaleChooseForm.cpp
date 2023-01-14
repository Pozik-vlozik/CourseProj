#include "ScaleChooseForm.h"
#include "NewDrawingForm.h"

using namespace System;
using namespace Test3;


int WINAPI WinMain1(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew ScaleChooseForm);
	return 0;
}

System::Void Test3::ScaleChooseForm::create_Click(System::Object^ sender, System::EventArgs^ e)
{
	NewDrawingForm^ ins = gcnew NewDrawingForm;
	ins->redraw_old_drawing = false;

	String^ drawing_name = this->textBox2->Text;
	fstream file;
	file.open("..\\Plannings\\Plannings names.txt");
	if (!file.is_open())
	{
		MessageBox::Show("Ошибка в открытии файла", "Что-то не так");
		this->Close();
	}
	else
	{
		while (!file.eof())
		{
			char buf[255];
			file.getline(buf, sizeof(buf));
			if (file.eof())
			{
				break;
			}
			if (char_to_string(buf) == drawing_name)
			{
				this->was_warning = false;
				WarningForm^ warn = gcnew WarningForm;
				warn->repeated_plan_name();
				warn->Owner = this;
				warn->Show();
				this->Enabled = false;
				return;
			}
		}
	}
	ins->open_for_loading = false;
	ins->Owner = this->Owner;
	ins->scale = Convert::ToDouble(this->textBox1->Text);
	ins->drawing_name = gcnew String(this->textBox2->Text);
	ins->Show();
	this->Close();
}

void Test3::ScaleChooseForm::replace_or_change(int replace)
{
	this->is_replace = replace;
	this->was_warning = true;
}

System::Void Test3::ScaleChooseForm::ScaleChooseForm_EnabledChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (this->was_warning)
	{
		if (this->is_replace)
		{
			NewDrawingForm^ ins = gcnew NewDrawingForm;
			ins->redraw_old_drawing = true;
			ins->open_for_loading = false;
			ins->Owner = this->Owner;
			ins->scale = Convert::ToDouble(this->textBox1->Text);
			ins->drawing_name = gcnew String(this->textBox2->Text);
			ins->Show();
			this->Close();
		}
	}
}