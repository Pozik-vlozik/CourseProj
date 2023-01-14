#pragma once
#include "MenuMain.h"
#include "DrawHelper.h"
#include "WarningForm.h"
#include "Planer.h"
#include <fstream>
#include <Windows.h>
using namespace std;


// For rooms magneting
enum
{
	NO_INTERSECT,
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};


// Statements
enum
{
	ROOM_LOCATING,
	ITEMS_POSITIONING,
	ITEM_PICKED,
	WALL_ITEM_PICKED
};


namespace Test3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для NewDrawingForm
	/// </summary>
	public ref class NewDrawingForm : public System::Windows::Forms::Form
	{
	public:
		NewDrawingForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~NewDrawingForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ exit;
	private: System::Windows::Forms::TextBox^ room_length;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ continue_planing;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ room_height;
	private: System::Windows::Forms::PictureBox^ pb_workplace;
	private: System::Windows::Forms::Label^ state_display;
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->exit = (gcnew System::Windows::Forms::Button());
			this->room_length = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->continue_planing = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->room_height = (gcnew System::Windows::Forms::TextBox());
			this->pb_workplace = (gcnew System::Windows::Forms::PictureBox());
			this->state_display = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_workplace))->BeginInit();
			this->SuspendLayout();
			// 
			// exit
			// 
			this->exit->Location = System::Drawing::Point(1184, 726);
			this->exit->Name = L"exit";
			this->exit->Size = System::Drawing::Size(75, 32);
			this->exit->TabIndex = 0;
			this->exit->Text = L"Выход";
			this->exit->UseVisualStyleBackColor = true;
			this->exit->Click += gcnew System::EventHandler(this, &NewDrawingForm::exit_Click);
			// 
			// room_length
			// 
			this->room_length->Location = System::Drawing::Point(97, 31);
			this->room_length->Name = L"room_length";
			this->room_length->Size = System::Drawing::Size(85, 22);
			this->room_length->TabIndex = 1;
			this->room_length->Text = L"4";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->continue_planing);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->room_height);
			this->groupBox1->Controls->Add(this->room_length);
			this->groupBox1->Location = System::Drawing::Point(1093, 66);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 151);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Комната";
			// 
			// continue_planing
			// 
			this->continue_planing->Location = System::Drawing::Point(24, 93);
			this->continue_planing->Name = L"continue_planing";
			this->continue_planing->Size = System::Drawing::Size(156, 35);
			this->continue_planing->TabIndex = 5;
			this->continue_planing->Text = L"Продолжить";
			this->continue_planing->UseVisualStyleBackColor = true;
			this->continue_planing->Click += gcnew System::EventHandler(this, &NewDrawingForm::continue_planing_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 31);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(74, 17);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Длина (м)";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 65);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(82, 17);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Ширина (м)";
			// 
			// room_height
			// 
			this->room_height->Location = System::Drawing::Point(97, 65);
			this->room_height->Name = L"room_height";
			this->room_height->Size = System::Drawing::Size(84, 22);
			this->room_height->TabIndex = 2;
			this->room_height->Text = L"4";
			// 
			// pb_workplace
			// 
			this->pb_workplace->Location = System::Drawing::Point(12, 12);
			this->pb_workplace->Name = L"pb_workplace";
			this->pb_workplace->Size = System::Drawing::Size(1079, 746);
			this->pb_workplace->TabIndex = 3;
			this->pb_workplace->TabStop = false;
			this->pb_workplace->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &NewDrawingForm::pb_workplace_MouseDown);
			// 
			// state_display
			// 
			this->state_display->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->state_display->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->state_display->Location = System::Drawing::Point(1103, 9);
			this->state_display->Name = L"state_display";
			this->state_display->Size = System::Drawing::Size(156, 54);
			this->state_display->TabIndex = 4;
			this->state_display->Text = L"Размещение комнат";
			// 
			// NewDrawingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1287, 770);
			this->Controls->Add(this->state_display);
			this->Controls->Add(this->pb_workplace);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->exit);
			this->Name = L"NewDrawingForm";
			this->Text = L"NewDrawingForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &NewDrawingForm::NewDrawingForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &NewDrawingForm::NewDrawingForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_workplace))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	public:

		double scale;
		String^ drawing_name;

		bool open_for_loading;
		bool finish_locating_rooms;
		bool redraw_old_drawing;
		int load_plan_number;

		void save_drawing(bool save);

		void save_without_doors(bool save);

	protected:

		int STATE;
		bool plan_saved;

		String^ path_to_icons;
		String^ path_to_names;

		Planer^ main_planer;

		const int pixels_in_santimeter = 43.5;

		DrawHelper^ drAss;
		List<Room^>^ rooms;

		List<String^>^ items_description;

		List<Items^>^ room_items;
		List<Items^>^ menu_room_items;
		PictureBox^ cur_pb;
		bool item_is_rotated;

		GroupBox^ items_locating_gb;		

		int cell_size;
		int border_thick;
		int pictures_amount;
		int room_item_amount;
		int pen_width;
		int magnet_delta;

		Color pb_default;
		Color pb_hover;
		Color pb_mooving;
		Color background_color;
		Color grid_color;

		bool moovable;
		MyPoint cur_point;
		MyPoint magnet_point;
		int cur_magn_side;
		PictureBox^ magneted_pb;

		void draw_main_markup(int cell_size);
		void draw_border(PictureBox^ pb, int board_thick, Color board_color, Color back_color);

		PictureBox^ add_picture_box(int x, int y, double pb_width, double pb_height);
		void remove_pb_from_rooms(PictureBox^ pb);
		void select_picture_box(PictureBox^ pb);
		void flipp_pb(PictureBox^ pb);
		void add_title(Room^ room);

		void finish_locating();
		void items_positioning();
		void delete_room_events();
		void add_positioning_events();
		void initialise_list_descr();
		void finish_planning();
		void clear_items();
		void saving_warning();
		void save_drawing();
		bool are_there_any_doors();

		void redraw_room(Room^ room, Color border_color);
		void redraw_rooms(Color border_color);

		void pb_unhook(PictureBox^ pb, int x_over_form, int y_over_form);
		Image^ get_item_image(int item_index);
		PictureBox^ create_static_item(int item_index, int x, int y);
		System::Drawing::Size get_item_size(int item_type);
		int get_item_index(PictureBox^ pb, List<Items^>^ list);
		int get_room_index(PictureBox^ pb, List<Room^>^ list);

		int intersect_side(PictureBox^ pb);
		void room_deleted(PictureBox^ pb);

		bool rooms_connected_check();

		/*  On FromLoad = true  */

		void load_planing();
		void locate_loaded_items();
		void locate_room(Room^ room);


	private: System::Void NewDrawingForm_Load(System::Object^ sender, System::EventArgs^ e)
	{
		this->path_to_icons = "icons\\";
		this->path_to_names = "..\\Plannings\\";
		this->plan_saved = false;

		this->drAss = gcnew DrawHelper();
		this->rooms = gcnew List<Room^>;
		this->items_description = gcnew List<String^>;

		this->border_thick = 2;
		this->pictures_amount = 0;
		this->pen_width = 3;
		this->STATE = ROOM_LOCATING;

		this->pb_default = Color::Blue;
		this->pb_hover = Color::Green;
		this->pb_mooving = Color::Purple;
		this->background_color = Color::FromArgb(91, 119, 143);
		this->grid_color = Color::FromArgb(202, 208, 219);


		initialise_list_descr();

		if (this->open_for_loading)
		{
			load_planing();
		}
		
		this->room_items = gcnew List<Items^>;
		this->menu_room_items = gcnew List<Items^>;

		this->room_item_amount = 9;

		this->magnet_delta = 20;
		this->cur_magn_side = NO_INTERSECT;
		this->magnet_point.set(-1);
		this->item_is_rotated = false;

		this->cell_size = this->pixels_in_santimeter;
		this->moovable = false;
		this->finish_locating_rooms = false;

		draw_main_markup(this->cell_size / this->scale);
	}

	private: System::Void NewDrawingForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
	{
		this->Owner->Show();
	}

	private: System::Void exit_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (this->STATE != ITEM_PICKED && this->STATE != WALL_ITEM_PICKED)
		{
			if (this->plan_saved)
			{
				this->Close();
			}
			else
			{
				saving_warning();
			}
		}
		else
		{
			MessageBox::Show("Сначала поставте взятую вещь", "Руки заняты");
		}		
	}
	
	public: System::Void pb_workplace_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) 
	{
		if (this->STATE == ROOM_LOCATING)
		{
			double pb_width = int(Convert::ToDouble(this->room_length->Text) * 100 + 0.5) / 100.0;
			double pb_height = int(Convert::ToDouble(this->room_height->Text) * 100 + 0.5) / 100.0;

			PictureBox^ pb = add_picture_box(e->X, e->Y, pb_width, pb_height);
			this->Controls->Add(pb);
			this->pb_workplace->SendToBack();
			this->rooms->Add(gcnew Room(pb, this->rooms->Count, pb_width, pb_height));

			redraw_room(this->rooms[get_room_index(pb, this->rooms)], this->pb_default);
		}
	}


	/*	Room events on LOCATING state  */

	public: System::Void pictureBox_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (this->STATE == ROOM_LOCATING)
		{
			select_picture_box((PictureBox^)sender);
			this->cur_point.set(e->X, e->Y);
			this->moovable = true;
			redraw_room(this->rooms[get_room_index((PictureBox^)sender, this->rooms)], this->pb_mooving);
		}
	}
	
	public: System::Void pictureBox_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (this->STATE == ROOM_LOCATING)
		{
			this->moovable = false;
			int index = get_room_index((PictureBox^)sender, this->rooms);
			if (index != -1)
			{
				redraw_room(this->rooms[index], this->pb_hover);
				if (this->magneted_pb != nullptr)
				{
					if (this->magnet_point == MyPoint(-1, -1))
					{
						this->rooms[index]->kill_neighbour(this->magneted_pb);
						this->rooms[get_room_index(this->magneted_pb, this->rooms)]->kill_neighbour(this->rooms[index]->pb);
					}
					else
					{
						this->rooms[index]->add_neighbour(this->magneted_pb, this->rooms[get_room_index(this->magneted_pb, this->rooms)]->room_number);
						this->rooms[get_room_index(this->magneted_pb, this->rooms)]->add_neighbour(this->rooms[index]->pb, this->rooms[index]->room_number);
					}
				}
			}
		}
	}
	
	public: System::Void pictureBox_MouseHover(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->STATE == ROOM_LOCATING)
		{
			redraw_room(this->rooms[get_room_index((PictureBox^)sender, this->rooms)], this->pb_hover);
		}
	}
	
	public: System::Void pictureBox_MouseLeave(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->STATE == ROOM_LOCATING)
		{
			redraw_room(this->rooms[get_room_index((PictureBox^)sender, this->rooms)], this->pb_default);
		}
	}
	
	public: System::Void pictureBox_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (this->STATE == ROOM_LOCATING)
		{
			if (this->moovable)
			{
				int x_over_form = Cursor->Position.X - this->Location.X - 8;
				int y_over_form = Cursor->Position.Y - this->Location.Y - 32;

				this->cur_magn_side = intersect_side((PictureBox^)sender);

				switch (this->cur_magn_side)
				{
				case RIGHT:

					((PictureBox^)sender)->Top += (y_over_form)-(this->cur_point.y + ((PictureBox^)sender)->Top);
					((PictureBox^)sender)->Left = this->magneted_pb->Location.X + this->magneted_pb->ClientSize.Width;
					this->magnet_point.set(this->magneted_pb->Location.X + this->magneted_pb->ClientSize.Width + this->cur_point.x, y_over_form);

					if (abs(this->magnet_point.x - x_over_form) > this->magnet_delta * 2)
					{
						pb_unhook((PictureBox^)sender, x_over_form, y_over_form);
					}
					break;
				case BOTTOM:

					((PictureBox^)sender)->Top = this->magneted_pb->Location.Y + this->magneted_pb->ClientSize.Height;
					((PictureBox^)sender)->Left += (x_over_form)-(this->cur_point.x + ((PictureBox^)sender)->Left);
					this->magnet_point.set(x_over_form, this->magneted_pb->Location.Y + this->magneted_pb->ClientSize.Height + this->cur_point.y);

					if (abs(this->magnet_point.y - y_over_form) > this->magnet_delta * 2)
					{
						pb_unhook((PictureBox^)sender, x_over_form, y_over_form);
					}
					break;
				case LEFT:
					((PictureBox^)sender)->Top += (y_over_form)-(this->cur_point.y + ((PictureBox^)sender)->Top);
					((PictureBox^)sender)->Left = this->magneted_pb->Location.X - ((PictureBox^)sender)->ClientSize.Width;
					this->magnet_point.set(this->magneted_pb->Location.X - ((PictureBox^)sender)->ClientSize.Width + this->cur_point.x, y_over_form);

					if (abs(this->magnet_point.x - x_over_form) > this->magnet_delta * 2)
					{
						pb_unhook((PictureBox^)sender, x_over_form, y_over_form);
					}
					break;
				case TOP:
					((PictureBox^)sender)->Top = this->magneted_pb->Location.Y - ((PictureBox^)sender)->ClientSize.Height;
					((PictureBox^)sender)->Left += (x_over_form)-(this->cur_point.x + ((PictureBox^)sender)->Left);
					this->magnet_point.set(x_over_form, this->magneted_pb->Location.Y - ((PictureBox^)sender)->ClientSize.Height + this->cur_point.y);

					if (abs(this->magnet_point.y - y_over_form) > this->magnet_delta * 2)
					{
						pb_unhook((PictureBox^)sender, x_over_form, y_over_form);
					}
					break;
				case NO_INTERSECT:
					this->cur_magn_side = intersect_side((PictureBox^)sender);
					((PictureBox^)sender)->Left += (x_over_form)-(this->cur_point.x + ((PictureBox^)sender)->Left);
					((PictureBox^)sender)->Top += (y_over_form)-(this->cur_point.y + ((PictureBox^)sender)->Top);
					this->magnet_point.set(-1);
					break;
				}
			}
		}
	}
	
	public: System::Void pictureBox_DoubleClick(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->STATE == ROOM_LOCATING)
		{
			room_deleted((PictureBox^)sender);
			this->Controls->Remove((PictureBox^)sender);
			remove_pb_from_rooms((PictureBox^)sender);
			for (int i = 0; i < this->rooms->Count; i++)
			{
				this->rooms[i]->room_number = i;
			}
			this->drAss->errase_picture_box((PictureBox^)sender);
			redraw_rooms(this->pb_default);
			delete (PictureBox^)sender;
		}

		/*for (int i = 0; i < this->rooms[get_room_index((PictureBox^)sender, this->rooms)]->neighbours->Count; i++)
		{
			draw_border(this->rooms[get_room_index((PictureBox^)sender, this->rooms)]->neighbours[i], 2, Color::Red, Color::Transparent);
		}*/
	}

	/*	Room events on LOCATING state  */



	/*	Item locating events  */

	private: System::Void itemBox_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->STATE != ITEM_PICKED && this->STATE != WALL_ITEM_PICKED)
		{
			int current_item_index = get_item_index((PictureBox^)sender, this->menu_room_items);
			int current_item_id = this->menu_room_items[current_item_index]->item_id;

			PictureBox^ pb = gcnew PictureBox();
			pb->Name = L"PictureBox" + Convert::ToString(current_item_id);
			pb->Location = System::Drawing::Point(Cursor->Position.X - this->Location.X - 8, Cursor->Position.Y - this->Location.Y - 32);
			
			pb->Size = System::Drawing::Size(get_item_size(current_item_id));
			pb->Image = get_item_image(current_item_id);
			pb->SizeMode = PictureBoxSizeMode::StretchImage;
			pb->MouseMove += gcnew MouseEventHandler(this, &NewDrawingForm::itemBox_MouseMove);
			this->room_items->Add(gcnew Items(pb, gcnew MyPoint(), current_item_id, this->item_is_rotated));

			this->Controls->Add(pb);
			pb->BringToFront();

			this->cur_pb = pb;

			if (current_item_id == WINDOW || current_item_id == DOORWAY)
			{
				this->STATE = WALL_ITEM_PICKED;
			}
			else
			{
				this->STATE = ITEM_PICKED;
			}
		}
		else
		{
			MessageBox::Show("Сначала поставте взятую вещь", "Руки заняты");
		}
	}

	private: System::Void itemBox_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (this->STATE == ITEM_PICKED || this->STATE == WALL_ITEM_PICKED)
		{
			this->cur_pb->Left += (Cursor->Position.X - this->Location.X) - this->cur_pb->Left - 8 + 1;
			this->cur_pb->Top += (Cursor->Position.Y - this->Location.Y) - this->cur_pb->Top - 32 + 1;
		}
	}

	private: System::Void itemBox_MouseMove_room(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (this->STATE == ITEM_PICKED)
		{
			this->cur_pb->Left += (Cursor->Position.X - this->Location.X) - this->cur_pb->Left - 8 + 1;
			this->cur_pb->Top += (Cursor->Position.Y - this->Location.Y) - this->cur_pb->Top - 32 + 1;
		}
		else if (this->STATE == WALL_ITEM_PICKED)
		{
			bool left = e->X < ((PictureBox^)sender)->Width / 2 ? true : false;
			bool top = e->Y < ((PictureBox^)sender)->Height / 2 ? true : false;

			int left_len = left ? e->X : ((PictureBox^)sender)->Width - e->X;
			int top_len = top ? e->Y : ((PictureBox^)sender)->Height - e->Y;

			bool left_or_top = left_len < top_len;

			if (left_or_top && left)
			{
				if (this->item_is_rotated)
				{
					flipp_pb(this->cur_pb);
				}
				this->cur_pb->Left = ((PictureBox^)sender)->Location.X;
				this->cur_pb->Top += (Cursor->Position.Y - this->Location.Y) - this->cur_pb->Top - 32 - this->cur_pb->Height / 2;
			}
			else if (left_or_top && !left)
			{
				if (this->item_is_rotated)
				{
					flipp_pb(this->cur_pb);
				}
				this->cur_pb->Left = ((PictureBox^)sender)->Location.X + ((PictureBox^)sender)->Width - this->cur_pb->Width;
				this->cur_pb->Top += (Cursor->Position.Y - this->Location.Y) - this->cur_pb->Top - 32 - this->cur_pb->Height / 2;
			}
			else if (!left_or_top && top)
			{
				if (!this->item_is_rotated)
				{
					flipp_pb(this->cur_pb);
				}
				this->cur_pb->Left += (Cursor->Position.X - this->Location.X) - this->cur_pb->Left - 8;
				this->cur_pb->Top = ((PictureBox^)sender)->Location.Y;
			}
			else if (!left_or_top && !top)
			{
				if (!this->item_is_rotated)
				{
					flipp_pb(this->cur_pb);
				}
				this->cur_pb->Left += (Cursor->Position.X - this->Location.X) - this->cur_pb->Left - 8;
				this->cur_pb->Top = ((PictureBox^)sender)->Location.Y + ((PictureBox^)sender)->Height - this->cur_pb->Height;
			}
		}
	}

	private: System::Void itemBox_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (this->STATE == ITEM_PICKED)
		{
			int room_type = this->rooms[get_room_index((PictureBox^)sender, this->rooms)]->get_area_type();
			int item_type = get_item_area_type(this->room_items[get_item_index((this->cur_pb), this->room_items)]->item_id);

			if (item_type != NEUTRAL_AREA && room_type != NEUTRAL_AREA)
			{
				if (item_type != room_type)
				{
					MessageBox::Show("Нельзя поставить выбранную вещь в данной комнате", "Неверное размещение");
					this->item_is_rotated = false;
					this->STATE = ITEMS_POSITIONING;
					this->Controls->Remove(this->cur_pb);
					return;
				}
			}
			int cur_ind = get_room_index((PictureBox^)sender, this->rooms);
			this->rooms[cur_ind]->add_item(this->cur_pb, gcnew MyPoint(e->X + 1, e->Y + 1), this->room_items[get_item_index(this->cur_pb, this->room_items)]->item_id, this->item_is_rotated);

			this->STATE = ITEMS_POSITIONING;
			this->Controls->Remove(this->cur_pb);

			redraw_room(this->rooms[get_room_index((PictureBox^)sender, this->rooms)], Color::Black);
		}
		else if (this->STATE == WALL_ITEM_PICKED)
		{
			Graphics^ g = Graphics::FromImage(((PictureBox^)sender)->Image);
			int cur_ind = get_room_index((PictureBox^)sender, this->rooms);

			this->rooms[cur_ind]->add_item(this->cur_pb, gcnew MyPoint(this->cur_pb->Location.X - ((PictureBox^)sender)->Location.X, this->cur_pb->Location.Y - ((PictureBox^)sender)->Location.Y), this->room_items[get_item_index(this->cur_pb, this->room_items)]->item_id, this->item_is_rotated);
			
			this->STATE = ITEMS_POSITIONING;
			this->Controls->Remove(this->cur_pb);
			this->item_is_rotated = false;

			redraw_room(this->rooms[get_room_index((PictureBox^)sender, this->rooms)], Color::Black);
		}
	}

	private: System::Void delete_itemBox_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->item_is_rotated = false;
		this->STATE = ITEMS_POSITIONING;
		this->Controls->Remove(this->cur_pb);
	}

	/*	Item locating events  */



	private: System::Void clear_items_Click(System::Object^ sender, System::EventArgs^ e)
	{
		clear_items();
	}

	private: System::Void finish_planing_Click(System::Object^ sender, System::EventArgs^ e)
	{
		finish_planning();
	}

	private: System::Void NewDrawingForm_EnabledChanged(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->finish_locating_rooms = true)
		{
			finish_locating();
		}
	}

	private: System::Void continue_planing_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (this->STATE == ROOM_LOCATING)
		{
			if (rooms_connected_check())
			{
				if (this->rooms->Count == 0)
				{
					MessageBox::Show("Вы ничего не поставили", "Что продолжать то?");
					return;
				}
				this->STATE = ITEMS_POSITIONING;
				finish_locating();
				this->groupBox1->Visible = false;
				if (this->items_locating_gb == nullptr)
				{
					add_positioning_events();
					items_positioning();
				}
				else
				{
					this->items_locating_gb->Visible = true;
				}
				redraw_rooms(Color::Black);
				this->state_display->Text = "Расстановка мебели";
			}
			else
			{
				MessageBox::Show("Сначала соедините все комнаты!", "Не все комнаты соединены");
			}
		}
	}
	
	private: System::Void back_to_locating_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->STATE != ITEMS_POSITIONING)
		{
			MessageBox::Show("Сначала поставте предмет", "Руки заняты");
			return;
		}
		redraw_rooms(this->pb_default);
		this->STATE = ROOM_LOCATING;
		this->state_display->Text = "Размещение комнат";
		this->items_locating_gb->Visible = false;
		this->groupBox1->Visible = true;
	}
};
}
