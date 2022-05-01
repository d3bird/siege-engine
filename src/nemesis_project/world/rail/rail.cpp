#include "rail.h"


railRoad::rail::rail(int aID, int aX, int aY, int aZ) {
	ID = aID;

	x = aX;
	y = aY;
	z = aZ;
	 
	connecttion1 = 0;
	connecttion2 = 0;
}

bool railRoad::rail::operator ==(const rail& right) {
	return (ID == right.ID);
}