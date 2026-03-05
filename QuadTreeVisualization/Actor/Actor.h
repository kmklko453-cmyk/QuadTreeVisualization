#pragma once

namespace QuadTreeV
{
class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Draw();

protected:

};

}


