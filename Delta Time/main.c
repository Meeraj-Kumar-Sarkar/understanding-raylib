#include "raylib.h"

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Delta-Time Calculation Demo");

    int currentFPS = 60;

    Vector2 deltaCircle = {0, (float)screenHeight/3.0f};
    Vector2 frameCircle = {0, (float)screenHeight*(2.0f/3.0f)};
    
    const float speed = 10.0f;
    const float circleRadius = 32.0f;

    SetTargetFPS(currentFPS);

    while(!WindowShouldClose()){
        float mouseWheel = GetMouseWheelMove();

        if(mouseWheel != 0){
            currentFPS += (int)mouseWheel;
            if(currentFPS < 0) currentFPS = 0;
            SetTargetFPS(currentFPS);
        }

        deltaCircle.x += GetFrameTime()*6.0f*speed;
        frameCircle.x += 0.1f*speed;

        if(deltaCircle.x > screenWidth) deltaCircle.x = 0;
        if(frameCircle.x > screenWidth) frameCircle.x = 0;

        if(IsKeyPressed(KEY_R)){
            deltaCircle.x = 0;
            frameCircle.x = 0;
        }

        BeginDrawing();
        ClearBackground(WHITE);

        DrawCircleV(deltaCircle, circleRadius, RED);
        DrawCircleV(frameCircle, circleRadius, GRAY);

        const char *fpsText = 0;
        if(currentFPS <= 0) fpsText = TextFormat("FPS unllimited (%d)", GetFPS());
        else fpsText = TextFormat("FPS: %d (target: %d)", GetFPS(), currentFPS);
        DrawText(fpsText, 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Frame Time: %02.02f ms", GetFrameTime()), 10, 30, 20, DARKGREEN);
        DrawText(TextFormat("Use scroll wheel of your mouse to control the FPS, r for reset"), 10, 50, 20, DARKGREEN);

        DrawText("FUNC: x += GetFrameTime()*speed", 10, 90, 20, RED);
        DrawText("FUNC: x += speed", 10, 240, 20, BLUE);

        EndDrawing();
    }

    CloseWindow();


    return 0;
}