#include "Planer.h"

int get_item_area_type(int item_number)
{
	if (item_number < SHOWER_CABIN)
	{
		return LIVING_AREA;
	}
	else if (item_number < VENTILATION)
	{
		return NON_LIVING_AREA;
	}
	return NEUTRAL_AREA;

}

int get_item_type(int item_number)
{
	if (item_number < SHOWER_CABIN)
	{
		return LIVING_ITEM;
	}
	else if (item_number < VENTILATION)
	{
		return NON_LIVING_ITEM;
	}
	return NEUTRAL_ITEM;
}


void rotate_pb(PictureBox^ pb)
{
	int width = pb->Width;
	pb->Width = pb->Height;
	pb->Height = width;
	pb->Image->RotateFlip(RotateFlipType::Rotate90FlipX);
}


ostream& operator<<(ostream& stream, const Items^ item)
{
	stream << item->position << " " << item->item_id << " " << item->is_flipped << "\n";
	return stream;
}

istream& operator>>(istream& stream, Items^ item)
{
	int item_id, is_flipped;
	stream >> item->position >> item_id >> is_flipped;
	
	item->item_id = item_id;
	item->is_flipped = is_flipped;
	item->item_type = get_item_type(item_id);

	return stream;
}



ostream& operator<<(ostream& stream, const Room^ room)
{
	stream << room->neightbours_numbers->Count << " ";
	for (int i = 0; i < room->neightbours_numbers->Count; i++)
	{
		stream << room->neightbours_numbers[i] << " ";
	}
	stream << "\n";
	stream << room->furniture->Count << "\n";
	stream << room->room_number << " " << room->location << " " << room->width << " " << room->height << "\n";

	for (int i = 0; i < room->furniture->Count; i++)
	{
		stream << room->furniture[i];
	}

	return stream;
}

istream& operator>>(istream& stream, Room^ room)
{
	int room_number, furniture_count, neighbours_number, number;
	float width, height;
	stream >> neighbours_number;
	for (int i = 0; i < neighbours_number; i++)
	{
		stream >> number;
		room->neightbours_numbers->Add(number);
	}
	stream >> furniture_count >> room_number >> room->location >> width >> height;
	room->room_number = room_number;
	room->width = width;
	room->height = height;
	room->area = int(width * height * 100 + 0.5) / 100.0;

	for (int i = 0; i < furniture_count; i++)
	{
		Items^ item = gcnew Items;
		stream >> item;

		if (room->get_area_type() == NEUTRAL_AREA)
		{
			room->area_type = get_item_area_type(item->item_id);
		}

		room->furniture->Add(item);
		

	}
	return stream;
}



ostream& operator<<(ostream& stream, Planer^ planer)
{
	stream << string_to_char(planer->get_address()) << "\n" << planer->get_scale() << "\n";
	stream << planer->get_rooms_amount() << "\n";
	
	List<Room^>^ rooms = planer->get_rooms();

	for (int i = 0; i < rooms->Count; i++)
	{
		stream << rooms[i];
	}

	return stream;
}

istream& operator>>(istream& stream, Planer^ planer)
{
	char addr[255];
	String^ address;
	double scale;
	int rooms_amount;
	List<Room^>^ rooms = gcnew List<Room^>;

	stream.getline(addr, sizeof(addr));
	stream >> scale >> rooms_amount;
	address = char_to_string(addr);

	planer->set_address(address);
	planer->set_scale(scale);

	for (int i = 0; i < rooms_amount; i++)
	{
		Room^ room = gcnew Room();
		stream >> room;
		rooms->Add(room);
	}

	planer->set_rooms(rooms);
	
	return stream;
}
