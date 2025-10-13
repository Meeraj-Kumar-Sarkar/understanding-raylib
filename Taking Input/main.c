#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Input Taking");

    Vector2 ballPosition = {(float)screenWidth/2, (float)screenHeight/2};

    SetTargetFPS(60);
    
    while(!WindowShouldClose()){
        if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) ballPosition.x += 2.0f;
        if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) ballPosition.x -= 2.0f;
        if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) ballPosition.y -= 2.0f;
        if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) ballPosition.y += 2.0f;

        BeginDrawing();
        ClearBackground(WHITE);

        DrawCircleV(ballPosition, 50, MAGENTA);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}