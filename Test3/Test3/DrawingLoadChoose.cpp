#include "DrawingLoadChoose.h"


System::Void Test3::DrawingLoadChoose::dataGridView1_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
	NewDrawingForm^ ins = gcnew NewDrawingForm();
	ins->Owner = this->Owner;
	ins->drawing_name = this->dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value->ToString();
	ins->open_for_loading = true;
	ins->redraw_old_drawing = true;
	this->Hide();
	ins->Show();
}
