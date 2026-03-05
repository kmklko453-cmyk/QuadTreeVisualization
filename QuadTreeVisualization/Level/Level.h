#pragma once
#include <vector>

namespace QuadTreeV
{
	//전방 선언
	class Actor;
	
		class Level
	{
	public:
		Level();
		virtual ~Level();

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		//액터 추가 함수
		void AddNewActor(Actor* newActor);

	protected:
		//액터 배열 

		std::vector<Actor*> actors;

	};

}


