#pragma once

namespace QuadTreeV
{
	// 전방 선언.
	class Input;
	class Renderer;
	//메인 게임 엔진 클래스 
	class Engine
	{

		// 엔진 설정 구조체.
		struct EngineSetting
		{
			// 프레임 속도.
			float framerate = 30.0f;

			// 화면 너비.
			int width = 500;

			// 화면 높이.
			int height = 500;
		};

	public:
		Engine();
		~Engine();

		//엔진루프
		void Run();

		//엔진 종료 함수
		void QuitEngine();

		//기존 키관련 함수 삭제 

		//새 레벨을 추가(설정) 하는 함수
		void SetNewLevel(class Level* newlevel);


	private:
		//엔진 시작 함수
		void BeginPlay();

		//업데이트 함수
		void Tick(float deltaTime);

		//그리기 함수 
		void Draw();
	private:
		// 엔진 종료 플래그 
		bool isQuit = false;

		// 엔진 설정 값.
		EngineSetting setting;

		// 입력 관리자.
		Input* input = nullptr;

		// 렌더러 객체.
		Renderer* renderer = nullptr;

		//메인 레벨
		class Level* mainLevel = nullptr;

	};
}

