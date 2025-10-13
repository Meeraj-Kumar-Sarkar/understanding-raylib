#include "raylib.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define BOARD_SIZE 8
#define TILE_SIZE 42
#define TILE_TYPES 5
#define SCORE_FONT_SIZE 38

const char tile_chars[TILE_TYPES] = {'#', '$', '%', '&', '@'};

Vector2 grid_origin;
char board[BOARD_SIZE][BOARD_SIZE];
bool match[BOARD_SIZE][BOARD_SIZE] = {0};
float fall_offset[BOARD_SIZE][BOARD_SIZE] = {0};
int score = 0;
Font score_font;
Vector2 selected_tile = {-1, -1};
float fall_speed = 8.0f;
bool is_animating = false; // Track if animations are in progress

char random_tile()
{
    return tile_chars[rand() % TILE_TYPES];
}

void swap_tiles(int x1, int y1, int x2, int y2)
{
    char temp = board[y1][x1];
    board[y1][x1] = board[y2][x2];
    board[y2][x2] = temp;
}

bool are_tiles_adjacent(Vector2 a, Vector2 b)
{
    return (abs((int)a.x - (int)b.x) + abs((int)a.y - (int)b.y)) == 1;
}

bool find_matches()
{
    bool found = false;
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            match[y][x] = false;
        }
    }

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE - 2; x++)
        {
            char t = board[y][x];
            if (t == board[y][x + 1] && t == board[y][x + 2])
            {
                match[y][x] = match[y][x + 1] = match[y][x + 2] = true;
                score += 10;
                found = true;
            }
        }
    }

    for (int y = 0; y < BOARD_SIZE - 2; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            char t = board[y][x];
            if (t == board[y + 1][x] && t == board[y + 2][x])
            {
                match[y][x] = match[y + 1][x] = match[y + 2][x] = true;
                score += 10;
                found = true;
            }
        }
    }
    return found;
}

void resolve_matches()
{
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        int write_y = BOARD_SIZE - 1;
        for (int y = BOARD_SIZE - 1; y >= 0; y--)
        {
            if (!match[y][x])
            {
                if (y != write_y)
                {
                    board[write_y][x] = board[y][x];
                    fall_offset[write_y][x] = (write_y - y) * TILE_SIZE;
                    board[y][x] = ' ';
                }
                write_y--;
            }
        }
        while (write_y >= 0)
        {
            board[write_y][x] = random_tile();
            fall_offset[write_y][x] = (write_y + 1) * TILE_SIZE;
            write_y--;
        }
    }
    is_animating = true; // Set animating flag
}

void update_fall_offsets()
{
    bool any_falling = false;
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (fall_offset[y][x] > 0)
            {
                fall_offset[y][x] -= fall_speed;
                if (fall_offset[y][x] < 0)
                {
                    fall_offset[y][x] = 0;
                }
                any_falling = true;
            }
        }
    }
    is_animating = any_falling;
}

void init_board()
{
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            board[y][x] = random_tile();
        }
    }
}

int main()
{
    const int screen_width = 800;
    const int screen_height = 450;

    InitWindow(screen_width, screen_height, "Raylib Match-3 Game");
    SetTargetFPS(60);
    srand(time(NULL));

    // Initialize grid origin after window creation
    int grid_width = BOARD_SIZE * TILE_SIZE;
    int grid_height = BOARD_SIZE * TILE_SIZE;
    grid_origin = (Vector2){
        (screen_width - grid_width) / 2.0f,
        (screen_height - grid_height) / 2.0f};

    // Load font with error handling
    score_font = LoadFontEx("assets/04b03.ttf", SCORE_FONT_SIZE, NULL, 0);
    if (score_font.baseSize == 0)
    {
        score_font = GetFontDefault(); // Fallback to default font
    }

    init_board();
    Vector2 mouse = {0, 0};

    while (!WindowShouldClose())
    {
        // Update game logic
        mouse = GetMousePosition();
        update_fall_offsets(); // Update falling animations

        if (!is_animating)
        { // Only allow input if no animations are in progress
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                int x = (mouse.x - grid_origin.x) / TILE_SIZE;
                int y = (mouse.y - grid_origin.y) / TILE_SIZE;

                if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
                {
                    Vector2 current_tile = (Vector2){(float)x, (float)y};
                    if (selected_tile.x < 0)
                    {
                        selected_tile = current_tile;
                    }
                    else
                    {
                        if (are_tiles_adjacent(selected_tile, current_tile))
                        {
                            swap_tiles((int)selected_tile.x, (int)selected_tile.y, (int)current_tile.x, (int)current_tile.y);
                            if (find_matches())
                            {
                                resolve_matches();
                            }
                            else
                            {
                                swap_tiles((int)selected_tile.x, (int)selected_tile.y, (int)current_tile.x, (int)current_tile.y);
                            }
                            selected_tile = (Vector2){-1, -1};
                        }
                        else
                        {
                            selected_tile = current_tile;
                        }
                    }
                }
            }

            // Check for new matches after resolving previous ones
            if (find_matches())
            {
                resolve_matches();
            }
        }

        // Render
        BeginDrawing();
        ClearBackground(BLACK);

        for (int y = 0; y < BOARD_SIZE; y++)
        {
            for (int x = 0; x < BOARD_SIZE; x++)
            {
                Rectangle rect = {
                    grid_origin.x + (x * TILE_SIZE),
                    grid_origin.y + (y * TILE_SIZE) - fall_offset[y][x],
                    TILE_SIZE,
                    TILE_SIZE};
                DrawRectangleLinesEx(rect, 1, GRAY);

                if (board[y][x] != ' ')
                {
                    DrawTextEx(
                        score_font,
                        TextFormat("%c", board[y][x]),
                        (Vector2){rect.x + 15, rect.y + 10},
                        20,
                        1,
                        match[y][x] ? GREEN : WHITE);
                }
            }
        }

        if (selected_tile.x >= 0)
        {
            DrawRectangleLinesEx(
                (Rectangle){
                    grid_origin.x + (selected_tile.x * TILE_SIZE),
                    grid_origin.y + (selected_tile.y * TILE_SIZE),
                    TILE_SIZE, TILE_SIZE},
                2, YELLOW);
        }

        DrawTextEx(
            score_font,
            TextFormat("SCORE: %d", score),
            (Vector2){20, 20},
            SCORE_FONT_SIZE,
            1.0f,
            RED);

        EndDrawing();
    }

    UnloadFont(score_font);
    CloseWindow();
    return 0;
}