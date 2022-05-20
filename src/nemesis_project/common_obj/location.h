#pragma once

#include <string>


template<class T> class loc;


template<> class loc<int> {
public:

	loc();
	~loc(){}
	loc(int  x0, int  y0, int  z0);

	int x;
	int y;
	int z;

	bool operator==(const loc<int>& other);
	void  operator=(const loc<int>& other);


private:

};

template<> class loc<double> {
public:

	loc();
	~loc() {}
	loc(double  x0, double  y0, double  z0);

	double x;
	double y;
	double z;

	bool operator==(const loc<double>& other);
	void  operator=(const loc<double>& other);

private:

};

template<> class loc<float> {
public:

	loc();
	~loc() {}
	loc(float  x0, float  y0, float  z0);

	float x;
	float y;
	float z;

	bool operator==(const loc<float>& other);
	void  operator=(const loc<float>& other);

private:

};