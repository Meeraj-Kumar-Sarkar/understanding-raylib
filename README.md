# Learning Raylib Through a Tile Match Game

This document provides a detailed walkthrough of how **Raylib** works by studying a simple **tile-matching puzzle game** written in C. The goal is to teach beginners the **fundamentals of Raylib**, including graphics, input handling, animation, and game loop design, by breaking down how each part of the code operates.

---

## 🎯 Purpose of This Project

Instead of focusing on gameplay mechanics, this project emphasizes understanding **how Raylib functions** and how to use it effectively in your first graphical C program. By the end, you should understand how to:

* Initialize and configure Raylib for a game window.
* Draw text and shapes using Raylib’s rendering system.
* Handle player input (mouse clicks).
* Manage real-time animations and updates.
* Organize game logic inside Raylib’s main loop.

This project acts as a strong foundation for learning **2D game development** using Raylib.

---

## ⚙️ 1. Raylib Initialization

Every Raylib program begins with setting up the window and the frame rate.

```c
InitWindow(width, height, "Tile Match Game");
SetTargetFPS(60);
```

* `InitWindow()` creates a window with the specified width, height, and title.
* `SetTargetFPS(60)` makes sure that the game updates 60 times per second, ensuring smooth visuals.

When the window is created, Raylib also sets up an OpenGL context and prepares to draw graphical elements each frame.

### Exiting the Game

Raylib automatically handles the window’s close button. You can check if the user wants to exit using:

```c
while (!WindowShouldClose()) {
    // game logic here
}
```

When the user closes the window, this loop ends, and you can call `CloseWindow()` to properly release resources.

---

## 🧱 2. Representing the Game Board

The grid (or board) is the main visual element of the game. It’s defined using a 2D array of characters:

```c
#define BOARD_SIZE 8
char board[BOARD_SIZE][BOARD_SIZE];
```

This creates an 8×8 board, where each element represents a tile. The tile’s symbol (`#, $, %, &, @`) is used to determine its type and color.

### Tile Randomization

The following function assigns random tile symbols:

```c
char random_tile() {
    return tile_chars[rand() % TILE_TYPES];
}
```

Here:

* `rand()` generates a random integer.
* The modulo operator `% TILE_TYPES` ensures the value is within the valid range of tile types.
* The returned character is stored in the grid.

This creates variety and ensures that each time you play, the board looks different.

---

## 🎨 3. Drawing Graphics with Raylib

One of Raylib’s main advantages is its **simple drawing API**. Every frame, you use a pair of functions to render graphics:

```c
BeginDrawing();
ClearBackground(RAYWHITE);

// Draw shapes and text here

EndDrawing();
```

### How It Works

* `BeginDrawing()` starts a new frame.
* `ClearBackground()` clears the old frame with a background color.
* You then draw everything for the new frame — tiles, text, and score.
* `EndDrawing()` presents that frame on screen.

This cycle repeats 60 times per second, making your game appear animated.

### Drawing Tiles

Tiles are drawn as rectangles or symbols on the screen:

```c
DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, color);
DrawText(TextFormat("%c", board[y][x]), x + 10, y + 8, 24, BLACK);
```

Each tile’s position is determined by multiplying its grid index by `TILE_SIZE`. This ensures consistent spacing across the grid.

---

## 🖱️ 4. Handling User Input

Raylib provides intuitive input functions to detect key and mouse events.

For example, to detect a left mouse click:

```c
if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Vector2 mouse = GetMousePosition();
}
```

### Selecting and Swapping Tiles

The program converts the mouse coordinates to grid coordinates:

```c
int tile_x = (mouse.x - grid_origin.x) / TILE_SIZE;
int tile_y = (mouse.y - grid_origin.y) / TILE_SIZE;
```

When the player selects two tiles, the program checks if they are adjacent:

```c
bool are_tiles_adjacent(Vector2 a, Vector2 b) {
    return (abs((int)a.x - (int)b.x) + abs((int)a.y - (int)b.y)) == 1;
}
```

If they are, their values are swapped in the `board` array.

---

## 🔍 5. Detecting Matches

After each move, the game scans the board for three or more identical tiles in a row or column. The matching logic works like this:

```c
for (int y = 0; y < BOARD_SIZE; y++) {
    for (int x = 0; x < BOARD_SIZE - 2; x++) {
        char t = board[y][x];
        if (t == board[y][x + 1] && t == board[y][x + 2]) {
            match[y][x] = match[y][x + 1] = match[y][x + 2] = true;
        }
    }
}
```

The `match[][]` array stores `true` where matching tiles are found. These tiles are later replaced by new ones.

This teaches beginners how to handle **pattern detection** and **logical grid scanning** in C.

---

## 🌀 6. Making Tiles Fall (Basic Animation)

When tiles disappear, empty spaces appear on the board. To simulate gravity, the tiles above should fall down. This is handled using an offset value:

```c
fall_offset[y][x] += fall_speed * GetFrameTime();
```

* `fall_offset` stores how far each tile has visually moved.
* `GetFrameTime()` returns the time between frames, ensuring smooth movement even if frame rate fluctuates.

Once a tile reaches its final position, it’s locked in place, and the offset resets to zero.

This introduces beginners to the **concept of frame-based animation** — updating positions incrementally each frame.

---

## 🔁 7. The Main Game Loop

All Raylib programs use the same loop structure:

```c
while (!WindowShouldClose()) {
    // 1. Handle input
    // 2. Update game state
    // 3. Draw the scene
}
```

Inside this loop:

* You first capture user input (like mouse clicks).
* Then you update the board based on any changes or matches.
* Finally, you redraw everything for the new frame.

This loop structure is essential to understand because **every Raylib project**, from small demos to full games, follows this pattern.

---

## 🧰 8. Concepts Learned from This Project

By studying this program, you learn the following Raylib fundamentals:

### 1. **Window and Frame Management**

Understanding how Raylib sets up a render window and manages frame updates.

### 2. **Rendering Shapes and Text**

Using simple draw functions to render game elements like tiles and text.

### 3. **Event Handling**

Capturing mouse input and translating it into game logic.

### 4. **Animation with Frame Timing**

Using `GetFrameTime()` to create smooth animations.

### 5. **Game Loop Architecture**

Building a continuous cycle that updates game logic and visuals every frame.

### 6. **Logical Thinking and Array Manipulation**

Managing a 2D grid efficiently using arrays and understanding adjacency and pattern matching.

---

**Author:** Meeraj

**Purpose:** Introduction to Raylib

**Language:** C

**Library:** Raylib

**Platform:** Linux (tested on Arch Linux -> [Omarchy](http://omarchy.org) )

**External Links:** [Raylib](www.raylib.com)
