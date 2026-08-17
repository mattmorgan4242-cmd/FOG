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
int hp = 5;
bool settings = false;
bool exitGame = false;
bool game = false;
float ButtonSize = 64;
Vector2 player = {375, 750};
float playerSize = 100;
float playerSpeed = 500;
bool gameOver = false;
Texture2D logo;
Texture2D bag;
Texture2D apple_red;
Texture2D apple_green;
Texture2D bear_green;
Texture2D bear_blue;
Texture2D bear_red;


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
    DrawText(TextFormat("Score: %d", score), 20, 20, 30, WHITE);
    DrawText(TextFormat("HP: %d", hp), GetScreenWidth() - MeasureText(TextFormat("HP: %d", hp), 30) - 20, 20, 30, WHITE);
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

for (int i = objects.size() - 1; i >= 0; i--)
{
    objects[i].position.y += objects[i].speed * GetFrameTime();

    Rectangle playerRect = {player.x, player.y, playerSize, playerSize * 1.5f};
    Rectangle objectRect = {objects[i].position.x, objects[i].position.y, objects[i].size, objects[i].size};

    if (CheckCollisionRecs(playerRect, objectRect))
    {
        objects.erase(objects.begin() + i);
        score++;
        continue;
    }
    if (objects[i].position.y + objects[i].size >= GetScreenHeight())
    {
        objects.erase(objects.begin() + i);
        hp--;
        continue;
    }
    if (hp <= 0)
    {
        gameOver = true;
    }


    DrawTexturePro(apple_red, {0, 0, (float)apple_red.width, (float)apple_red.height}, {objects[i].position.x, objects[i].position.y, objects[i].size, objects[i].size}, {0, 0}, 0.0f, WHITE);
}
}
void DrawGameOver()
{
    DrawText("GAME OVER", (GetScreenWidth() - MeasureText("GAME OVER", 60)) / 2, 250, 60, RED);
    DrawText(TextFormat("Score: %d", score), (GetScreenWidth() - MeasureText(TextFormat("Score: %d", score), 30)) / 2, 330, 30, WHITE);

    if (GuiButton({250, 450, 300, 60}, "Zagraj jeszcze raz"))
    {
        score = 0;
        hp = 5;
        objects.clear();
        player.x = 375;
        gameOver = false;
    }

    if (GuiButton({250, 530, 300, 60}, "Powrot do menu"))
    {
        score = 0;
        hp = 5;
        objects.clear();
        player.x = 375;
        game = false;
        gameOver = false;
    }
}



int main() {
    srand(time(0));
InitWindow(800, 1000, "Falling Objects Game");
logo = LoadTexture("textures/FOG.png");
bag = LoadTexture("textures/bag.png");
apple_red = LoadTexture("textures/apple_red.png");
apple_green = LoadTexture("textures/apple_green.png");
bear_blue = LoadTexture("textures/bear_blue.png");
bear_green = LoadTexture("textures/bear_green.png");
bear_red = LoadTexture("textures/bear_red.png");
GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
SetTargetFPS(60);
while (!WindowShouldClose() && !exitGame)
{
BeginDrawing();
ClearBackground(BLACK);


    if (gameOver)
        {
            DrawGameOver();
        }
        else if (game)
        {
            DrawGame();
        }
        else if (gameOver)
        {
            DrawGameOver();
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