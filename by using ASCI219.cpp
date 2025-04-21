#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;

// Maze dimensions
const int WIDTH = 31, HEIGHT = 15;

// Player settings
char player = 'P';
int posX = 1, posY = 1;  // Player's starting position
char action;
int movesTaken = 0;
int score = 0;
int currentLevel = 1;
bool levelCompleted = false;

// Structure for enemy properties
struct Enemy {
    char symbol;
    bool active;
    int x, y;
};

// Original maze for Level 1 (not modified during play)
const unsigned char originalMazeLevel1[HEIGHT][WIDTH] = {
    // 15 rows of 31 characters each, using ASCII 219 for walls
    // Use ' ', '*', 'E', and other characters to define paths, collectibles, end goal, etc.
    {219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
    {219,' ',' ',' ',219,219,219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',219},
    {219,219,'*',219,219,' ',' ',' ',219,' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,219,219},
    {219,' ',' ',219,' ',' ',' ',219,219,' ',219,' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219},
    {219,' ','*',219,219,219,' ',219,' ',' ',219,' ',219,219,219,219,219,' ',219,' ',219,219,219,219,219,' ',219,219,219,219,219},
    {219,' ',' ',' ',' ',' ',' ',219,' ',219,219,' ',219,' ',' ',' ',' ',' ',219,' ',219,' ',' ',' ',' ',' ',219,' ',' ',' ',219},
    {219,219,219,219,219,219,' ',219,' ',219,' ',' ',219,219,219,219,219,' ',219,' ',219,219,219,219,219,' ',219,219,219,219,219},
    {219,' ',' ',' ',' ',' ',' ',219,' ',219,' ',' ',219,' ',' ',' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',219},
    {219,' ',219,219,219,219,' ',219,' ',219,219,'*',219,219,219,219,219,' ',219,219,219,219,219,219,219,' ',219,219,219,219,219},
    {219,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',219,' ',' ',' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',219},
    {219,219,219,219,219,219,' ',219,219,219,219,' ',219,219,219,219,219,' ',219,219,219,219,219,219,219,' ',219,219,219,219,219},
    {219,'*',' ',' ',' ',' ',' ',219,' ',' ',' ',' ',219,' ',' ',' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',219,' ',' ',' ',219},
    {219,' ',219,219,219,219,' ',219,'*',219,219,' ',219,219,219,219,219,' ',219,219,219,219,219,219,219,' ',219,219,219,219,219},
    {219,' ',' ',' ',' ',' ',' ',219,' ',219,' ',' ',' ',' ','*',' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',' ',' ','E',' ',219},
    {219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219}
};

// Working maze that is modified during gameplay
unsigned char mazeLevel1[HEIGHT][WIDTH];
unsigned char (*maze)[WIDTH] = mazeLevel1;  // Pointer to current maze

// One enemy for Level 1
Enemy enemiesLevel1[1] = {{'X', true, 6, 3}};  // Symbol, active, X position, Y position
Enemy* enemies = enemiesLevel1;
int enemyCount = 1;

// Move console cursor to (x, y) position
void gotoxy(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Clear the screen using system call
void clearScreen() {
    system("cls");
}

// Show main menu
void displayMenu() {
    clearScreen();
    cout << "Namaste! Enjoy your game" << endl;
    cout << "Created by Aman Yadav" << endl;
    cout << "#--- Maze Game ---#" << endl;
    cout << "1. Play Level 1" << endl;
    cout << "Q. Exit Game" << endl;
    cout << "Enter your choice: ";
}

// Show player controls and level info
void drawInstructions() {
    gotoxy(0, HEIGHT + 2);
    cout << "Controls: W (Up), A (Left), S (Down), D (Right), Q (Exit)       ";
    gotoxy(0, HEIGHT + 3);
    cout << "Objective: Reach 'E' to complete the game, avoid 'X', collect '*' for score";
    gotoxy(0, HEIGHT + 4);
    cout << "Current Level: " << currentLevel << "                            ";
}

// Draw the maze and player/enemy positions
void drawMaze(int oldX = -1, int oldY = -1) {
    static bool firstDraw = true;

    if (firstDraw) {
        gotoxy(0, 0);
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                cout << maze[y][x];
            }
            cout << endl;
        }
        firstDraw = false;
    }

    // Clear previous player position
    if (oldX != -1 && oldY != -1) {
        gotoxy(oldX, oldY);
        cout << ' ';
    }

    // Draw player at new position
    gotoxy(posX, posY);
    cout << player;

    // Draw all enemies
    for (int i = 0; i < enemyCount; ++i) {
        if (enemies[i].active) {
            gotoxy(enemies[i].x, enemies[i].y);
            cout << enemies[i].symbol;
        }
    }

    // Display stats
    gotoxy(0, HEIGHT);
    cout << "Level: " << currentLevel << " | Moves: " << movesTaken << " | Score: " << score << "    ";
    drawInstructions();
}

// Copy original maze to working maze
void resetMaze() {
    memcpy(mazeLevel1, originalMazeLevel1, sizeof(originalMazeLevel1));
    maze = mazeLevel1;
}

// Setup level (reset maze, position, etc.)
void initializeLevel() {
    resetMaze();
    enemies = enemiesLevel1;
    enemyCount = 1;
    posX = 1; posY = 1;
    movesTaken = 0;
    levelCompleted = false;

    clearScreen();
    drawMaze();
}

// Show final message after completing level
void showCongratulations() {
    clearScreen();
    cout << "########################################" << endl;
    cout << "#        CONGRATULATIONS!              #" << endl;
    cout << "#   You completed Level " << currentLevel << "!             #" << endl;
    cout << "#   Final Score: " << score << "                     #" << endl;
    cout << "#   Moves Taken: " << movesTaken << "                    #" << endl;
    cout << "#   Press any key to return to menu    #" << endl;
    cout << "########################################" << endl;
    _getch();
    levelCompleted = true;  // Signal to return to menu
}

// Handle player movement and logic
void movePlayer() {
    if (levelCompleted) return;

    action = _getch();  // Read user input
    int oldX = posX, oldY = posY;
    int newX = posX, newY = posY;

    // Update position based on input
    switch (action) {
        case 'w': case 'W': newY--; break;
        case 's': case 'S': newY++; break;
        case 'a': case 'A': newX--; break;
        case 'd': case 'D': newX++; break;
        case 'q': case 'Q': levelCompleted = true; return;
        default: return;  // Ignore other keys
    }

    // Check for collision with wall
    if (maze[newY][newX] != 219) {
        movesTaken++;

        // Collect collectible
        if (maze[newY][newX] == '*') {
            score++;
            maze[newY][newX] = ' ';
        }

        // Move player
        posX = newX;
        posY = newY;

        // Check if player reached end
        if (maze[posY][posX] == 'E') {
            showCongratulations();
            return;
        }
    }

    // Check for enemy collision
    for (int i = 0; i < enemyCount; ++i) {
        if (enemies[i].active && posX == enemies[i].x && posY == enemies[i].y) {
            gotoxy(0, HEIGHT + 5);
            cout << "Game Over! Caught by " << enemies[i].symbol;
            gotoxy(0, HEIGHT + 6);
            cout << "Moves: " << movesTaken << " Score: " << score;
            gotoxy(0, HEIGHT + 7);
            cout << "Press any key to return to menu...";
            _getch();
            levelCompleted = true;
            return;
        }
    }

    drawMaze(oldX, oldY);  // Redraw maze with updated positions
}

int main() {
    // Hide cursor in console
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);

    // Game loop
    while (true) {
        displayMenu();
        char choice = _getch();

        if (choice == '1') {
            currentLevel = 1;
            initializeLevel();
        } else if (choice == 'q' || choice == 'Q') {
            clearScreen();
            cout << "Exiting Game... Thank you for playing!" << endl;
            break;
        }

        while (!levelCompleted) {
            movePlayer();
        }
    }

    return 0;
}
