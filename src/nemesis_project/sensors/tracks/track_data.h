#pragma	once 
#include "../../common_obj/location.hpp"


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

	void update_location(const loc<double> &location);
	void update_rotation();
	
	
	
private:
	int ID;

	double x_velocity;
	double y_velocity;
	double z_velocity;

	loc<double> location;

};

