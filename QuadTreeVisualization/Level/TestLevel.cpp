#include "TestLevel.h"
#include "QuadTree/QuadTree.h"
#include "Math/Vector2.h"
#include "Core/Input.h"
#include "Renderer/Renderer.h"

using namespace QuadTreeV;
TestLevel::TestLevel()
{
	AddNewActor(new QuadTree());
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
	ShowVector2();
}

void TestLevel::ShowVector2()
{
	Vector2 mousePos = Input::Get().GetMousePosition();
	sprintf_s(vectorString, 128, "Mouse Position (%d, %d) ", mousePos.x, mousePos.y);
	Renderer::Get().Submit(vectorString, Vector2(0, 40));

}
