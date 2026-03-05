#pragma once

#include "Actor.h"

class TestActor : public QuadTreeV::Actor
{
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

};

