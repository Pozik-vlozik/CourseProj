#pragma once
#include <Windows.h>
#include "MyPoint.h"
using namespace System;
using namespace System::IO;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::ComponentModel;
using namespace System::Collections::Generic;

ref struct DrawKit
{
	PictureBox^ pb;
	SolidBrush^ brush;
	Pen^ pen;
	Bitmap^ bm;
	Color back_color;
	Font^ font;
	int pen_width;

	DrawKit(PictureBox^ pb)
	{
		set_all(pb, Color::Black, Color::Transparent, Color::Black, 1);
	}

	DrawKit(PictureBox^ pb, Font^ font)
	{
		set_all(pb, Color::Black, Color::Black, Color::Transparent, 1);
		this->font = gcnew Font(font->FontFamily, 3);
	}

	DrawKit(PictureBox^ pb, Color back_color)
	{
		set_all(pb, Color::Black, Color::Black, back_color, 1);
	}

	DrawKit(PictureBox^ pb, Color pen_color, Color brush_color)
	{
		set_all(pb, pen_color, brush_color, Color::Black, 1);
	}

	DrawKit(PictureBox^ pb, Color pen_color, Color brush_color, Color back_color, int pen_width)
	{
		set_all(pb, pen_color, brush_color, back_color, pen_width);
	}

	DrawKit(const DrawKit% other)
	{
		set_all(other.pb, other.pen->Color, other.brush->Color, other.back_color, other.pen_width);
	}

	void set_all(PictureBox^ pb, Color pen_color, Color brush_color, Color back_color, int pen_width)
	{
		this->brush = gcnew SolidBrush(brush_color);
		this->font = gcnew Font(FontFamily::GenericSansSerif, 12.0F);
		this->pen = gcnew Pen(pen_color);
		this->bm = gcnew Bitmap(pb->Width, pb->Height);
		this->back_color = back_color;
		this->pen_width = pen_width;
		this->pb = pb;
	}
};


ref class DrawHelper
{

private:

	List<DrawKit^>^ draw_kits;

	static int pictures_amount = 0;

	void add_element(DrawKit^ kit, PictureBox^ pb);


	void draw_circle_private(int x, int y, int rad, PictureBox^ pb, Color pen_color, Color brush_color);

	void paint_back_private(PictureBox^ pb, Color back_color);

	void draw_rect_private(int x1, int y1, int x2, int y2, PictureBox^ pb, Color pen_color, Color brush_color);

	void draw_line_private(int x1, int y1, int x2, int y2, PictureBox^ pb, Color pen_color, int pen_width);

	void draw_string_private(PictureBox^ pb, int index, String^ str, int x, int y, FontFamily^ ff, float em_size, FontStyle fs);


	/* Не графические инструменты */

	int get_draw_kit_index(PictureBox^ pb);

	void delete_draw_kit(int index);

	void delete_draw_kit(PictureBox^ pb);

	int try_to_add_picture_box(PictureBox^ pb);


public:

	DrawHelper();

	DrawHelper(PictureBox^ pb, Color back_color);

	DrawHelper(PictureBox^ pb, Color pen_color, Color brush_color, Color back_color, int pen_width);

	~DrawHelper();

	/* Не графические инструменты */

	void errase_picture_box(PictureBox^ pb);


	/* Помощь в рисовании */

	void draw_circle(int x, int y, int rad, PictureBox^ pb);

	void draw_circle(int x, int y, int rad, PictureBox^ pb, Color pen_color, Color brush_color);


	void draw_rect(int x1, int y1, int x2, int y2, PictureBox^ pb);

	void draw_rect(int x1, int y1, int x2, int y2, PictureBox^ pb, Color pen_color, Color brush_color);

	void draw_rect(int x1, int y1, int x2, int y2, Bitmap^ bm, Color pen_color, Color brush_color, int pen_width);


	void draw_line(int x1, int y1, int x2, int y2, PictureBox^ pb);

	void draw_line(int x1, int y1, int x2, int y2, PictureBox^ pb, Color pen_color, int pen_width);
	
	void draw_line(MyPoint p1, MyPoint p2, PictureBox^ pb);

	void draw_line(MyPoint p1, MyPoint p2, PictureBox^ pb, Color pen_color, int pen_width);

	void draw_line(MyPoint^ p1, MyPoint^ p2, PictureBox^ pb);

	void draw_line(MyPoint^ p1, MyPoint^ p2, PictureBox^ pb, Color pen_color, int pen_width);


	/* Работа с цветами */

	void set_brush_color(PictureBox^ pb, Color back_color);

	void set_pen_color(PictureBox^ pb, Color brush_color);

	void set_pen_width(PictureBox^ pb, int pen_width);

	void set_back_color(PictureBox^ pb, Color back_color);

	void set_bitmap(PictureBox^ pb, Bitmap^ bm);


	/* Для заднего фона */

	void paint_back(PictureBox^ pb);

	void paint_back(PictureBox^ pb, Color back_color);


	/* Вывод текста */

	void draw_string(PictureBox^ pb, String^ str, int x, int y);

	void draw_string(PictureBox^ pb, String^ str, int x, int y, FontStyle fs);

	void draw_string(PictureBox^ pb, String^ str, int x, int y, float em_size, FontStyle fs);

	void draw_string(PictureBox^ pb, String^ str, int x, int y, Font^ font);

	
	void clear_bitmap(PictureBox^ pb);

	void clear_bitmap(PictureBox^ pb, Color back_color);

};
