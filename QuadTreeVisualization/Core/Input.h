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
		//콘솔 창안에서 마우스 좌표 구하는 함수
		bool TryGetConsoleMousePosition(Vector2& outPos);

		void ProcessInput();

		// 전역적으로 접근하는 함수.
		static Input& Get();

		//Getter
		const Vector2& GetMousePosition() const { return lastMousePosition; }

	private:
		static Input* instance;
	
		//마우스 정보 저장용
		Vector2 lastMousePosition{ 0, 0 };
	};
}

