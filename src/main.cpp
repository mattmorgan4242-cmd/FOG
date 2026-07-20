#include <iostream>
#include <raylib.h>
#include <string>
#include <ctime>
#include <vector>
#include <raygui.h>

void DrawGameMenu()
{

}



int main() {
InitWindow(800, 1000, "sth");
SetTargetFPS(60);
 while (!WindowShouldClose()) {
BeginDrawing();
ClearBackground(BLACK);
DrawGameMenu();


EndDrawing();
}

//CloseWindow();
return 0;
}