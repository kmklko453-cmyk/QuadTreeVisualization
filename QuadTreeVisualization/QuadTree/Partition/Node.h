#pragma once
#include "Bounds.h"
#include <vector>

//영역 구분을 위한 열거형
enum class NodeIndex
{
	//완전히 포함되는 4가지 
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	//경계선 겹침
	Straddling,
	//영역을 벗어난 경우
	OutOfArea
};

class Node
{
public:
	Node(const Bounds& bounds, int depth = 0);
	~Node();

	//삽입(Insert) 
	void Insert(Node* node);

	//질의 
	void Query(const Bounds& bounds, std::vector<Node*>& possibleNode);

	//정리 
	void Clear();

	//getter
	inline const Bounds& GetBounds() const { return bounds; }
	inline const std::vector<Node*>& Points() const { return points; }

	//자식노드
	inline Node* TopLeft() const { return topLeft; }
	inline Node* TopRight() const { return topRight; }
	inline Node* BottomLeft() const { return bottomLeft; }
	inline Node* BottomRight() const { return bottomRight; }


private:
	//4분할 함수
	bool SubDivide();

	//영역이 분할 됐는지 여부 확인 함수
	bool IsDivided();

	//전달된 영역과 겹치는 영역을 반환하는 함수
	NodeIndex TestRegion(const Bounds& bounds);

	//전달된 영역이 포함되거나 거치는 영역을 모두 구할 떄 사용하는 함수
	std::vector<NodeIndex> GetQuad(const Bounds& bounds);

	//자식 노드 정리 함수
	void ClearChildren();

private:
	//현재 노드의 깊이
	int depth = 0;

	//노드의 영역 (Bounds)
	Bounds bounds;

	//현재 영역에 포함된 노드(목록)
	std::vector<Node*> points;

	//자식 노드 (4개의 노드)
	Node* topLeft = nullptr;
	Node* topRight = nullptr;
	Node* bottomLeft = nullptr;
	Node* bottomRight = nullptr;

};

