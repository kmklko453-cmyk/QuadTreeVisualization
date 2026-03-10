#include "Engine/Engine.h"
#include "Level/QuadTreeLevel.h"
#include "math/Vector2.h"

#include <iostream>
#include <windows.h>

using namespace QuadTreeV;
int main()
{

    Engine engine;
    engine.SetNewLevel(new QuadTreeLevel);
    engine.Run();

}