#include "Node.h"
#include "Util/Util.h"

Node::Node(const Bounds& bounds, int depth)
	:bounds(bounds), depth(depth)
{
}

Node::~Node()
{
	//정리
	Clear();
}

void Node::Clear()
{
	//point에 추가 되는 노드는 외부(level)에서 관리함

	//목록 정리
	points.clear();

	//분할된 경우 자손 정리
	if (IsDivided())
	{

		topLeft->Clear();
		topRight->Clear();
		bottomLeft->Clear();
		bottomRight->Clear();

		ClearChildren();
	}
}

bool Node::SubDivide()
{
	//최대 깊이 도달 했는지 확인
	if (depth == 5)
	{
		return false;
	}

	//분할 여부  파악
	//분할 전이면 영역 나누기
	if (!IsDivided())
	{
		//영역을 나누기 위한 변수
		int x = bounds.X();
		int y = bounds.Y();
		int halfWidth = bounds.Width() / 2;
		int halfHeight = bounds.Height() / 2;

		// 각 4분면의 자식 객체 생성.
		topLeft = new Node(
			Bounds(x, y, halfWidth, halfHeight), depth + 1
		);

		topRight = new Node(
			Bounds(x + halfWidth, y, halfWidth, halfHeight), depth + 1
		);

		bottomLeft = new Node(
			Bounds(x, y + halfHeight, halfWidth, halfHeight), depth + 1
		);

		bottomRight = new Node(
			Bounds(x + halfWidth, y + halfHeight, halfWidth, halfHeight),
			depth + 1
		);

	}



	return false;
}

bool Node::IsDivided()
{
	// 자식 하나만 확인
	return topLeft != nullptr;
}

NodeIndex Node::TestRegion(const Bounds& bounds)
{
	//전달된 bounds와 겹치는 4분면 목록 확인 
	std::vector<NodeIndex> quads = GetQuad(bounds);

	//겹치는 곳이 없으면 OutOfArea 반환
	if (quads.empty())
	{
		return NodeIndex::OutOfArea;
	}

	//4개중 하나의 영역에만 겹치는 경우 해당 4분면 반환
	if (quads.size() == 1)
	{
		return quads[0];
	}

	//여러 영역과 겹치는 경우
	return NodeIndex::Straddling;
}

std::vector<NodeIndex> Node::GetQuad(const Bounds& bounds)
{
	//겹치는 영역 반환을 위한 함수
	std::vector<NodeIndex> quads;

	//영역 계산에 필요한 함수
	int x = bounds.X();
	int y = bounds.Y();
	int halfWidth = this->bounds.Width() / 2;
	int halfHeight = this->bounds.Height() / 2;
	int centerY = halfWidth;
	int centerX = halfHeight;

	//왼쪽 영역이랑 겹치는지 확인
	bool left = bounds.X() < centerX && bounds.MaxX() >= x;

	//오른쪽 영역이랑 겹치는지 확인
	bool right = bounds.MaxX() >= centerX && bounds.X() >= x;

	//위쪽이랑 영역이 겹치는지 확인
	bool top = bounds.Y() < centerY && bounds.MaxY() >= y;

	//아래쪽이랑 영역이 겹치는지 확인
	bool bottom = bounds.MaxY() >= centerY && bounds.Y() < this->bounds.MaxY();

	//영역 판정
	if (top && left)
	{
		quads.emplace_back(NodeIndex::TopLeft);
	}
	if (top && right)
	{
		quads.emplace_back(NodeIndex::TopRight);
	}
	if (bottom && left)
	{
		quads.emplace_back(NodeIndex::BottomLeft);
	}
	if (bottom && right)
	{
		quads.emplace_back(NodeIndex::BottomRight);
	}

	return quads;
}

void Node::ClearChildren()
{
	//분할 진행된 경우 자손 노드 삭제
	if (IsDivided())
	{
		SafeDelete(topLeft);
		SafeDelete(topRight);
		SafeDelete(bottomLeft);
		SafeDelete(bottomRight);
	}
}
