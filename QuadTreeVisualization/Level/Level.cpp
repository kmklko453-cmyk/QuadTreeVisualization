#include "Level.h"
#include "Actor/Actor.h"

QuadTreeV::Level::Level()
{
}

QuadTreeV::Level::~Level()
{
	//메모리 정리
	for (Actor*& actor : actors)
	{
		//메모리 해제
		if (actor)
		{
			delete actor;
			actor = nullptr;
		}
	}
	
	//배열 초기화
	actors.clear();
}

void QuadTreeV::Level::BeginPlay()
{
	//액터에 이벤트 흘리기
	for (Actor* actor : actors)
	{
		
		actor->BeginPlay();
	}
}

void QuadTreeV::Level::Tick(float deltaTime)
{
	// 액터에 이벤트 흘리기.
	for (Actor* actor : actors)
	{
		actor->Tick(deltaTime);
	}
}
void QuadTreeV::Level::Draw()
{
	// 액터에 이벤트 흘리기.
	for (Actor* actor : actors)
	{
		actor->Draw();
	}
}

void QuadTreeV::Level::AddNewActor(Actor* newActor)
{
	actors.emplace_back(newActor);
}
