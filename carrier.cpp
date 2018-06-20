#include "carrier.h"


Carrier::Carrier(int cgravity_x,int cgravity_y,int width,int d,int rotation)
{
	_cgravity_x = cgravity_x;
	_cgravity_y = cgravity_y;
	_width = width;
	_d = d;
	_rotation = rotation;
}


Carrier::~Carrier()
{
}
