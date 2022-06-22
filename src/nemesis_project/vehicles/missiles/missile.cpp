#include "missile.h"


missile::missile(int id, loc<int> aLocation)
{
	ID = id;
	location = aLocation;
	model = NULL;
}

missile::~missile()
{
}