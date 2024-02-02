#ifndef NAME_H
#define NAME_H
#pragma once

#include "Component.h"
#include <string>

struct Name : Component {
public:
	std::string name;
};

#endif // NAME_H