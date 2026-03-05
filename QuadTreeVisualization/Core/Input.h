#pragma once
#include "Math/Vector2.h"

namespace QuadTreeV
{
	class Input
	{
		friend class Engine;

	private:
		Input();
		~Input();

	public:
		//마우스 포지션 전달해주는 함수
		Vector2 GetMousePosition();
		
		void ProcessInput();

		// 전역적으로 접근하는 함수.
		static Input& Get();

	private:
		static Input* instance;
	
		//마우스 이전 위치 저장 변수
		Vector2 prevMousePos;
		bool hasPrevMousePos = false;
	};
}

