#pragma once
#include <Windows.h>
#include <fstream>
#include <iostream>
#include "help_funcs.h"
#include "DrawHelper.h"
#include "MyPoint.h"
using namespace std;

using namespace System;
using namespace System::IO;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

enum
{
	LIVING_AREA,
	NON_LIVING_AREA,
	NEUTRAL_AREA
};

enum
{
	LIVING_ITEM,
	NON_LIVING_ITEM,
	NEUTRAL_ITEM
};

enum
{
	ELECTRIC_OVEN,
	GAS_OVEN,
	SHOWER_CABIN,
	SINK,
	TOILET,
	BATH,
	VENTILATION,
	WINDOW,
	DOORWAY
};

int get_item_area_type(int item_number);

int get_item_type(int item_number);

void rotate_pb(PictureBox^ pb);



ref struct Items
{
	PictureBox^ pb;
	MyPoint^ position;
	int item_id;
	int item_type;
	bool is_flipped;

	Items() 
	{
		this->position = gcnew MyPoint();
	};

	Items(PictureBox^ pb, MyPoint^ position, int item_id, bool is_flipped)
	{
		this->pb = pb;
		this->item_id = item_id;
		this->is_flipped = is_flipped;
		this->item_type = get_item_type(item_id);
		this->position = position;
	}

	Items(MyPoint^ position, int item_id, bool is_flipped)
	{
		this->position = position;
		this->item_id = item_id;
		this->is_flipped = is_flipped;
		this->item_type = get_item_type(item_id);
	}

};

ostream& operator<<(ostream& stream, const Items^ item);

istream& operator>>(istream& stream, Items^ item);



ref struct Room
{
	PictureBox^ pb;
	MyPoint^ location;
	
	int room_number;
	int area_type;
	bool is_connected;

	float width;
	float height;
	float area;

	List<PictureBox^>^ neighbours;
	List<int>^ neightbours_numbers;
	List<Items^>^ furniture;

	Room()
	{
		this->area_type = NEUTRAL_AREA;
		this->furniture = gcnew List<Items^>;
		this->neighbours = gcnew List<PictureBox^>;
		this->neightbours_numbers = gcnew List<int>;
		this->location = gcnew MyPoint();
	}

	Room(PictureBox^ pb, int room_number, float width, float height)
	{
		this->pb = pb;
		this->location = gcnew MyPoint(pb->Location.X, pb->Location.Y);
		this->room_number = room_number;
		this->width = width;
		this->height = height;
		this->area = int(width * height * 100 + 0.5) / 100.0;
		this->area_type = NEUTRAL_AREA;
		this->furniture = gcnew List<Items^>;
		this->neighbours = gcnew List<PictureBox^>;
		this->neightbours_numbers = gcnew List<int>;
	}

	~Room()
	{
		this->furniture->Clear();
	}

	void set_location()
	{
		this->location = gcnew MyPoint(pb->Location.X, pb->Location.Y);
	}

	void add_item(PictureBox^ pb, MyPoint^ position, int item_id, bool flipped)
	{
		if (get_item_area_type(item_id) != NEUTRAL_AREA)
		{
			if (this->area_type != NEUTRAL_AREA)
			{
				if (this->area_type != get_item_area_type(item_id))
				{
					MessageBox::Show("Wrong!", "Если вы видете это сообщение, значит что-то слишком пошло не так");
					return;
				}
			}
			else
			{
				this->area_type = get_item_area_type(item_id);
			}
		}
		this->furniture->Add(gcnew Items(pb, position, item_id, flipped));
	}

	void clear_items()
	{
		this->furniture->Clear();
		this->area_type = NEUTRAL_AREA;
	}

	int get_area_type()
	{
		return this->area_type;
	}

	void connect_room()
	{
		this->is_connected = true;
	}

	void disconnect_room()
	{
		this->is_connected = false;
	}

	void add_neighbour(PictureBox^ pb, int neighbour_number)
	{
		for (int i = 0; i < this->neighbours->Count; i++)
		{
			if (this->neighbours[i] == pb)
			{
				return;
			}
		}
		this->neighbours->Add(pb);
		this->neightbours_numbers->Add(neighbour_number);
	}

	void add_neighbour(PictureBox^ pb)
	{
		for (int i = 0; i < this->neighbours->Count; i++)
		{
			if (this->neighbours[i] == pb)
			{
				return;
			}
		}
		this->neighbours->Add(pb);
	}

	void kill_neighbour(PictureBox^ pb)
	{
		int index = this->neighbours->IndexOf(pb);
		if (index != -1)
		{
			this->neighbours->RemoveAt(index);
			this->neightbours_numbers->RemoveAt(index);
		}
	}

	int get_neighbours_amount()
	{
		return this->neighbours->Count;
	}
};

ostream& operator<<(ostream& stream, const Room^ room);

istream& operator>>(istream& stream, Room^ room);



ref class Planer
{

private:

	List<Room^>^ rooms;
	String^ address;
	double scale;

public:

	Planer()
	{
		this->rooms = gcnew List<Room^>;
	}

	Planer(List<Room^>^ rooms, String^ address, double scale)
	{
		this->rooms = rooms;
		this->address = address;
		this->scale = scale;
	}

	List<Room^>^ get_rooms()
	{
		return this->rooms;
	}

	String^ get_address()
	{
		return this->address;
	}

	double get_scale()
	{
		return this->scale;
	}

	int get_rooms_amount()
	{
		return this->rooms->Count;
	}

	void set_rooms(List<Room^>^ rooms)
	{
		this->rooms = rooms;
	}

	void set_address(String^ addr)
	{
		this->address = addr;
	}

	void set_scale(double scale)
	{
		this->scale = scale;
	}

	void draw_planning(Form^ form)
	{
		if (this->rooms != nullptr)
		{
			for (int i = 0; i < this->rooms->Count; i++)
			{
				form->Controls->Add(this->rooms[i]->pb);
			}
		}
	}

};


ostream& operator<<(ostream& stream, Planer^ planer);

istream& operator>>(istream& stream, Planer^ planer);

