#pragma once
#include <Windows.h>
#include <fstream>
#include <math.h>
#include <string>
#include <iostream>
using namespace std;

using namespace System;
using namespace System::IO;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


ref class MyPoint
{
public:

	int x;
	int y;

	MyPoint() {}

	MyPoint(int x, int y);

	MyPoint(const MyPoint% mypoint);

	MyPoint(MyPoint^ mypoint);

	void set(int both);

	void set(int x, int y);

	double vec_modl();

	static double VectModule(MyPoint% vect);

	MyPoint operator -(const MyPoint% other);

	void operator=(const MyPoint% other);

	int operator *(const MyPoint% other);

	bool operator==(const MyPoint% other);

};

ostream& operator<<(ostream& stream, const MyPoint^ point);

istream& operator>>(istream& stream, MyPoint^ point);
