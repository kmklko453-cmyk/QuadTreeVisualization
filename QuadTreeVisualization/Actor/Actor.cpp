#include "Actor.h"


QuadTreeV::Actor::Actor()
{
}

QuadTreeV::Actor::~Actor()
{
}

void QuadTreeV::Actor::BeginPlay()
{
	//이벤트를 받은 후 플래그 설정
	hasBeganPlay = true;
}

void QuadTreeV::Actor::Tick(float deltaTime)
{
}

void QuadTreeV::Actor::Draw()
{
}

