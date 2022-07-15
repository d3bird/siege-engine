#pragma once

#include "grnd_obj_type.hpp"
#include "../../common_obj/location.h"
#include  <rendering/rendering_object_data.hpp>

namespace grnd_items {

	class grnd_obj
	{
	public:

		grnd_obj(int aID, grnd_obj_type aType,int aAmount, int aMax_amount,const loc<int> &alocation);
		grnd_obj(const grnd_obj&) = delete;

		~grnd_obj();
		
		void set_type(grnd_obj_type aType);

		void set_rendering_model(rendering::item_info* model);
		rendering::item_info* get_model();

		int get_ID();
		loc<int> get_location();
		int get_amount();
		int get_max_amount();
		grnd_obj_type get_type();

		//return the amount remaining if change goes above/bellow the max/min
		int operator+=(int add);
		int operator-=(int subtrack);
		int operator-(int subtrack);
		int operator+(int add);

		bool operator==(const grnd_obj& other);
		bool operator==(int other_id);
		grnd_obj operator = (const grnd_obj& other) = delete;

	private:

		int ID;

		grnd_obj_type type;
		int amount;
		int max_amount;

		loc<int> location;

		rendering::item_info* rendering_model;
	};

}