#include "Engine.h"
#include <iostream>
#include <Windows.h>

QuadTreeV::Engine::Engine()
{
}

QuadTreeV::Engine::~Engine()
{
}

void QuadTreeV::Engine::Run()
{
	//시계 정밀도
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	//프레임 계산용 변수
	int64_t currentTime = 0;
	int64_t previousTime = 0;

	//하드웨어 타이머로 시간 구하기
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	//엔진 시작 직전 현재 이전 값을 맞춤
	currentTime = time.QuadPart;
	previousTime = currentTime;

	//기준 프레임 (단위: 초)
	float targetFramerate = 30.0f;
	float oneFrameTime = 1.0f / targetFramerate;

	//엔진 루프
	while (!isQuit)
	{
		//현재 시간 구하기
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		//프레임 계산 
		float deltaTime = static_cast<float>(currentTime - previousTime);

		//초단위 변화
		deltaTime = deltaTime / static_cast<float>(frequency.QuadPart);

		//프레임 고정 기법
		if (deltaTime >= oneFrameTime)
		{
			ProcessInput();

			//프레임 처리
			Tick(deltaTime);
			Draw();

			//이전 시간 값 갱신
			previousTime = currentTime;
		}
	}

	std::cout << "Engine has been shutdown....\n";
}

void QuadTreeV::Engine::QuitEngine()
{
	isQuit = true;
}

void QuadTreeV::Engine::ProcessInput()
{
}

void QuadTreeV::Engine::Tick(float deltaTime)
{
	std::cout << "DelteTime: " << deltaTime << " FPS: " << (1.0f / deltaTime) << "\n";

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		QuitEngine();
	}
}

void QuadTreeV::Engine::Draw()
{
}
