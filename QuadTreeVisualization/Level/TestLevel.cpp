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
	QuadTree tree(Bounds(5, 5, 100,50));

	Vector2 pos = Input::Get().GetMousePosition();

	Node mouseposB(Bounds(pos.x,pos.y));
	//root bounds ¸ÂÃç¼­ ¹Ú½º »ý¼º
	DrawBox(
		tree.GetNode()->GetBounds().X(),
		tree.GetNode()->GetBounds().Y(),
		tree.GetNode()->GetBounds().Width(),
		tree.GetNode()->GetBounds().Height());
	//¸¶¿ì½º ÇöÀç ÁÂÇ¥ Ãâ·Â
	ShowVector2(
		tree.GetNode()->GetBounds().X(), tree.GetNode()->GetBounds().Height());

	

		Renderer::Get().Submit("true", Vector2(5, 52));
		tree.GetNode()->Insert(&mouseposB);
		int index = 0;
		while(!mouseposB.Points().empty())
		{
			
			DrawLine(
			mouseposB.GetBounds().X(),
			mouseposB.GetBounds().Y(),
			mouseposB.GetBounds().Width(),
			mouseposB.GetBounds().Height());

		}
	
}

void TestLevel::ShowVector2(int x, int heigh)
{
	Vector2 mousePos = Input::Get().GetMousePosition();
	sprintf_s(vectorString, 128, "Mouse Position (%d, %d) ", mousePos.x, mousePos.y);
	Renderer::Get().Submit(vectorString, Vector2(x, heigh+1));

}

void TestLevel::DrawBox(int x, int y, int width, int height)
{
	//TopLeft ²ÀÁþÁ¡
	Renderer::Get().Submit("+", Vector2(x, y), Color::Green);
	//TopRight ²ÀÁþÁ¡
	Renderer::Get().Submit("+", Vector2(x, height), Color::Green);
	//BottomLeft ²ÀÁþÁ¡
	Renderer::Get().Submit("+", Vector2(width, y), Color::Green);
	//BottomRight ²ÀÁþÁ¡
	Renderer::Get().Submit("+", Vector2(width, height), Color::Green);

	//Top
	for (int i = x+1; i < width; i++)
	{
		Renderer::Get().Submit("-", Vector2(i, y), Color::Green);
	}
	//Left
	for (int i = y+1; i < height; i++)
	{
		Renderer::Get().Submit("|", Vector2(x, i), Color::Green);
	}
	//Bottom
	for (int i = x+1; i < width; i++)
	{
		Renderer::Get().Submit("-", Vector2(i, height), Color::Green);
	}
	//Right
	for (int i = y+1; i < height; i++)
	{
		Renderer::Get().Submit("|", Vector2(width, i), Color::Green);
	}
}

void TestLevel::DrawLine(int x, int y, int width, int height)
{
	//TopHalf ²ÀÁþÁ¡
	Renderer::Get().Submit("+", Vector2((width/2), y), Color::Green);
	//RightHalf ²ÀÁþÁ¡
	Renderer::Get().Submit("+", Vector2(width, (height/2)), Color::Green);
	//BottomHalf ²ÀÁþÁ¡
	Renderer::Get().Submit("+", Vector2((width/2), height), Color::Green);
	//LeftHalf ²ÀÁþÁ¡
	Renderer::Get().Submit("+", Vector2(x,(height/2)), Color::Green);

	//Left->Right
	for (int i = (height / 2)+1; i < width; i++)
	{
		Renderer::Get().Submit("-", Vector2(i, height/2), Color::Green);
	}
	//Top-Bottom
	for (int i = (width/2); i < height; i++)
	{
		Renderer::Get().Submit("|", Vector2((width / 2), i), Color::Green);
	}
	
}

