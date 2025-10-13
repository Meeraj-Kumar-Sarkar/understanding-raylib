#include "raylib.h"

#define MAX_GESTURE_STRING 20

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Input Gesture");

    Vector2 touchPosition = {0, 0};
    Rectangle touchArea = {220, 10, screenWidth - 230.0f, screenHeight - 20.0f};

    int gesturesCount = 0;
    char gestureStrings[MAX_GESTURE_STRING][32];

    int currentGesture = GESTURE_NONE;
    int lastGesture = GESTURE_NONE;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        lastGesture = currentGesture;
        currentGesture = GetGestureDetected();
        touchPosition = GetTouchPosition(0);

        if (CheckCollisionPointRec(touchPosition, touchArea) && (currentGesture != GESTURE_NONE))
        {
            if (currentGesture != lastGesture)
            {
                switch (currentGesture)
                {
                case GESTURE_TAP:
                    TextCopy(gestureStrings[gesturesCount], "GESTURE TAP");
                    break;
                case GESTURE_DOUBLETAP:
                    TextCopy(gestureStrings[gesturesCount], "GESTURE DOUBLETAP");
                    break;
                case GESTURE_HOLD:
                    TextCopy(gestureStrings[gesturesCount], "GESTURE HOLD");
                    break;
                case GESTURE_DRAG:
                    TextCopy(gestureStrings[gesturesCount], "GESTURE DRAG");
                    break;
                case GESTURE_SWIPE_RIGHT:
                    TextCopy(gestureStrings[gesturesCount], "GESTURE SWIPE RIGHT");
                    break;
                case GESTURE_SWIPE_LEFT:
                    TextCopy(gestureStrings[gesturesCount], "GESTURE SWIPE LEFT");
                    break;
                case GESTURE_SWIPE_UP:
                    TextCopy(gestureStrings[gesturesCount], "GESTURE SWIPE UP");
                    break;
                case GESTURE_SWIPE_DOWN:
                    TextCopy(gestureStrings[gesturesCount], "GESTURE SWIPE DOWN");
                    break;
                case GESTURE_PINCH_IN:
                    TextCopy(gestureStrings[gesturesCount], "GESTURE PINCH IN");
                    break;
                case GESTURE_PINCH_OUT:
                    TextCopy(gestureStrings[gesturesCount], "GESTURE PINCH OUT");
                    break;
                default:
                    break;
                }

                gesturesCount++;

                if (gesturesCount >= MAX_GESTURE_STRING)
                {
                    for (int i = 0; i < MAX_GESTURE_STRING; i++)
                        TextCopy(gestureStrings[i], "\0");

                    gesturesCount = 0;
                }
            }
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRec(touchArea, GRAY);
        DrawRectangle(225, 15, screenWidth - 240, screenHeight - 30, RAYWHITE);
        DrawText("GESTURES TEST AREA", screenWidth - 270, screenHeight - 40, 20, Fade(GRAY, 0.5f));

        for (int i = 0; i < gesturesCount; i++)
        {
            if (i % 2 == 0)
                DrawRectangle(10, 30 + 20 * i, 200, 20, Fade(LIGHTGRAY, 0.5f));
            else
                DrawRectangle(10, 30 + 20 * i, 200, 20, Fade(LIGHTGRAY, 0.3f));

            if (i < gesturesCount - 1)
                DrawText(gestureStrings[i], 35, 36 + 20 * i, 10, DARKGRAY);
            else
                DrawText(gestureStrings[i], 35, 36 + 20 * i, 10, MAROON);
        }

        DrawRectangleLines(10, 29, 200, screenHeight - 50, GRAY);
        DrawText("DETECTED GESTURES", 50, 15, 10, GRAY);

        if (currentGesture != GESTURE_NONE)
            DrawCircleV(touchPosition, 30, MAROON);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}