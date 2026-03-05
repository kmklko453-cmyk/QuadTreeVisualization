#pragma once

namespace QuadTreeV
{
	//메인 게임 엔진 클래스 
	class Engine
	{
	public:
		Engine();
		~Engine();

		//엔진루프
		void Run();

		//엔진 종료 함수
		void QuitEngine();

		//기존 키관련 함수 삭제 

	private:
		//Todo: 필요한지 모르겠음/입력 처리 함수  cursor 위치 반환할 떄 사용하면 필요함
		void ProcessInput();

		//업데이트 함수
		void Tick(float deltaTime);

		//그리기 함수 
		void Draw();

	private:
		// 엔진 종료 플래그 
		bool isQuit = false;

	};

}


