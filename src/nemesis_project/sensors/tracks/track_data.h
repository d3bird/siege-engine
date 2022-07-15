#pragma	once 
#include "../../common_obj/location.h"
#include <rendering/rendering_object_data.hpp>

/* the track class
* a track is the location of a tpye of object that is updated by
* the track manager
* 
* the tracks manager is localised 
*/

class track{
public:
	track(int id);
	~track();

	void update(double time_change);

	void set_tracking_model(rendering::item_info* model);

	void update_location(const loc<double>& alocation);
	void update_location(double x, double y, double z);
	void update_rotation(const rendering::rotation& new_angle);

	bool is_tracking();
	bool has_track_gone_stale();

	void print_info();

	loc<double> get_location();
	rendering::rotation get_rotation();
	double get_x_velocity();
	double get_y_velocity();
	double get_z_velocity();
	int get_ID();

	bool operator==(const track& other);
	bool operator==(int other_id);
	
private:
	int ID;
	rendering::item_info* tracking_model;
	bool track_stale;
	bool currently_tracking;

	rendering::rotation angles;
	double x_velocity;
	double y_velocity;
	double z_velocity;

	loc<double> location;

};

