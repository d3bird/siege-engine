#include "time_record.h"

a_time::time_manager::time_manager(double s, double m, double h, int d, int mo, int y) {
	sec = s;
	min = m;
	hour = h;
	day = d;
	month = mo;
	year = y;

	time_change = 0;
	time_ratio = 10;
}

a_time::time_manager::~time_manager() {

}

void a_time::time_manager::operator+= (const double delta_time) {
	time_change += delta_time;

}

//getter
a_time::time_stamp& a_time::time_manager::get_time_stamp() {
	return time_stamp(sec, min, hour, day, month, year);
}

//setters
void a_time::time_manager::set_year(int y) {
	year = y;
}

void a_time::time_manager::set_month(int m) {
	month = m;
}

void a_time::time_manager::set_day(int d) {
	day = d;
}

void a_time::time_manager::set_hour(double h) {
	hour = h;
}

void a_time::time_manager::set_min(double m) {
	min = m;
}

void a_time::time_manager::set_sec(double s) {
	sec = s;
}