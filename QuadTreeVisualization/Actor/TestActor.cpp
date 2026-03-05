#include "TestActor.h"
#include <iostream>

void TestActor::BeginPlay()
{
	//이벤트 흐름에 탑승용
	Actor::BeginPlay();
	
	//std::cout << "TestActor::BeginPlay()\n";
}

void TestActor::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	//std::cout << "TestActor::Tick(). deltaTime: " << deltaTime << ", FPS: " << (1.0f / deltaTime) << "\n";
}

void TestActor::Draw()
{ 
	Actor::Draw();
}
