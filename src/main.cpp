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
Vector2 player = {375, 750};
float playerSize = 100;
float playerSpeed = 500;
Texture2D logo;
Texture2D bag;
Texture2D apple_red;
Texture2D apple_green;


struct FallingObject
{
    Vector2 position;
    float speed;
    float size;
};

std::vector<FallingObject> objects;
float spawnTimer = 0.0f;

void DrawGameMenu()
{
    DrawTexturePro(logo, {0, 0, (float)logo.width, (float)logo.height}, {(GetScreenWidth() - 400) / 2.0f, 100, 400, 200}, {0, 0}, 0.0f, WHITE);
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

    DrawTexturePro(bag, {0, 0, (float)bag.width, (float)bag.height}, {player.x, player.y, playerSize, playerSize * 1.5f}, {0, 0}, 0.0f, WHITE);

    spawnTimer += GetFrameTime();

    if (spawnTimer >= 2.0f)
    {
        spawnTimer = 0.0f;

        FallingObject object;
        object.position = {(float)GetRandomValue(0, GetScreenWidth() - 30), -30};
        object.speed = 100;
        object.size = 50;

        objects.push_back(object);
    }

    for (auto &object : objects)
    {
        object.position.y += object.speed * GetFrameTime();

        DrawTexturePro(apple_red, {0, 0, (float)apple_red.width, (float)apple_red.height}, {object.position.x, object.position.y, object.size, object.size}, {0, 0}, 0.0f, WHITE);
    }
}



int main() {
    srand(time(0));
InitWindow(800, 1000, "Falling Objects Game");
logo = LoadTexture("textures/FOG.png");
bag = LoadTexture("textures/bag.png");
apple_red = LoadTexture("textures/apple_red.png");
apple_green = LoadTexture("textures/apple_green.png");
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