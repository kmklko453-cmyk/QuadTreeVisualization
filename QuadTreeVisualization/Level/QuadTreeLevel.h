#pragma once
#include "Level.h"
#include "QuadTree/Partition/Node.h"

class TestLevel : public QuadTreeV::Level
{
public:
	TestLevel();

	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Draw();

	void ShowVector2(int x, int height);
	void DrawBox(const Bounds bounds);
	void DrawLine(const Bounds bounds);
	bool DrawLineRecursive(Node* node);
	

private:
	// 좌표 문자열.
	char vectorString[128] = {};
};

