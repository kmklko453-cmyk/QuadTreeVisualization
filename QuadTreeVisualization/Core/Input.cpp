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

	bool Input::TryGetConsoleMousePosition(Vector2& outPos)
	{
		//처음 한번 초기화가 되도록 static 선언 
		static bool initialized = false;
		//콘솔 입력 장치 접근 handle 빈 값을 초기화
		static HANDLE hInput = INVALID_HANDLE_VALUE;

		//초기화 처음 한번만 초기화함 한번 실행 후 initialized =true;
 		if (!initialized)
		{
			//입력 장치 권한 가져오기
			hInput = GetStdHandle(STD_INPUT_HANDLE);
			//획득 실패시 종료
			if (hInput == INVALID_HANDLE_VALUE)
			{
				return false;
			}

			DWORD mode = 0;
			if (!GetConsoleMode(hInput, &mode))
			{
				return false;
			}

			//플래그 연산: 특정 기능을 켜거나 끈다.
			//빠른 편집 모드(복/붙 하는 기능) 드래그시 콘솔을 멈추게 함
			//그 기능을 끄는것
			mode &= ~ENABLE_QUICK_EDIT_MODE;
			//위에 기능을 사용하기 위해 확장 플래그 켜기
			mode |= ENABLE_EXTENDED_FLAGS;
			//콘솔이 마우스 움직임을 감지함
			mode |= ENABLE_MOUSE_INPUT;

			//설정을 셋팅함
			if (!SetConsoleMode(hInput, mode))
			{
				return false;
			}

			initialized = true;
		}

		//이벤트가 있는지 확인 
		DWORD eventCount = 0;
		if (!GetNumberOfConsoleInputEvents(hInput, &eventCount))
		{
			return false;
		}
		//없으면 마우스가 움직이지 않은거임
		if (eventCount == 0)
		{
			return false;
		}

		//입력 마우스 데이터 읽기
		//이벤트 정보를 담을 그릇
		INPUT_RECORD record{};
		//몇 개의 이벤트를 읽었는지 저장할 변수 
		DWORD readCount = 0;

		//버퍼에서 이벤트 1개를 꺼내 record에 저장
		if (!ReadConsoleInput(hInput, &record, 1, &readCount))
		{
			return false;
		}
		//마우스 타입만 가져오기
		if (record.EventType != MOUSE_EVENT)
		{
			return false;
		}
		//record.MouseEvent를 mouse로 부르기
		const MOUSE_EVENT_RECORD& mouse = record.Event.MouseEvent;

		//마우스가 이동 했을 때만 처리
		if (mouse.dwEventFlags != MOUSE_MOVED)
		{
			return false;
		}

		//마우스 좌표저장
		Vector2 next;
		next.x = static_cast<int>(mouse.dwMousePosition.X);
		next.y = static_cast<int>(mouse.dwMousePosition.Y);

		lastMousePosition = next;
		outPos = next;
		return true;
	}

	void Input::ProcessInput()
	{
		Vector2 mousePos;

		TryGetConsoleMousePosition(mousePos);
		
	
	}


	Input& Input::Get()
	{
		// 싱글턴(Singleton).
		// 이 함수는 콘텐츠 프로젝트에서 접근함.
		// 따라서 엔진은 이미 초기화 완료 상태.6
		if (!instance)
		{
			// 자동으로 중단점 걸림.
			__debugbreak();
		}


		//static Input instance;
		return *instance;
	}

}
