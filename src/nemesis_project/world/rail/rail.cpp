#include "rail.h"


railRoad::rail::rail(int aID, int aX, int aY, int aZ) {
	ID = aID;

	location = loc<int>(aX, aY, aZ);
	connecttion1 = 0;
	connecttion2 = 0;
}

railRoad::rail::rail(int aID, loc<int>& alocation) {
	location = alocation;
	ID = aID;
	connecttion1 = 0;
	connecttion2 = 0;
}


bool railRoad::rail::operator ==(const rail& right) {
	return (ID == right.ID);
}