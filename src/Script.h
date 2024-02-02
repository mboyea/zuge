#ifndef SCRIPT
#define SCRIPT
#pragma once

class Sprite;
class Script {
public:
	Sprite* sprite;

	Script();
	~Script();

	void OnStart();
	void OnUpdate();
};

#endif // SCRIPT