#include "QuadTreeLevel.h"

#include "Core/Input.h"
#include "Renderer/Renderer.h"

using namespace QuadTreeV;

QuadTreeLevel::QuadTreeLevel()
	: tree(Bounds(0, 0, 200, 150)), mousePos(0, 0), mouseNode(new Node(Bounds(0, 0)))
{
}

void QuadTreeLevel::BeginPlay()
{
}

void QuadTreeLevel::Tick(float deltaTime)
{
	Level::Tick(deltaTime);
	//마우스 좌표 Vector 클래스에 저장 
	mousePos = Input::Get().GetMousePosition();

	//예외처리
	if (!tree.GetNode())
	{
		return;
	}

	tree.GetNode()->Clear();
	//기존 스마트 포인터가 가리키는 객체 삭제후 새로 생성
	//delete mouseNode;
	//mouseNode = new Node(...)
	mouseNode.reset(new Node(Bounds(mousePos.x, mousePos.y)));
	
	//겹치는 영역 확인하면서 분기 
	//get() <- 스마트 포인터 함수 현재 스마트 포인터가 가리키는 객체를 반환 
	//즉 스마트 포인터의 값을 반환함
	tree.GetNode()->Insert(mouseNode.get());
}

void QuadTreeLevel::Draw()
{
	Level::Draw();
	//예외 처리
	if (!tree.GetNode())
	{
		return;
	}
	//쿼드 트리 크기 설정 
	DrawBox(tree.GetNode()->GetBounds());
	//마우스 좌표 그리기
	ShowVector2(
		tree.GetNode()->GetBounds().X(),
		tree.GetNode()->GetBounds().Height());
	//쿼드 트리 분할 그리기
	DrawLineRecursive(tree.GetNode());
}

void QuadTreeLevel::ShowVector2(int x, int height)
{
	sprintf_s(vectorString, 128, "Mouse Position (%d, %d)", mousePos.x, mousePos.y);
	Renderer::Get().Submit(vectorString, Vector2(x, height + 1));
}

void QuadTreeLevel::DrawBox(const Bounds bounds)
{
	//꼭짓점 그리기
	Renderer::Get().Submit("+", Vector2(bounds.X(), bounds.Y()), Color::Green);
	Renderer::Get().Submit("+", Vector2(bounds.X(), bounds.Height()), Color::Green);
	Renderer::Get().Submit("+", Vector2(bounds.Width(), bounds.Y()), Color::Green);
	Renderer::Get().Submit("+", Vector2(bounds.Width(), bounds.Height()), Color::Green);

	//Top
	for (int i = bounds.X() + 1; i < bounds.Width(); i++)
	{
		Renderer::Get().Submit("-", Vector2(i, bounds.Y()), Color::Green);
	}
	//Left
	for (int i = bounds.Y() + 1; i < bounds.Height(); i++)
	{
		Renderer::Get().Submit("|", Vector2(bounds.X(), i), Color::Green);
	}
	//Bottom
	for (int i = bounds.X() + 1; i < bounds.Width(); i++)
	{
		Renderer::Get().Submit("-", Vector2(i, bounds.Height()), Color::Green);
	}
	//Right
	for (int i = bounds.Y() + 1; i < bounds.Height(); i++)
	{
		Renderer::Get().Submit("|", Vector2(bounds.Width(), i), Color::Green);
	}
}

void QuadTreeLevel::DrawLine(const Bounds bounds)
{
	//Left -> Right
	for (int i = bounds.X() + 1; i < bounds.X() + bounds.Width(); i++)
	{
		Renderer::Get().Submit("-", Vector2(i, bounds.Y() + bounds.Height() / 2), Color::Green);
	}
	//Top -> Bottom
	for (int i = bounds.Y() + 1; i < bounds.Y() + bounds.Height(); i++)
	{
		Renderer::Get().Submit("|", Vector2(bounds.X() + bounds.Width() / 2, i), Color::Green);
	}
	//Center
	Renderer::Get().Submit("+", Vector2(bounds.X() + bounds.Width() / 2, bounds.Y() + bounds.Height() / 2));
}

bool QuadTreeLevel::DrawLineRecursive(Node* node)
{
	//에외처리
	if (!node)
	{
		return false;
	}
	//마지막 노드시 그리고 종료
	if (!node->Points().empty())
	{
		DrawLine(node->GetBounds());
		return true;
	}
	//자식 없으면 종료
	if (!node->IsDivided())
	{
		return false;
	}

	//현재 분할 그리기
	DrawLine(node->GetBounds());

	//TopLeft
	if (node->TopLeft())
	{
		DrawLineRecursive(node->TopLeft());
	}
	//TopRight
	if (node->TopRight())
	{
		DrawLineRecursive(node->TopRight());
	}
	//BottomLeft
	if (node->BottomLeft())
	{
		DrawLineRecursive(node->BottomLeft());
	}
	//BottomRight
	if (node->BottomRight())
	{
		DrawLineRecursive(node->BottomRight());
	}

	return true;
}
