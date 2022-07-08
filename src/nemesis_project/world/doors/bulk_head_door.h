#pragma once

#include <rendering/rendering_object_data.hpp>
#include "../../common_obj/location.h"


class bulk_head_door{
public:
	bulk_head_door();
	~bulk_head_door();

	void update(double time);

	void create_door(loc<int> start, loc<int> end, bool y_axis, bool dir1);

	void set_models();

	bool is_open();
	bool is_moving();
	bool is_closing();
	bool is_openeing();
	
	void open_door();
	void close_door();


	struct door_section {
		rendering::item_info* obj;
		loc<double> open_location;
		loc<double> close_location;
		loc<double> current_location;
		rendering::rotation angle;
	};

	door_section** door_objs;
	int x_size;
	int z_size;

private:
	bool m_is_open;
	bool m_openeing;

	bool m_is_close;
	bool m_closing;
	double m_move_speed;

	bool m_open_y_axis;
	bool m_open_dir;

};
