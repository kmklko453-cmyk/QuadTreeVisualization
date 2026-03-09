#include "TestLevel.h"
#include "QuadTree/QuadTree.h"
#include "Math/Vector2.h"
#include "Core/Input.h"
#include "Renderer/Renderer.h"

using namespace QuadTreeV;
TestLevel::TestLevel()
{

}

void TestLevel::BeginPlay()
{

}
void TestLevel::Tick(float deltaTime)
{

}
void TestLevel::Draw()
{
	Level::Draw();
	//쿼드 트리 생성
	QuadTree tree(Bounds(0, 0, 200, 150));
	//마우스 좌표 Vector 클래스로 저장
	Vector2 pos = Input::Get().GetMousePosition();
	//마우스 좌표로 node 생성
	Node mouseposB(Bounds(pos.x, pos.y));

	//root bounds 맞춰서 박스 생성
	DrawBox(tree.GetNode()->GetBounds());
	//마우스 현재 좌표 출력
	ShowVector2(
		tree.GetNode()->GetBounds().X(),
		tree.GetNode()->GetBounds().Height());

	// 삽입할 노드의 bounds가 속한 사분면으로 재귀 삽입한다.
	// 여러 사분면에 걸치거나( Straddling ) 최대 깊이면 현재 노드에 저장한다.
	tree.GetNode()->Insert(&mouseposB);

	//위 결과를 바탕으로 마지막 노드까지 재귀하면서 그림
	DrawLineRecursive(tree.GetNode());

}

void TestLevel::ShowVector2(int x, int heigh)
{
	Vector2 mousePos = Input::Get().GetMousePosition();
	sprintf_s(vectorString, 128, "Mouse Position (%d, %d) ", mousePos.x, mousePos.y);
	Renderer::Get().Submit(vectorString, Vector2(x, heigh + 1));

}

void TestLevel::DrawBox(const Bounds bounds)
{


	//TopLeft 꼭짓점
	Renderer::Get().Submit("+", Vector2(bounds.X(), bounds.Y()), Color::Green);
	//TopRight 꼭짓점
	Renderer::Get().Submit("+", Vector2(bounds.X(), bounds.Height()), Color::Green);
	//BottomLeft 꼭짓점
	Renderer::Get().Submit("+", Vector2(bounds.Width(), bounds.Y()), Color::Green);
	//BottomRight 꼭짓점
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

void TestLevel::DrawLine(const Bounds bounds)
{
	for (int i = bounds.X() + 1; i < bounds.X() + bounds.Width(); i++)
	{
		Renderer::Get().Submit("-", Vector2(i, bounds.Y() + bounds.Height() / 2), Color::Green);
	}
	//Top-Bottom
	for (int i = bounds.Y() + 1; i < bounds.Y() + bounds.Height(); i++)
	{
		Renderer::Get().Submit("|", Vector2(bounds.X() + bounds.Width() / 2, i), Color::Green);
	}
	Renderer::Get().Submit("+", Vector2((bounds.X() + bounds.Width() / 2), (bounds.Y() + bounds.Height() / 2)));
}

bool TestLevel::DrawLineRecursive(Node* node)
{
	//마지막 노드 확인 조건
	if (node->Points().empty() == false)
	{
		DrawLine(node->GetBounds());
		return true;
	}
	//재귀 종료 조건
	if (!node || !node->IsDivided())
	{
		return false;
	}

	DrawLine(node->GetBounds());


	//분기 조건
	if (node->TopLeft())
	{
		DrawLineRecursive(node->TopLeft());

	}
	if (node->TopRight())
	{

		DrawLineRecursive(node->TopRight());

	}
	if (node->BottomLeft())
	{

		DrawLineRecursive(node->BottomLeft());

	}
	if (node->BottomRight())
	{

		DrawLineRecursive(node->BottomRight());

	}

	return true;
	//return true;
}

