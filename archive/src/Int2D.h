#ifndef INT2D_H
#define INT2D_H
#pragma once

class Int2D {
public:
	int x, y;

	Int2D();
	Int2D(int posX, int posY);

	Int2D operator+(Int2D const& rs);
	Int2D operator-(Int2D const& rs);
	Int2D operator-=(Int2D const& rs);
	Int2D operator+=(Int2D const& rs);
};

#endif // INT2D_H