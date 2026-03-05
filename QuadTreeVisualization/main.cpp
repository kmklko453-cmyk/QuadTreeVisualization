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
void drawBox(int x, int y, int w, int h) {
    // 윗변
    for (int i = 0; i < w; i++) {
        gotoxy(x + i, y);
        std::cout << "-";
    }
    // 아랫변
    for (int i = 0; i < w; i++) {
        gotoxy(x + i, y + h);
        std::cout << "-";
    }
    // 왼쪽 세로변
    for (int i = 0; i <= h; i++) {
        gotoxy(x, y + i);
        std::cout << "|";
    }
    // 오른쪽 세로변
    for (int i = 0; i <= h; i++) {
        gotoxy(x + w, y + i);
        std::cout << "|";
    }
    // 모서리 장식
    gotoxy(x, y); std::cout << "+";
    gotoxy(x + w, y); std::cout << "+";
    gotoxy(x, y + h); std::cout << "+";
    gotoxy(x + w, y + h); std::cout << "+";
}

int main()
{

    Engine engine;
    engine.SetNewLevel(new TestLevel);
    engine.Run();

    //drawBox(0, 0, 40, 20);
}