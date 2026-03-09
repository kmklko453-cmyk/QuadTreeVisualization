#pragma once

#include "Math/Vector2.h"

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

		void SetPosition(const Vector2& newPosition);

		//Getter
		inline bool HasBeganPlay() const { return hasBeganPlay; }


	protected:
		//이미 BeginPlay 이벤트를 받았는지 여부
		bool hasBeganPlay = false;

		//활성화 상태 여부
		bool isActive = true;

		//현재 프레임에 삭제 요청 받았는지 여부 
		bool destroyRequested = false;

	private:
		//위치
		Vector2 potition;
	};

}


