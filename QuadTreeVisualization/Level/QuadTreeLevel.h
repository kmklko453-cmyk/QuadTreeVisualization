#pragma once
#include <memory>

#include "Level.h"
#include "QuadTree/Partition/Node.h"
#include "QuadTree/QuadTree.h"
#include "Math/Vector2.h"

class QuadTreeLevel : public QuadTreeV::Level
{
public:
	QuadTreeLevel();

	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Draw();

	void ShowVector2(int x, int height);
	void DrawBox(const Bounds bounds);
	void DrawLine(const Bounds bounds);
	bool DrawLineRecursive(Node* node);

private:
	//화면에 그릴 문자열 버퍼
	char vectorString[128] = {};

	//쿼드 트리 
	QuadTree tree;
	//마우스 포지션 받을 Vector2 클래스
	QuadTreeV::Vector2 mousePos;
	//마우스 포지션 받을 Node 타입 스마트 포인터 
	std::unique_ptr<Node> mouseNode;
};
