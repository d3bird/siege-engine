#include "track_data.h"

track::track(int id){
	ID = id;
}

track::~track(){

}
//
//track& track::operator=(const track& other) {
//
//	return NULL;
//}

bool track::operator==(const track& other) {
	return false;
}

bool track::operator==(const int& id) {
	return ID == id;
}
