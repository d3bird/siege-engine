#include "location.h"

//============================ INT =========================

loc<int>::loc() {
	x = -1;
	y = -1;
	z = -1;
}


loc<int>::loc(int  x0, int  y0, int  z0) {
	x = x0;
	y = y0;
	z = z0;
}


bool loc<int>::operator==(const loc<int>& other) {
	return (x == other.x &&
		y == other.y &&
		z == other.z);
}

bool loc<int>::operator!=(const loc<int>& other) {
	return (x != other.x ||
		y != other.y ||
		z != other.z);
}

void  loc<int>::operator=(const loc<int>& other) {
	x = other.x;
	y = other.y;
	z = other.z;
}

std::string loc<int>::to_string() {
	return std::to_string(x)+ ","+ std::to_string(y) +","+ std::to_string(z);
}


//============================ DOUBLE =========================

loc<double>::loc() {
	x = -1;
	y = -1;
	z = -1;
}


loc<double>::loc(double  x0, double  y0, double  z0) {
	x = x0;
	y = y0;
	z = z0;
}


bool loc<double>::operator==(const loc<double>& other) {
	return (x == other.x &&
		y == other.y &&
		z == other.z);
}

bool loc<double>::operator!=(const loc<double>& other) {
	return (x != other.x ||
		y != other.y ||
		z != other.z);
}

void  loc<double>::operator=(const loc<double>& other) {
	x = other.x;
	y = other.y;
	z = other.z;
}

std::string loc<double>::to_string() {
	return std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z);
}

//============================ FLOAT =========================

loc<float>::loc() {
	x = -1;
	y = -1;
	z = -1;
}


loc<float>::loc(float  x0, float  y0, float  z0) {
	x = x0;
	y = y0;
	z = z0;
}


bool loc<float>::operator==(const loc<float>& other) {
	return (x == other.x &&
		y == other.y &&
		z == other.z);
}

bool loc<float>::operator!=(const loc<float>& other) {
	return (x != other.x ||
		y != other.y ||
		z != other.z);
}

void  loc<float>::operator=(const loc<float>& other) {
	x = other.x;
	y = other.y;
	z = other.z;
}

std::string loc<float>::to_string() {
	return std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z);
}