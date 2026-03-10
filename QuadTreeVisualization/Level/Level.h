#pragma once
#include <vector>

namespace QuadTreeV
{
	class Level
	{
	public:
		Level();
		virtual ~Level();

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();
	};

}


