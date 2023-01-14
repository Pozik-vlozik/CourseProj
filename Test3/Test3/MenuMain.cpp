#include "MenuMain.h"
#include "ScaleChooseForm.h"

using namespace System;
using namespace Test3;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MenuMain);
	return 0;
}

System::Void Test3::MenuMain::create_new_drawing_but_Click(System::Object^ sender, System::EventArgs^ e)
{
	ScaleChooseForm^ ins = gcnew ScaleChooseForm();
	MenuMain::Hide();
	ins->Owner = this;
	ins->Show();
}

System::Void Test3::MenuMain::load_drawing_but_Click(System::Object^ sender, System::EventArgs^ e)
{
	DrawingLoadChoose^ ins = gcnew DrawingLoadChoose();
	MenuMain::Hide();
	ins->Owner = this;
	ins->Show();
}
