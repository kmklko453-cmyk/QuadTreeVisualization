#pragma once

#include "Actor/Actor.h"

class QuadTree : public QuadTreeV::Actor
{
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

};

