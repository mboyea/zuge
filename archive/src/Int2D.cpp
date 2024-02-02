#include "Int2D.h"

Int2D::Int2D() {
	x = 0;
	y = 0;
}

Int2D::Int2D(int posX, int posY) {
	x = posX;
	y = posY;
}

Int2D Int2D::operator+(Int2D const& rs) {
	x += rs.x;
	y += rs.y;
	return *this;
}

Int2D Int2D::operator-(Int2D const& rs) {
	x -= rs.x;
	y -= rs.y;
	return *this;
}

Int2D Int2D::operator+=(Int2D const& rs) {
	x += rs.x;
	y += rs.y;
	return *this;
}

Int2D Int2D::operator-=(Int2D const& rs) {
	x -= rs.x;
	y -= rs.y;
	return *this;
}