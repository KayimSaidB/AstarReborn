#include "bed.h"


Bed::Bed(int tabposition[8], int width, int d)
{
	memcpy(_tabposition, tabposition, 8*sizeof(int));
	_width = width;
	_d = d;
}


Bed::~Bed()
{
}

int *Bed::get_up_left_corner(){
	int *coord = (int*)malloc(2 * sizeof(int));
	coord[0] = _tabposition[0];
	coord[1] = _tabposition[1];
		return coord;

}
int *Bed::get_up_right_corner(){
	int *coord = (int*)malloc(2 * sizeof(int));
	coord[0] = (int)_tabposition[2];
	coord[1] = (int)_tabposition[3];
		return coord;
}
int *Bed::get_down_left_corner(){
	int *coord = (int*)malloc(2 * sizeof(int));
	coord[0] = _tabposition[4];
	coord[1] = _tabposition[5];
		return coord;
}
int *Bed::get_down_right_corner(){
	int *coord = (int*)malloc(2 * sizeof(int));
	coord[0] = _tabposition[6];
	coord[1] = _tabposition[7];
	return coord;
}