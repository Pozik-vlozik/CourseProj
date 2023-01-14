#include "NewDrawingForm.h"

using namespace Test3;
using namespace System;

int WINAPI WinMain2(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew NewDrawingForm);
	return 0;
}

void Test3::NewDrawingForm::draw_main_markup(int cell_size)
{
	this->pb_workplace->BackColor = this->background_color;
	for (int i = 0; i < this->pb_workplace->ClientSize.Width; i += cell_size)
	{
		for (int j = 0; j < this->pb_workplace->ClientSize.Height; j += cell_size)
		{
			drAss->draw_line(i, 0, i, this->pb_workplace->ClientSize.Height, this->pb_workplace, this->grid_color, this->pen_width);
			drAss->draw_line(0, i, this->pb_workplace->ClientSize.Width, i, this->pb_workplace, this->grid_color, this->pen_width);
		}
	}
}

void Test3::NewDrawingForm::pb_unhook(PictureBox^ pb, int x_over_form, int y_over_form)
{
	pb->Top += (y_over_form)-(this->cur_point.y + pb->Top);
	pb->Left += (x_over_form)-(this->cur_point.x + pb->Left);
	this->magnet_point.set(-1);
	this->cur_magn_side = NO_INTERSECT;
}

PictureBox^ Test3::NewDrawingForm::add_picture_box(int x, int y, double pb_width, double pb_height)
{
	PictureBox^ pb = gcnew PictureBox();
	pb->Location = Point(x, y);
	pb->Size = System::Drawing::Size(pb_width * this->pixels_in_santimeter / this->scale, pb_height * this->pixels_in_santimeter / this->scale);
	pb->Image = gcnew Bitmap(pb->Size.Width, pb->Size.Height);
	pb->Name = L"PictureBox" + Convert::ToString(this->pictures_amount);
	pb->TabStop = false;
	pb->MouseHover += gcnew EventHandler(this, &NewDrawingForm::pictureBox_MouseHover);
	pb->MouseLeave += gcnew EventHandler(this, &NewDrawingForm::pictureBox_MouseLeave);
	pb->DoubleClick += gcnew EventHandler(this, &NewDrawingForm::pictureBox_DoubleClick);
	pb->MouseUp += gcnew MouseEventHandler(this, &NewDrawingForm::pictureBox_MouseUp);
	pb->MouseDown += gcnew MouseEventHandler(this, &NewDrawingForm::pictureBox_MouseDown);
	pb->MouseDown += gcnew MouseEventHandler(this, &NewDrawingForm::itemBox_MouseDown);
	pb->MouseMove += gcnew MouseEventHandler(this, &NewDrawingForm::pictureBox_MouseMove);
	pb->MouseMove += gcnew MouseEventHandler(this, &NewDrawingForm::itemBox_MouseMove_room);

	this->drAss->paint_back(pb, Color::White);
	this->pictures_amount++;
	return pb;
}

void Test3::NewDrawingForm::draw_border(PictureBox^ pb, int board_thick, Color board_color, Color back_color)
{
	drAss->set_pen_width(pb, board_thick * 2);
	drAss->draw_rect(board_thick, board_thick, pb->ClientSize.Width - board_thick, pb->ClientSize.Height - board_thick, pb, board_color, back_color);
}

void Test3::NewDrawingForm::remove_pb_from_rooms(PictureBox^ pb)
{
	for (int i = 0; i < this->rooms->Count; i++)
	{
		if (this->rooms[i]->pb == pb)
		{
			this->rooms->RemoveAt(i);
			return;
		}
	}
}

void Test3::NewDrawingForm::select_picture_box(PictureBox^ pb)
{
	pb->BringToFront();
}

void Test3::NewDrawingForm::flipp_pb(PictureBox^ pb)
{
	int width = pb->Width;
	pb->Width = pb->Height;
	pb->Height = width;
	pb->Image->RotateFlip(RotateFlipType::Rotate90FlipX);
	this->item_is_rotated = !this->item_is_rotated;
}

void Test3::NewDrawingForm::finish_locating()
{

	for (int i = 0; i < this->rooms->Count; i++)
	{
		draw_border(this->rooms[i]->pb, this->border_thick, Color::Black, Color::Transparent);
	}
	for (int i = 0; i < this->rooms->Count; i++)
	{
		add_title(this->rooms[i]);
	}
}

void Test3::NewDrawingForm::add_title(Room^ room)
{
	System::Drawing::Font^ font = gcnew System::Drawing::Font(FontFamily::GenericMonospace, 10.0F);

	int emSize = 12;
	double area_size = int(room->area * 100 + 0.5) / 100.0;
	String^ area = Convert::ToString(area_size);
	if (area_size < 2)
	{
		emSize = 8;
	}
	font = gcnew System::Drawing::Font("Coruer New", emSize);

	this->drAss->set_brush_color(room->pb, Color::Black);
	this->drAss->set_pen_color(room->pb, Color::Black);
	this->drAss->set_pen_width(room->pb, 1);

	this->drAss->draw_string(room->pb, Convert::ToString(room->width), (room->pb->ClientSize.Width - emSize) / 2, this->border_thick, font);
	this->drAss->draw_string(room->pb, Convert::ToString(room->height), this->border_thick, (room->pb->ClientSize.Height - emSize) / 2, font);
	this->drAss->draw_string(room->pb, area, (room->pb->ClientSize.Width - area->Length * emSize) / 2, room->pb->ClientSize.Height / 2 + 4, font);

	this->drAss->draw_line((room->pb->ClientSize.Width - area->Length * emSize) / 2, room->pb->ClientSize.Height / 2 + 5, (room->pb->ClientSize.Width + area->Length * emSize) / 2, room->pb->ClientSize.Height / 2 + 5, room->pb);

	this->drAss->set_brush_color(room->pb, Color::Red);
	this->drAss->set_pen_color(room->pb, Color::Red);
	this->drAss->draw_string(room->pb, Convert::ToString(room->room_number + 1), (room->pb->ClientSize.Width - emSize) / 2, room->pb->ClientSize.Height / 2 - emSize, font);
}

System::Drawing::Size Test3::NewDrawingForm::get_item_size(int item_type)
{
	if (item_type == BATH || item_type == VENTILATION)
	{
		return System::Drawing::Size(86, 32);
	}
	else if (item_type == WINDOW || item_type == DOORWAY)
	{
		return System::Drawing::Size(3, 31);
	}
	else
	{
		return System::Drawing::Size(35, 35);
	}
}

void Test3::NewDrawingForm::items_positioning()
{
	GroupBox^ gb = gcnew GroupBox;
	GroupBox^ living_gb = gcnew GroupBox;
	GroupBox^ nonliving_gb = gcnew GroupBox;
	GroupBox^ items_setting_gb = gcnew GroupBox;
	PictureBox^ ins;

	for (int i = 0; i < this->room_item_amount; i++)
	{
		switch (get_item_type(i))
		{
		case LIVING_ITEM:
			ins = create_static_item(i, 5, living_gb->Controls->Count * 40 + 20);
			living_gb->Controls->Add(ins);
			break;
		case NON_LIVING_ITEM:
			ins = create_static_item(i, 5, nonliving_gb->Controls->Count * 40 + 20);
			nonliving_gb->Controls->Add(ins);
			break;
		case NEUTRAL_ITEM:
			ins = create_static_item(i, 5, gb->Controls->Count * 40 + 20);
			gb->Controls->Add(ins);
			break;
		}
		ToolTip^ t = gcnew ToolTip;
		t->SetToolTip(ins, this->items_description[i]);
		ins->Click += gcnew EventHandler(this, &NewDrawingForm::itemBox_Click);

		this->menu_room_items->Add(gcnew Items(ins, gcnew MyPoint(), i, this->item_is_rotated));
	}

	living_gb->Location = System::Drawing::Point(0, 0);
	living_gb->Text = L"Жилые предметы";
	living_gb->Name = L"living_gb";
	living_gb->Size = System::Drawing::Size(120, living_gb->Controls->Count * 40 + 20);
	living_gb->TabStop = false;
	items_setting_gb->Controls->Add(living_gb);

	nonliving_gb->Location = System::Drawing::Point(0, living_gb->Controls->Count * 40 + 20);
	nonliving_gb->Text = L"Нежилые предметы";
	nonliving_gb->Name = L"nonliving_gb";
	nonliving_gb->Size = System::Drawing::Size(130, nonliving_gb->Controls->Count * 40 + 20);
	nonliving_gb->TabStop = false;
	items_setting_gb->Controls->Add(nonliving_gb);

	gb->Location = System::Drawing::Point(0, living_gb->Controls->Count * 40 + 20 + nonliving_gb->Controls->Count * 40 + 20);
	gb->Text = L"Общие предметы";
	gb->Name = L"gb";
	gb->Size = System::Drawing::Size(150, gb->Controls->Count * 40 + 20);
	gb->TabStop = false;
	items_setting_gb->Controls->Add(gb);

	PictureBox^ del_item = gcnew PictureBox;
	del_item->Location = System::Drawing::Point(0, living_gb->Controls->Count * 40 + 20 + nonliving_gb->Controls->Count * 40 + 20 + gb->Controls->Count * 40 + 20);
	del_item->Name = L"delItemPB";
	del_item->Size = System::Drawing::Size(35, 35);
	del_item->TabStop = false;
	del_item->Image = Image::FromFile(L"icons\\delete_item.jpg");
	del_item->SizeMode = PictureBoxSizeMode::StretchImage;
	del_item->Click += gcnew EventHandler(this, &NewDrawingForm::delete_itemBox_Click);
	items_setting_gb->Controls->Add(del_item);

	Button^ clear_but = gcnew Button;
	clear_but->Location = System::Drawing::Point(50, living_gb->Controls->Count * 40 + 20 + nonliving_gb->Controls->Count * 40 + 20 + gb->Controls->Count * 40 + 20);
	clear_but->Name = L"clear_items";
	clear_but->Size = System::Drawing::Size(75, 25);
	clear_but->TabIndex = 0;
	clear_but->Text = L"Очистить все";
	clear_but->UseVisualStyleBackColor = true;
	clear_but->Click += gcnew System::EventHandler(this, &NewDrawingForm::clear_items_Click);
	items_setting_gb->Controls->Add(clear_but);

	Button^ finish_but = gcnew Button;
	finish_but->Location = System::Drawing::Point(0, clear_but->Location.Y + 45);
	finish_but->Name = L"finish_planning";
	finish_but->Size = System::Drawing::Size(90, 25);
	finish_but->TabIndex = 0;
	finish_but->Text = L"Закончить планировку";
	finish_but->UseVisualStyleBackColor = true;
	finish_but->Click += gcnew System::EventHandler(this, &NewDrawingForm::finish_planing_Click);
	items_setting_gb->Controls->Add(finish_but);

	Button^ back_but = gcnew Button;
	back_but->Name = L"back_to_locating";
	back_but->Size = System::Drawing::Size(90, 25);
	back_but->Location = System::Drawing::Point(0, finish_but->Location.Y + 25);
	back_but->TabIndex = 0;
	back_but->Text = L"Назад";
	back_but->UseVisualStyleBackColor = true;
	back_but->Click += gcnew System::EventHandler(this, &NewDrawingForm::back_to_locating_Click);
	items_setting_gb->Controls->Add(back_but);

	items_setting_gb->Location = System::Drawing::Point(832, 62);
	items_setting_gb->Text = L"";
	items_setting_gb->Name = L"item_setting_gb";
	items_setting_gb->Size = System::Drawing::Size(130, back_but->Location.Y + back_but->Height);
	items_setting_gb->TabStop = false;
	this->Controls->Add(items_setting_gb);

	this->items_locating_gb = items_setting_gb;
}

void Test3::NewDrawingForm::delete_room_events()
{
	this->pb_workplace->MouseDown -= gcnew MouseEventHandler(this, &NewDrawingForm::pb_workplace_MouseDown);

	for (int i = 0; i < this->rooms->Count; i++)
	{
		this->rooms[i]->pb->MouseHover -= gcnew EventHandler(this, &NewDrawingForm::pictureBox_MouseHover);
		this->rooms[i]->pb->MouseLeave -= gcnew EventHandler(this, &NewDrawingForm::pictureBox_MouseLeave);
		this->rooms[i]->pb->DoubleClick -= gcnew EventHandler(this, &NewDrawingForm::pictureBox_DoubleClick);
		this->rooms[i]->pb->MouseUp -= gcnew MouseEventHandler(this, &NewDrawingForm::pictureBox_MouseUp);
		this->rooms[i]->pb->MouseDown -= gcnew MouseEventHandler(this, &NewDrawingForm::pictureBox_MouseDown);
		this->rooms[i]->pb->MouseMove -= gcnew MouseEventHandler(this, &NewDrawingForm::pictureBox_MouseMove);
	}
}

void Test3::NewDrawingForm::add_positioning_events()
{
	this->pb_workplace->MouseMove += gcnew MouseEventHandler(this, &NewDrawingForm::itemBox_MouseMove);

	for (int i = 0; i < this->rooms->Count; i++)
	{
		this->rooms[i]->pb->MouseMove += gcnew MouseEventHandler(this, &NewDrawingForm::itemBox_MouseMove_room);
		this->rooms[i]->pb->MouseDown += gcnew MouseEventHandler(this, &NewDrawingForm::itemBox_MouseDown);
	}
}

void Test3::NewDrawingForm::initialise_list_descr()
{
	this->items_description->Add("Электрическая плита");
	this->items_description->Add("Газовая плита");
	this->items_description->Add("Душевая кабинка");
	this->items_description->Add("Раковина");
	this->items_description->Add("Туалет");
	this->items_description->Add("Ванная");
	this->items_description->Add("Вентиляция");
	this->items_description->Add("Окно");
	this->items_description->Add("Дверь");
}

void Test3::NewDrawingForm::finish_planning()
{
	if (are_there_any_doors())
	{
		double living_area = 0, non_living_area = 0, total_area = 0;
		for (int i = 0; i < this->rooms->Count; i++)
		{
			if (this->rooms[i]->get_area_type() == LIVING_AREA)
			{
				living_area += this->rooms[i]->area;
			}
			if (this->rooms[i]->get_area_type() == NON_LIVING_AREA)
			{
				non_living_area += this->rooms[i]->area;
			}
			else
			{
				total_area += this->rooms[i]->area;
			}
		}
		total_area += living_area + non_living_area;
		MessageBox::Show("Жилая площадь: " + Convert::ToString( int(living_area * 100 + 0.5) / 100.0 ) + " m2" + "\nНежилая площадь: " + Convert::ToString( int(non_living_area * 100 + 0.5) / 100.0) + " m2" + "\nОбщая площадь: " + Convert::ToString( int(total_area * 100 + 0.5) / 100.0) + " m2");

		for (int i = 0; i < this->rooms->Count; i++)
		{
			this->rooms[i]->set_location();
		}
		save_drawing();
	}
	else
	{
		WarningForm^ warn = gcnew WarningForm;
		warn->Owner = this;
		warn->no_doors();
		warn->Show();
		this->Enabled = false;
	}
}	

void Test3::NewDrawingForm::save_without_doors(bool save)
{
	if (save)
	{
		save_drawing();
		this->plan_saved = true;
	}
}

void Test3::NewDrawingForm::save_drawing()
{
	this->main_planer = gcnew Planer(this->rooms, this->drawing_name, this->scale);
	ofstream file;
	if (!this->redraw_old_drawing)
	{
		if (!this->plan_saved)
		{
			file.open(string_to_char(this->path_to_names + Convert::ToString("Plannings names.txt")), ios_base::app);
			file << string_to_char(this->drawing_name + "\n");
			file.close();
		}
	}
	file.open(string_to_char(this->path_to_names + this->drawing_name + ".txt"));
	if (file.is_open())
	{
		file << this->main_planer;
		this->plan_saved = true;
	}
	else
	{
		MessageBox::Show("Ошибка в открытии файла сохранений", "Что-то не так");
	}
}

void Test3::NewDrawingForm::saving_warning()
{
	WarningForm^ warn = gcnew WarningForm;
	warn->Owner = this;
	warn->didnt_saved_drawing();
	warn->Show();
	this->Enabled = false;
}

void Test3::NewDrawingForm::save_drawing(bool save)
{
	if (save)
	{
		save_drawing();
	}
}

PictureBox^ Test3::NewDrawingForm::create_static_item(int item_index, int x, int y)
{
	PictureBox^ pb = gcnew PictureBox();

	pb->Name = L"ItemPictureBox" + Convert::ToString(item_index);
	pb->Location = System::Drawing::Point(x, y);
	pb->SizeMode = PictureBoxSizeMode::StretchImage;
	if (item_index == WINDOW || item_index == DOORWAY)
	{
		pb->Size = System::Drawing::Size(get_item_size(SINK));
		pb->SizeMode = PictureBoxSizeMode::CenterImage;
	}
	else
	{
		pb->Size = System::Drawing::Size(get_item_size(item_index));
	}
	pb->TabStop = false;
	pb->Image = get_item_image(item_index);

	return pb;
}

Image^ Test3::NewDrawingForm::get_item_image(int item_index)
{
	return Image::FromFile(this->path_to_icons + Convert::ToString(item_index) + ".jpg");
}

int Test3::NewDrawingForm::get_item_index(PictureBox^ pb, List<Items^>^ list)
{
	for (int i = 0; i < list->Count; i++)
	{
		if (list[i]->pb == pb)
		{
			return i;
		}
	}
	return -1;
}

int Test3::NewDrawingForm::get_room_index(PictureBox^ pb, List<Room^>^ list)
{
	for (int i = 0; i < list->Count; i++)
	{
		if (list[i]->pb == pb)
		{
			return i;
		}
	}
	return -1;
}	

void Test3::NewDrawingForm::room_deleted(PictureBox^ pb)
{
	for (int i = 0; i < this->rooms->Count; i++)
	{
		this->rooms[i]->kill_neighbour(pb);
	}
}

int Test3::NewDrawingForm::intersect_side(PictureBox^ pb)
{
	int delta_x, delta_y;

	for (int i = 0; i < this->rooms->Count; i++)
	{
		System::Drawing::Rectangle rect = System::Drawing::Rectangle(this->rooms[i]->pb->Location.X - this->magnet_delta, this->rooms[i]->pb->Location.Y - this->magnet_delta, this->rooms[i]->pb->Width + this->magnet_delta * 2, this->rooms[i]->pb->Height + this->magnet_delta * 2);
		if (pb != this->rooms[i]->pb && pb->Bounds.IntersectsWith(rect))
		{
			delta_x = pb->Location.X - rect.Location.X;
			delta_y = pb->Location.Y - rect.Location.Y;

			this->magneted_pb = this->rooms[i]->pb;

			if (delta_x > rect.Width - 2 * this->magnet_delta && abs(delta_y) < max(pb->Height, rect.Height))
			{
				return RIGHT;
			}
			else if (abs(delta_x) < max(pb->Width, rect.Width) && delta_y > rect.Height - 2 * this->magnet_delta)
			{
				return	BOTTOM;
			}
			else if (-(delta_x) > pb->Width - 2 * this->magnet_delta && abs(delta_y) < max(pb->Height, rect.Height))
			{
				return LEFT;
			}
			else if (abs(delta_x) < max(pb->Width, rect.Width) && -(delta_y) > pb->Height - 2 * this->magnet_delta)
			{
				return TOP;
			}
		}
	}
	return NO_INTERSECT;
}

void Test3::NewDrawingForm::clear_items()
{
	if (this->STATE == ITEM_PICKED || this->STATE == WALL_ITEM_PICKED)
	{
		MessageBox::Show("Сначала поставте предмет", "Руки заняты");
		return;
	}

	for (int i = 0; i < this->rooms->Count; i++)
	{
		this->rooms[i]->clear_items();

		redraw_room(this->rooms[i], Color::Black);

	}

}

void Test3::NewDrawingForm::redraw_room(Room^ room, Color border_color)
{
	System::Drawing::Size size;
	Bitmap^ bm = gcnew Bitmap(room->pb->Width, room->pb->Height);
	this->drAss->draw_rect(this->border_thick, this->border_thick, bm->Width - this->border_thick, bm->Height - this->border_thick, bm, border_color, Color::White, this->border_thick * 2);
	
	for (int i = 0; i < room->furniture->Count; i++)
	{
		int item_id = room->furniture[i]->item_id;
		Bitmap^ item = gcnew Bitmap(get_item_image(item_id));
		MyPoint^ pos = room->furniture[i]->position;
		size = get_item_size(item_id);
		if (room->furniture[i]->is_flipped)
		{
			item->RotateFlip(RotateFlipType::Rotate90FlipX);
			int width = size.Width;
			size.Width = size.Height;
			size.Height = width;
		}
		Graphics^ g = Graphics::FromImage(bm);
		g->DrawImage(item, System::Drawing::Rectangle(Point(pos->x, pos->y), size));
	}
	this->drAss->set_bitmap(room->pb, bm);
	add_title(room);
}

void Test3::NewDrawingForm::redraw_rooms(Color border_color)
{
	for (int i = 0; i < this->rooms->Count; i++)
	{
		redraw_room(this->rooms[i], border_color);
	}
}

bool Test3::NewDrawingForm::rooms_connected_check()
{
	if (this->rooms->Count < 2)
	{
		return true;
	}

	int connections = 0, amount;
	for (int i = 0; i < this->rooms->Count; i++)
	{
		amount = this->rooms[i]->get_neighbours_amount();
		if (amount == 0)
		{
			return false;
		}
		connections += amount;
	}
	if (connections < (this->rooms->Count - 2) * 2 + 2)
	{
		return false;
	}
	return true;
}

bool Test3::NewDrawingForm::are_there_any_doors()
{
	for (int i = 0; i < this->rooms->Count; i++)
	{
		for (int j = 0; j < this->rooms[i]->furniture->Count; j++)
		{
			if (this->rooms[i]->furniture[j]->item_id == DOORWAY)
			{
				return true;
			}
		}
	}
	return false;
}
	

/*  On FromLoad = true  */

void Test3::NewDrawingForm::load_planing()
{
	this->main_planer = gcnew Planer();

	ifstream file;
	file.open(string_to_char(this->path_to_names + this->drawing_name + ".txt"));
	if (file.is_open())
	{
		file >> this->main_planer;
	}
	else
	{
		MessageBox::Show("Ошибка при открытии файла", "Что-то не так");
	}
	file.close();
	this->scale = this->main_planer->get_scale();
	locate_loaded_items();
}

void Test3::NewDrawingForm::locate_loaded_items()
{
	this->rooms = this->main_planer->get_rooms();
	for (int i = 0; i < this->rooms->Count; i++)
	{
		locate_room(this->rooms[i]);
	}
	for (int i = 0; i < this->rooms->Count; i++)
	{
		for (int j = 0; j < this->rooms[i]->neightbours_numbers->Count; j++)
		{
			this->rooms[i]->add_neighbour(this->rooms[this->rooms[i]->neightbours_numbers[j]]->pb);
		}
	}
}

void Test3::NewDrawingForm::locate_room(Room^ room)
{
	room->pb = add_picture_box(room->location->x, room->location->y, room->width, room->height);
	redraw_room(room, this->pb_default);
	this->Controls->Add(room->pb);
	this->pb_workplace->SendToBack();
}