#pragma once
#include "Level.h"

class TestLevel : public QuadTreeV::Level
{
public:
	TestLevel();

	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Draw();

};

