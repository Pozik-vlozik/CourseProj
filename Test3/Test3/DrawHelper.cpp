#include "DrawHelper.h"


/* Конструкторы */

DrawHelper::DrawHelper()
{
	this->draw_kits = gcnew List<DrawKit^>;
	PictureBox^ pb = gcnew PictureBox;
	pb->Width = 1;
	pb->Height = 1;
	add_element(gcnew DrawKit(pb, Color::Black), pb);
}

DrawHelper::DrawHelper(PictureBox^ pb, Color back_color)
{
	this->draw_kits = gcnew List<DrawKit^>;	
	add_element(gcnew DrawKit(pb, back_color), pb);
}

DrawHelper::DrawHelper(PictureBox^ pb, Color pen_color, Color brush_color, Color back_color, int pen_width)
{
	this->draw_kits = gcnew List<DrawKit^>;
	add_element(gcnew DrawKit(pb, pen_color, brush_color, back_color, pen_width), pb);
}

DrawHelper::~DrawHelper()
{
	int size = this->draw_kits->Count;
	for (int i = 0; i < size; i++)
	{
		delete this->draw_kits[i]->bm;
		delete this->draw_kits[i]->brush;
		delete this->draw_kits[i]->pen;
	}
	delete[] this->draw_kits;
	this->pictures_amount = 0;
}

/* Конструкторы */


void DrawHelper::add_element(DrawKit^ kit, PictureBox^ pb)
{
	this->draw_kits->Add(kit);
	this->pictures_amount++;
}



/* Не графические инструменты */

int DrawHelper::get_draw_kit_index(PictureBox^ pb)
{
	for (int i = 0; i < this->draw_kits->Count; i++)
	{
		if (draw_kits[i]->pb == pb)
		{
			return i;
		}
	}
	return -1;
}

void DrawHelper::delete_draw_kit(int index)
{
	delete this->draw_kits[index]->font;
	delete this->draw_kits[index]->brush;
	delete this->draw_kits[index]->pen;
	delete this->draw_kits[index]->bm;
	this->draw_kits->RemoveAt(index);
}

void DrawHelper::delete_draw_kit(PictureBox^ pb)
{
	delete_draw_kit(get_draw_kit_index(pb));
}

int DrawHelper::try_to_add_picture_box(PictureBox^ pb)
{
	int index = get_draw_kit_index(pb);
	if (index == -1)
	{
		add_element(gcnew DrawKit(pb), pb);
		index = get_draw_kit_index(pb);
	}
	return index;
}


void DrawHelper::errase_picture_box(PictureBox^ pb)
{
	delete_draw_kit(pb);
}

/* Не графические инструменты */



/* Помощь в рисовании */

void DrawHelper::draw_circle_private(int x, int y, int rad, PictureBox^ pb, Color pen_color, Color brush_color)
{
	int index = try_to_add_picture_box(pb);
	
	Graphics^ g = Graphics::FromImage(this->draw_kits[index]->bm);

	Pen^ p = gcnew Pen(pen_color);
	p->Width = this->draw_kits[index]->pen_width;
	SolidBrush^ b = gcnew SolidBrush(brush_color);

	g->DrawEllipse(p, x - rad / 2, y - rad / 2, rad, rad);
	g->FillEllipse(b, x - rad / 2, y - rad / 2, rad, rad);

	delete p;
	delete b;

	pb->Image = this->draw_kits[index]->bm;
}

void DrawHelper::draw_circle(int x, int y, int rad, PictureBox^ pb)
{
	int index = try_to_add_picture_box(pb);

	draw_circle_private(x, y, rad, pb, this->draw_kits[index]->pen->Color, this->draw_kits[index]->brush->Color);
}

void DrawHelper::draw_circle(int x, int y, int rad, PictureBox^ pb, Color pen_color, Color brush_color)
{
	draw_circle_private(x, y, rad, pb, pen_color, brush_color);
}


void DrawHelper::draw_rect_private(int x1, int y1, int x2, int y2, PictureBox^ pb, Color pen_color, Color brush_color)
{
	int index = try_to_add_picture_box(pb);

	Graphics^ g = Graphics::FromImage(this->draw_kits[index]->bm);

	Pen^ p = gcnew Pen(pen_color);
	p->Width = this->draw_kits[index]->pen_width;
	SolidBrush^ b = gcnew SolidBrush(brush_color);

	g->DrawRectangle(p, x1, y1, x2 - x1, y2 - y1);
	g->FillRectangle(b, x1, y1, x2 - x1, y2 - y1);

	delete p;
	delete b;

	pb->Image = this->draw_kits[index]->bm;
}

void DrawHelper::draw_rect(int x1, int y1, int x2, int y2, PictureBox^ pb)
{
	int index = try_to_add_picture_box(pb);
	draw_rect_private(x1, y1, x2, y2, pb, this->draw_kits[index]->pen->Color, this->draw_kits[index]->brush->Color);
}

void DrawHelper::draw_rect(int x1, int y1, int x2, int y2, PictureBox^ pb, Color pen_color, Color brush_color)
{
	draw_rect_private(x1, y1, x2, y2, pb, pen_color, brush_color);
}

void DrawHelper::draw_rect(int x1, int y1, int x2, int y2, Bitmap^ bm, Color pen_color, Color brush_color, int pen_width)
{
	Graphics^ g = Graphics::FromImage(bm);

	Pen^ p = gcnew Pen(pen_color);
	p->Width = pen_width;
	SolidBrush^ b = gcnew SolidBrush(brush_color);

	g->DrawRectangle(p, x1, y1, x2 - x1, y2 - y1);
	g->FillRectangle(b, x1, y1, x2 - x1, y2 - y1);

	delete p;
	delete b;
}


void DrawHelper::draw_line_private(int x1, int y1, int x2, int y2, PictureBox^ pb, Color pen_color, int pen_width)
{
	int index = try_to_add_picture_box(pb);

	Graphics^ g = Graphics::FromImage(this->draw_kits[index]->bm);

	Pen^ p = gcnew Pen(pen_color);
	p->Width = pen_width;

	g->DrawLine(p, x1, y1, x2, y2);
	delete p;

	pb->Image = this->draw_kits[index]->bm;
}

void DrawHelper::draw_line(int x1, int y1, int x2, int y2, PictureBox^ pb)
{
	int index = try_to_add_picture_box(pb);

	draw_line_private(x1, y1, x2, y2, pb, this->draw_kits[index]->pen->Color, this->draw_kits[index]->pen->Width);
}

void DrawHelper::draw_line(int x1, int y1, int x2, int y2, PictureBox^ pb, Color pen_color, int pen_width)
{
	draw_line_private(x1, y1, x2, y2, pb, pen_color, pen_width);
}

void DrawHelper::draw_line(MyPoint p1, MyPoint p2, PictureBox^ pb)
{
	int index = try_to_add_picture_box(pb);

	draw_line_private(p1.x, p1.y, p2.x, p2.y, pb, this->draw_kits[index]->pen->Color, this->draw_kits[index]->pen->Width);
}

void DrawHelper::draw_line(MyPoint p1, MyPoint p2, PictureBox^ pb, Color pen_color, int pen_width)
{
	draw_line_private(p1.x, p1.y, p2.x, p2.y, pb, pen_color, pen_width);
}

void DrawHelper::draw_line(MyPoint^ p1, MyPoint^ p2, PictureBox^ pb)
{
	int index = try_to_add_picture_box(pb);

	draw_line_private(p1->x, p1->y, p2->x, p2->y, pb, this->draw_kits[index]->pen->Color, this->draw_kits[index]->pen->Width);
}

void DrawHelper::draw_line(MyPoint^ p1, MyPoint^ p2, PictureBox^ pb, Color pen_color, int pen_width)
{
	draw_line_private(p1->x, p1->y, p2->x, p2->y, pb, pen_color, pen_width);
}

/* Помощь в рисовании */



/* Для заднего фона */

void DrawHelper::paint_back_private(PictureBox^ pb, Color back_color)
{
	int index = try_to_add_picture_box(pb);

	Graphics^ g = Graphics::FromImage(this->draw_kits[index]->bm);
	SolidBrush^ b = gcnew SolidBrush(back_color);
	g->FillRectangle(b, 0, 0, pb->Width, pb->Height);
	pb->Image = this->draw_kits[index]->bm;

	delete b;
}

void DrawHelper::paint_back(PictureBox^ pb)
{
	int index = try_to_add_picture_box(pb);

	paint_back_private(pb, this->draw_kits[index]->back_color);
}

void DrawHelper::paint_back(PictureBox^ pb, Color back_color)
{
	paint_back_private(pb, back_color);
}


/* Для заднего фона */



/* Работа с цветами */

void DrawHelper::set_pen_color(PictureBox^ pb, Color pen_color)
{
	int index = try_to_add_picture_box(pb);
	this->draw_kits[index]->pen->Color = pen_color;
}

void DrawHelper::set_pen_width(PictureBox^ pb, int pen_width)
{
	int index = try_to_add_picture_box(pb);
	this->draw_kits[index]->pen->Width = pen_width;
	this->draw_kits[index]->pen_width = pen_width;
}

void DrawHelper::set_brush_color(PictureBox^ pb, Color brush_color)
{
	int index = try_to_add_picture_box(pb);
	this->draw_kits[index]->brush->Color = brush_color;
}

void DrawHelper::set_back_color(PictureBox^ pb, Color back_color)
{
	int index = try_to_add_picture_box(pb);
	this->draw_kits[index]->back_color = back_color;
}

void DrawHelper::set_bitmap(PictureBox^ pb, Bitmap^ bm)
{
	int index = try_to_add_picture_box(pb);
	this->draw_kits[index]->bm = bm;
}

/* Работа с цветами */



/* Вывод текста */

void DrawHelper::draw_string_private(PictureBox^ pb, int index, String^ str, int x, int y, FontFamily^ ff, float em_size, FontStyle fs)
{
	Graphics^ g = Graphics::FromImage(this->draw_kits[index]->bm);

	Font^ font = gcnew Font(ff, em_size, fs);
	g->DrawString(str, font, this->draw_kits[index]->brush, x, y);
	pb->Image = this->draw_kits[index]->bm;
}


void DrawHelper::draw_string(PictureBox^ pb, String^ str, int x, int y)
{
	int index = get_draw_kit_index(pb);
	draw_string_private(pb, index, str, x, y, this->draw_kits[index]->font->FontFamily, this->draw_kits[index]->font->Size, this->draw_kits[index]->font->Style);
}

void DrawHelper::draw_string(PictureBox^ pb, String^ str, int x, int y, FontStyle fs)
{
	int index = get_draw_kit_index(pb);
	draw_string_private(pb, index, str, x, y, this->draw_kits[index]->font->FontFamily, this->draw_kits[index]->font->Size, fs);
}

void DrawHelper::draw_string(PictureBox^ pb, String^ str, int x, int y, float em_size, FontStyle fs)
{
	int index = get_draw_kit_index(pb);
	draw_string_private(pb, index, str, x, y, this->draw_kits[index]->font->FontFamily, em_size, fs);
}

void DrawHelper::draw_string(PictureBox^ pb, String^ str, int x, int y, Font^ font)
{
	int index = get_draw_kit_index(pb);
	Graphics^ g = Graphics::FromImage(this->draw_kits[index]->bm);

	g->DrawString(str, font, this->draw_kits[index]->brush, x, y);

	pb->Image = this->draw_kits[index]->bm;
}

/* Вывод текста */



void DrawHelper::clear_bitmap(PictureBox^ pb)
{
	int index = get_draw_kit_index(pb);

	if (index == -1)
	{
		return;
	}

	Graphics^ g = Graphics::FromImage(this->draw_kits[index]->bm);
	g->Clear(this->draw_kits[index]->back_color);
	pb->Image = this->draw_kits[index]->bm;
}

void DrawHelper::clear_bitmap(PictureBox^ pb, Color back_color)
{
	int index = get_draw_kit_index(pb);

	if (index == -1)
	{
		return;
	}

	Graphics^ g = Graphics::FromImage(this->draw_kits[index]->bm);
	g->Clear(back_color);
	pb->Image = this->draw_kits[index]->bm;
}
