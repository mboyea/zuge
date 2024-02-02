#include "Position.h"

Position::Position() {
	x = 0;
	y = 0;
}

Position::Position(int posX, int posY) {
	x = posX;
	y = posY;
}

Position Position::operator+(Position const& rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Position Position::operator-(Position const& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Position Position::operator+=(Position const& rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Position Position::operator-=(Position const& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}