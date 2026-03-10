#pragma once

#include <Windows.h>

namespace QuadTreeV
{
	// 콘솔에 텍스트 색상 등을 지정할 때 사용할
	// 색상 열거형.
	enum class Color : unsigned short
	{
		Black = 0,
		Blue = FOREGROUND_BLUE,
		Green = BACKGROUND_GREEN,
		Red = FOREGROUND_RED,
		White = Blue | Green | Red,
	};
}