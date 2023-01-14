#include "WarningForm.h"

void Test3::WarningForm::repeated_plan_name()
{
	this->state = PLAN_NAME_REPEAT;
	this->button1->Text = "Изменить имя";
	this->button2->Text = "Перезаписать";
	this->label1->Text = "У вас уже есть планировка и таким названием. Хоитие изменить имя, или перезаписать старую планировку?";
}

void Test3::WarningForm::didnt_saved_drawing()
{
	this->state = DIDNT_SAVED_DRAWING;
	this->button1->Text = "Сохранить";
	this->button2->Text = "Выйти";
	this->label1->Text = "Вы хотите закрыть планировку, не сохранив ее. Сохранить ее?";
}

void Test3::WarningForm::no_doors()
{
	this->state = NO_DOORS;
	this->button1->Text = "Сохранить";
	this->button2->Text = "Поставить двери";
	this->label1->Text = "Вы хотите сохранить планировку не поставив ни одной двери. Сохранить ее?";
}

System::Void Test3::WarningForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->state == PLAN_NAME_REPEAT)
	{
		((ScaleChooseForm^)this->Owner)->replace_or_change(false);
		this->Owner->Enabled = true;
		this->Close();
	}
	else if (this->state == DIDNT_SAVED_DRAWING)
	{
		((NewDrawingForm^)this->Owner)->save_drawing(true);
		this->Owner->Enabled = true;
		this->Owner->Close();
	}
	else if (this->state == NO_DOORS)
	{
		((NewDrawingForm^)this->Owner)->save_drawing(true);
		this->Owner->Enabled = true;
		this->Close();
	}

}

System::Void Test3::WarningForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->state == PLAN_NAME_REPEAT)
	{
		((ScaleChooseForm^)this->Owner)->replace_or_change(true);
		this->Owner->Enabled = true;
		this->state = WARNED;
		this->Close();
	}
	else if (this->state == DIDNT_SAVED_DRAWING)
	{
		((NewDrawingForm^)this->Owner)->save_drawing(false);
		this->Owner->Enabled = true;
		this->Owner->Close();
	}
	else if (this->state == NO_DOORS)
	{
		((NewDrawingForm^)this->Owner)->save_drawing(false);
		this->Owner->Enabled = true;
		this->state = WARNED;
		this->Close();
	}
}
