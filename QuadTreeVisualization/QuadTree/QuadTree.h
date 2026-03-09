#pragma once
#include "Partition/Node.h"

class QuadTree
{
public:
	QuadTree(const Bounds bounds);
	~QuadTree();

	//질의 함수
	std::vector<Node*> Query(Node* queryNode);


public:
	//트리의 최대 허용깊이
	static const int maxDepth = 3;

	Node* GetNode() const { return root; };

private:
	//루트 노드
	Node* root = nullptr;

};

