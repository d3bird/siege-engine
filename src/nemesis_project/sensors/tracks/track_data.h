#pragma	once 
#include "../common_obj/location.hpp"

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



	//operators
	//track& operator=(const track& other);
	bool operator==(const track& other);
	bool operator==(const int& id);

private:
	int ID;

};

