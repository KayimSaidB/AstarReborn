#pragma once
#include<cstdio> 
#include<cstdlib> 
#include <ctime>
#include <cmath>
#include <windows.h>

class Bed
{
public:
	Bed(int tabposition[8], int width, int d);
	~Bed();
	int get_width(){ return _width; };
	int get_d(){ return _d; };
	int *get_up_left_corner();
	int *get_up_right_corner();
	int *get_down_left_corner();
	int *get_down_right_corner();


private:
		int _tabposition[8];
		int _width;
		int _d;
		
};

