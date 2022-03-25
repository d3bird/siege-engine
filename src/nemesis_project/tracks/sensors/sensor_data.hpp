#pragma	once 


struct sensor_base {

	bool running;
	bool jammed;
	double noise_tollerece;

	bool wired;
	bool radio;
	bool connected;
};

struct radar {
	int x;
	int y;
	int z;

	double angle;
	double trun_rate;

	sensor_base* base_sats;
};

struct radio {
	int x;
	int y;
	int z;

	double radius;

	sensor_base* base_sats;
};