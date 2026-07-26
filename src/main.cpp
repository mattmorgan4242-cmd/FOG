#include <iostream>
#include <raylib.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int score;
int highscore;
bool settings = false;
bool exitGame = false;
bool game = false;
float ButtonSize = 64;
Vector2 player = {375, 800};
float playerSize = 50;
float playerSpeed = 300;




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
    game = true;
}
GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, old);
if (GuiButton({
    (GetRenderWidth() - ButtonSize * 6) / 2.0f,
    (GetRenderHeight() - ButtonSize) / 2.0f,
    ButtonSize * 6,
    ButtonSize
}, "Ustawienia")) {
    settings = true;
}
GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(RED));
    if (GuiButton({
    (GetRenderWidth() - ButtonSize * 6) / 2.0f,
    (GetRenderHeight() - ButtonSize) / 1.65f,
    ButtonSize * 6,
    ButtonSize
}, "Wyjdz")) {
    exitGame = true;
}
GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, old);
}
void DrawSettings()
{
    DrawText("USTAWIENIA", (GetScreenWidth() - MeasureText("USTAWIENIA", 40)) / 2, 100, 40, WHITE);

    if (GuiButton({(GetScreenWidth() - 250) / 2.0f, 750, 250, 60}, "Powrot"))
    {
        settings = false;
    }
}

void DrawGame() {
 if (IsKeyDown(KEY_LEFT))
    {
        player.x -= playerSpeed * GetFrameTime();
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        player.x += playerSpeed * GetFrameTime();
    }

    if (player.x < 0)
    {
        player.x = 0;
    }

    if (player.x + playerSize > GetScreenWidth())
    {
        player.x = GetScreenWidth() - playerSize;
    }

    DrawRectangle(player.x, player.y, playerSize, playerSize * 2, BLUE);
}



int main() {
    srand(time(0));
InitWindow(800, 1000, "sth");
GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
SetTargetFPS(60);
while (!WindowShouldClose() && !exitGame)
{
BeginDrawing();
ClearBackground(BLACK);

    if (game)
        {
            DrawGame();
        }
        else if (settings)
        {
            DrawSettings();
        }
        else
        {
            DrawGameMenu();
        }


EndDrawing();
}

CloseWindow();
return 0;
}