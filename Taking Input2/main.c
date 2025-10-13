#include "raylib.h"

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Input Mouse");

    Vector2 ballPosition = {-100.0f, -100.0f};
    Color ballColor = DARKBLUE;

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        if(IsKeyPressed(KEY_H)){
            if(IsCursorHidden())
                ShowCursor();
            else
                HideCursor();
        }

        ballPosition = GetMousePosition();

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) ballColor = RED;
        else if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) ballColor = GREEN;
        else if(IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) ballColor = BLACK;
        else ballColor = DARKBLUE;

        BeginDrawing();
            ClearBackground(WHITE);
            DrawCircleV(ballPosition, 40, ballColor);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}