#include "MyPoint.h"

MyPoint::MyPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}

MyPoint::MyPoint(const MyPoint% mypoint)
{
	this->x = mypoint.x;
	this->y = mypoint.y;
}

MyPoint::MyPoint(MyPoint^ mypoint)
{
	this->x = mypoint->x;
	this->y = mypoint->y;
}

void MyPoint::set(int both)
{
	this->x = both;
	this->y = both;
}

void MyPoint::set(int x, int y)
{
	this->x = x;
	this->y = y;
}

double MyPoint::vec_modl()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

MyPoint MyPoint::operator-(const MyPoint% other)
{
	return  MyPoint(this->x - other.x, this->y - other.y);
}

double MyPoint::VectModule(MyPoint% vect)
{
	return sqrt(pow(vect.x, 2) + pow(vect.y, 2));
}

void MyPoint::operator=(const MyPoint% other)
{
	this->x = other.x;
	this->y = other.y;
}

int MyPoint::operator*(const MyPoint% other)
{
	return this->x * other.x + this->y * other.y;
}

bool MyPoint::operator==(const MyPoint% other)
{
	return this->x == other.x && this->y == other.y;
}

ostream& operator<<(ostream& stream, const MyPoint^ point)
{
	stream << point->x << " " << point->y;
	return stream;
}

istream& operator>>(istream& stream, MyPoint^ point)
{
	int x, y;
	stream >> x >> y;
	point->set(x, y);
	return stream;
}