//----------------------------------------------------------
// A 2d vector, storing information for all your 2d vectory needs
// Bryn Stringer 
//----------------------------------------------------------
#pragma once

class util_vector2d
{
public:
	util_vector2d(void);
	util_vector2d(int,int);
	~util_vector2d(void);
	int x;
	int y;

	util_vector2d operator +(util_vector2d input);

};
