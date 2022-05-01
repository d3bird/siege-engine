#pragma once

namespace railRoad {
	class rail {
	public:
		rail(int aID, int aX, int aY, int aZ);

		int get_x() { return x; }
		int get_y() { return y; }
		int get_z() { return z; }
		int get_ID() { return ID; }

		void set_connection1(rail* con) { connecttion1 = con; }
		void set_connection2(rail* con) { connecttion2 = con; }

		rail* get_connection1() { return connecttion1; }
		rail* get_connection2() { return connecttion2; }

		bool operator ==(const rail& right);

	private:

		int ID;

		int x;
		int y;
		int z;

		rail* connecttion1;
		rail* connecttion2;

	};

}