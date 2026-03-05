#include<iostream>
#include <Windows.h>

#include "Input.h"

namespace QuadTreeV
{
	Input* Input::instance = nullptr;

	Input::Input()
	{
		//객체가 초기화 되면 자기 자신의 주소를 저장
		instance = this;
	}
	Input::~Input()
	{
	}
	Vector2 QuadTreeV::Input::GetMousePosition()
	{
		POINT pt;
		GetCursorPos(&pt);
		
		return Vector2(static_cast<float>(pt.x), static_cast<float>(pt.y));
		
		
	}

	void QuadTreeV::Input::ProcessInput()
	{
		Vector2 v = Input::Get().GetMousePosition();

		if (!hasPrevMousePos || v != prevMousePos)
		{
			std::cout << "Mouse: " << v.x << ", " << v.y << '\n';
			prevMousePos = v;
			hasPrevMousePos = true;
		}

	}


	Input& Input::Get()
	{
		// 싱글턴(Singleton).
		// 이 함수는 콘텐츠 프로젝트에서 접근함.
		// 따라서 엔진은 이미 초기화 완료 상태.
		if (!instance)
		{
			// 디버그 모드에서만 동작함.
			// 자동으로 중단점 걸림.
			__debugbreak();
		}

		// Lazy-Pattern.
		// 이펙티브 C++에 나옴.
		//static Input instance;
		return *instance;
	}

}
