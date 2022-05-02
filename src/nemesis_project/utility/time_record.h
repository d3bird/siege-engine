#pragma

namespace a_time {

	/*time stamp
	* this is the time that something happened in the world
	*/

	struct time_stamp {

		double sec;
		double min;
		double hour;
		int day;
		int month;
		int year;

		time_stamp(double s, double m, double h, int d, int mo, int y) {
			sec = s;
			min = m;
			hour = h;
			day = d;
			month = mo;
			year = y;
		}

		bool operator< (const time_stamp& rhs) {
			if (year == rhs.year) {
				if (month == rhs.month) {
					if (day == rhs.day) {
						if (hour == rhs.hour) {
							if (min == rhs.min) {
								if (sec == rhs.sec) {
									return false;
								}
								else if (sec < rhs.sec) {
									return true;
								}
							}
							else if (min < rhs.min) {
								return true;
							}
						}
						else if (hour < rhs.hour) {
							return true;
						}
					}
					else if (day < rhs.day) {
						return true;
					}
				}
				else if (month < rhs.month) {
					return true;
				}
			}
			else if (year < rhs.year) {
				return true;
			}
			return false;
		}
		//inline bool operator> (const time_stamp& rhs) { return rhs < const this; }
		//inline bool operator<=(const time_stamp& rhs) { return !(lhs > rhs); }
		//inline bool operator>=(const time_stamp& rhs) { return !(lhs < rhs); }

	};


	/*time manager
	* keeps track of the time in the world, converts 
	*/
	class time_manager {
	public:
		time_manager(double s, double m, double h, int d, int mo, int y);
		~time_manager();

		void operator+= (const double delta_time);

		//getter
		time_stamp& get_time_stamp();

		//setters
		void set_year(int y);
		void set_month(int m);
		void set_day(int d);
		void set_hour(double h);
		void set_min(double m);
		void set_sec(double s);

	private:

		//current time
		double sec;
		double min;
		double hour;
		int day;
		int month;
		int year;

		double time_change;
		double time_ratio;


	};

}