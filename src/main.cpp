#include <iostream>
#include <raylib.h>
#include <string>
#include <ctime>
#include <vector>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int score;
int highscore;
bool settings = false;
float ButtonSize = 64;

void StartGame() {
    
}


void DrawGameMenu()
{
    int old = GuiGetStyle(BUTTON, BASE_COLOR_NORMAL);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(GREEN));
    if (GuiButton({
    (GetRenderWidth() - ButtonSize * 6) / 2.0f,
    (GetRenderHeight() - ButtonSize) / 2.5f,
    ButtonSize * 6,
    ButtonSize
}, "Graj")) {
    StartGame();
}
GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, old);
}



int main() {
InitWindow(800, 1000, "sth");
GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
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