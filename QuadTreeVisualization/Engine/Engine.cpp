#include "Engine.h"
#include "Level/Level.h"
#include "Core/Input.h"`r`n#include "Renderer/Renderer.h"

#include <iostream>
#include <Windows.h>


QuadTreeV::Engine::Engine()
{
	input = new Input();
}

QuadTreeV::Engine::~Engine()
{
	//메인 레벨 제거
	if (mainLevel)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}

	if (input)
	{
		delete input;
		input = nullptr;
	}

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
			input->ProcessInput();

			//프레임 처리
			BeginPlay();
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

void QuadTreeV::Engine::SetNewLevel(Level* newLevel)
{
	//기존 레벨 있는지 확인 
	//있으면 기존 레벨 제거
	if (mainLevel)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}

	//레벨 설정
	mainLevel = newLevel;
}


void QuadTreeV::Engine::BeginPlay()
{
	//레벨이 있으면 이벤트 전달
	if (!mainLevel)
	{
		std::cout << "mainLevel is empty.\n";
		return;
	}

	mainLevel->BeginPlay();
}

void QuadTreeV::Engine::Tick(float deltaTime)
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		QuitEngine();
	}

	//레벨에 이벤트 흘리기
	//예외처리
	if (!mainLevel)
	{
		QuitEngine();
		std::cout << "Error: Engine::Tick(). mainLevel is empty\n";
		return;
	}

	mainLevel->Tick(deltaTime);
}

void QuadTreeV::Engine::Draw()
{
	//레벨에 이벤트 흘리기
	//예외처리
	if (!mainLevel)
	{
		std::cout << "Error: Engine::Draw(). mainLevel is empty\n";
		return;
	}

	mainLevel->Draw();

}
