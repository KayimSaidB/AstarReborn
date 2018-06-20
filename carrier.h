#pragma once
class Carrier
{
public:
	Carrier(int cgravity_x,
		int cgravity_y,
		int width,
		int d,int rotation);
	~Carrier();
	int get_cgravityX(){ return _cgravity_x; };
	int get_cgravityY(){ return _cgravity_y; };
	int set_cgravityX(int newX){ _cgravity_x=newX; };
	int set_cgravityY(int newY){ _cgravity_y=newY; };
	int get_width(){ return _width; };
	int get_d(){ return _d; };
	int get_rotation(){ return _rotation; }
	void set_rotation(int newrotation){ _rotation= newrotation; }

private:
	int _cgravity_x;
	int _cgravity_y;
	int _width;
	int _d;
	int _rotation; /// 1 North 2 South 3 West 4 East

};

