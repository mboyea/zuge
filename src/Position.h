#ifndef POSITION
#define POSITION
#pragma once

class Position {
public:
	int x = 1, y = 1;

	Position();
	Position(int posX, int posY);

	Position operator+(Position const& rhs);
	Position operator-(Position const& rhs);
	Position operator+=(Position const& rhs);
	Position operator-=(Position const& rhs);
};

#endif // POSITION