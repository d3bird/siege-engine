#pragma once

#include <string>


template<class T> class loc;


template<> class loc<int> {
public:

	loc();
	loc(const loc<double>& other);
	loc(const loc<float>& other);
	~loc(){}
	loc(int  x0, int  y0, int  z0);

	int x;
	int y;
	int z;

	bool operator==(const loc<int>& other);
	bool operator!=(const loc<int>& other);
	void  operator=(const loc<int>& other);
	void  operator=(const loc<double>& other);
	void  operator=(const loc<float>& other);

	std::string to_string();

private:

};

template<> class loc<double> {
public:

	loc();
	loc(const loc<int>& other);
	loc(const loc<float>& other);
	~loc() {}
	loc(double  x0, double  y0, double  z0);

	double x;
	double y;
	double z;

	bool operator==(const loc<double>& other);
	bool operator!=(const loc<double>& other);
	void  operator=(const loc<int>& other);
	void  operator=(const loc<double>& other);
	void  operator=(const loc<float>& other);

	std::string to_string();

private:

};

template<> class loc<float> {
public:

	loc();
	loc(const loc<double>& other);
	loc(const loc<int>& other);
	~loc() {}
	loc(float  x0, float  y0, float  z0);

	float x;
	float y;
	float z;

	bool operator==(const loc<float>& other);
	bool operator!=(const loc<float>& other);
	void  operator=(const loc<int>& other);
	void  operator=(const loc<double>& other);
	void  operator=(const loc<float>& other);

	std::string to_string();

private:

};