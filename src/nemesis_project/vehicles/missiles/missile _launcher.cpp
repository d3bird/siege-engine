#include "missile _launcher.h"


launcher::launcher(int id, loc<int> aLocation)
{
	ID = id;
	location = aLocation;
	model = NULL;
	slotted_missile = NULL;
}

launcher::~launcher()
{
}

void launcher::update_missile_model() {
	if (slotted_missile != NULL && slotted_missile->model != NULL) {
		slotted_missile->model->x_m = location.x * 2;
		slotted_missile->model->y_m = location.y * 2;
		slotted_missile->model->z_m = location.z * 2;
	}
}
