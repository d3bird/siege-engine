#pragma once

#include "optimized_spawner.h"


/*This class takes the API that weas set up and creates the optimized spawner
* that will primarly interact with the and hanfdle the optimazation of determining what
* is on screen and what is not,
*/
class create_engine
{
public:
	create_engine();
	~create_engine();

	optimized_spawner* init(engine_api* API);

	optimized_spawner* get_current() { return current; }

private:

	optimized_spawner* current;

};

