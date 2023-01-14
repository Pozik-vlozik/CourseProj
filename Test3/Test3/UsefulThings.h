#pragma once
using namespace System::Windows::Forms;

ref class UsefulThings
{
};




ref struct items
{
	PictureBox^ pb;
	int item_id;
	int item_type;
	bool flipped;

	items(PictureBox^ pb, int item_id)
	{
		this->pb = pb;
		this->item_id = item_id;
		this->flipped = false;
		if (item_id < SHOWER_CABIN)
		{
			this->item_type = LIVING_ITEM;
		}
		else if (item_id < VENTILATION)
		{
			this->item_type = NON_LIVING_ITEM;
		}
		else
		{
			this->item_type = NEUTRAL_ITEM;
		}
	}
};


