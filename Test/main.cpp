#include <windows.h>
#include <iostream>

int main()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    if (hInput == INVALID_HANDLE_VALUE)
    {
        std::cout << "GetStdHandle failed\n";
        return 1;
    }

    DWORD prevMode = 0;
    if (!GetConsoleMode(hInput, &prevMode))
    {
        std::cout << "GetConsoleMode failed\n";
        return 1;
    }

    // Quick Edit 끄고, 마우스 입력 켜기
    DWORD newMode = prevMode;
    newMode &= ~ENABLE_QUICK_EDIT_MODE;
    newMode |= ENABLE_EXTENDED_FLAGS;
    newMode |= ENABLE_MOUSE_INPUT;

    if (!SetConsoleMode(hInput, newMode))
    {
        std::cout << "SetConsoleMode failed\n";
        return 1;
    }

    std::cout << "콘솔 안에서 마우스를 움직이거나 클릭해봐.\n";
    std::cout << "ESC 누르면 종료.\n\n";

    INPUT_RECORD record;
    DWORD readCount = 0;

    while (true)
    {
        if (!ReadConsoleInput(hInput, &record, 1, &readCount))
        {
            std::cout << "ReadConsoleInput failed\n";
            break;
        }

        if (record.EventType == KEY_EVENT &&
            record.Event.KeyEvent.bKeyDown &&
            record.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
        {
            break;
        }

        if (record.EventType == MOUSE_EVENT)
        {
            const MOUSE_EVENT_RECORD& mouse = record.Event.MouseEvent;

            SHORT x = mouse.dwMousePosition.X;
            SHORT y = mouse.dwMousePosition.Y;

            // 이동
            if (mouse.dwEventFlags == MOUSE_MOVED)
            {
                std::cout << "Move  : " << x << ", " << y << "\n";
            }
            // 클릭/버튼 상태 변화 (dwEventFlags == 0)
            else if (mouse.dwEventFlags == 0)
            {
                if (mouse.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
                {
                    std::cout << "LClick: " << x << ", " << y << "\n";
                }
                else if (mouse.dwButtonState & RIGHTMOST_BUTTON_PRESSED)
                {
                    std::cout << "RClick: " << x << ", " << y << "\n";
                }
                else
                {
                    std::cout << "Release: " << x << ", " << y << "\n";
                }
            }
        }
    }

    // 원래 모드 복구
    SetConsoleMode(hInput, prevMode);
    return 0;
}