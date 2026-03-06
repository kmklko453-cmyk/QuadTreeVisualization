#pragma once
#include "Level.h"

class TestLevel : public QuadTreeV::Level
{
public:
	TestLevel();

	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Draw();

	void ShowVector2(int x, int heigh);
	void DrawBox(int x, int y, int width, int height);
	void DrawLine(int x, int y, int width, int height);
	

private:
	// 좌표 문자열.
	char vectorString[128] = {};
};

