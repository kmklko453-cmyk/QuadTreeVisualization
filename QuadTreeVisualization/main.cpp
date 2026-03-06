#include "Engine/Engine.h"
#include "Level/TestLevel.h"
#include "math/Vector2.h"

#include <iostream>
#include <windows.h>

using namespace QuadTreeV;

// 콘솔 커서를 특정 위치(x, y)로 이동시키는 함수
void gotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 사각형 그리기 (x, y: 시작 좌표, w: 가로, h: 세로)


int main()
{

    Engine engine;
    engine.SetNewLevel(new TestLevel);
    engine.Run();

    //drawBox(0, 0, 40, 20);
}