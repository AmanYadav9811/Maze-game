#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;

const int WIDTH = 31, HEIGHT = 15;
char player = 'P';
int posX = 1, posY = 1;
char action;
int movesTaken = 0;
int score = 0;
int currentLevel = 1;
bool levelCompleted = false;

struct Enemy {
    char symbol;
    bool active;
    int x;
    int y;
};

// Level 1 Maze
unsigned char mazeLevel1[HEIGHT][WIDTH] = {
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

// Level 2 Maze (same as Level 1)
unsigned char mazeLevel2[HEIGHT][WIDTH] = {
    {219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
    {219,' ',' ',' ',219,219,219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',219},
    {219,' ','*',219,219,' ',' ',219,'*',' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,219,219},
    {219,' ',' ',219,' ',' ',' ',219,219,' ',219,' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219},
    {219,' ','*',219,219,219,' ',219,' ',' ',219,' ',219,'*',219,219,219,' ',219,' ',219,219,219,219,219,' ',219,'*',219,219,219},
    {219,' ',' ',' ',' ',' ',' ',219,' ',219,219,' ',219,' ',' ',' ',' ',' ',219,' ',219,' ',' ',' ',' ',' ',219,' ',' ',' ',219},
    {219,219,'*',219,219,219,' ',219,' ',219,' ',' ',219,219,219,'*',219,' ',219,' ',219,219,219,219,219,' ',219,'*',219,219,219},
    {219,' ',' ',' ',' ',' ',' ',219,' ',219,' ',' ',219,' ',' ',' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',219},
    {219,' ','*',219,'*',219,' ',219,' ',219,219,'*',219,219,219,219,219,' ',219,219,219,219,219,219,219,' ',219,219,219,219,219},
    {219,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',219,' ',' ',' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',219},
    {219,219,219,219,219,219,' ',219,219,219,219,' ',219,219,'*',219,219,' ',219,219,219,219,219,219,219,' ',219,219,219,219,219},
    {219,'*',' ',' ',' ',' ',' ',219,' ',' ',' ',' ',219,' ',' ',' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',219,' ',' ',' ',219},
    {219,' ',219,219,219,219,' ',219,'*',219,219,' ',219,219,219,219,219,' ',219,219,219,219,219,219,219,' ',219,219,219,219,219},
    {219,' ',' ',' ',' ',' ',' ',219,' ',219,' ',' ',' ',' ','*',' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',' ',' ','E',' ',219},
    {219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219}
};

unsigned char (*maze)[WIDTH] = mazeLevel1;
Enemy enemiesLevel1[1] = {{'X', true, 6, 3}};
Enemy enemiesLevel2[1] = {{'X', true, 6, 3}}; // Same enemy position as Level 1
Enemy* enemies = enemiesLevel1;
int enemyCount = 1;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void displayMenu() {
    system("cls");
    cout << "Namaste enjoy your game" << endl;
    cout << "Created by Aman yadav" << endl;
    cout << "#---Maze-Game---#" << endl;
    cout << "1. Play Level 1" << endl;
    cout << "2. Play Level 2" << endl;  // Added Level 2 option
    cout << "Q. Exit Game" << endl;
    cout << "Enter your choice:" << endl;
}

void drawInstructions() {
    gotoxy(0, HEIGHT + 2);
    cout << "Controls: W (Up), A (Left), S (Down), D (Right), Q (Exit)" << endl;
    cout << "Objective: Reach 'E' to complete the game, avoid enemy (X), collect '*' for score" << endl;
    cout << "Current Level: " << currentLevel << endl;
}

void drawMaze(int oldX = -1, int oldY = -1) {
    static bool firstDraw = true;
    gotoxy(0, 0);

    if (firstDraw) {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                cout << maze[y][x];
            }
            cout << endl;
        }
        firstDraw = false;
    }

    if (oldX != -1 && oldY != -1) {
        gotoxy(oldX, oldY);
        cout << ' ';
    }

    gotoxy(posX, posY);
    cout << player;

    for (int i = 0; i < enemyCount; ++i) {
        if (enemies[i].active) {
            gotoxy(enemies[i].x, enemies[i].y);
            cout << enemies[i].symbol;
        }
    }

    gotoxy(0, HEIGHT);
    cout << "Level: " << currentLevel << " | Moves Taken: " << movesTaken << " | Score: " << score << "    ";
    drawInstructions();
}

void initializeLevel() {
    if (currentLevel == 1) {
        maze = mazeLevel1;
        enemies = enemiesLevel1;
        enemyCount = 1;
    } else if (currentLevel == 2) {
        maze = mazeLevel2;
        enemies = enemiesLevel2;
        enemyCount = 1;
    }

    posX = 1;
    posY = 1;
    movesTaken = 0;
    levelCompleted = false;

    // Redraw the entire maze
    system("cls");
    for (int y = 0; y < HEIGHT; y++) {
        gotoxy(0, y);
        for (int x = 0; x < WIDTH; x++) {
            cout << maze[y][x];
        }
    }

    drawMaze();
}

void showCongratulations() {
    system("cls");
    cout << "########################################" << endl;
    cout << "#                                      #" << endl;
    cout << "#        CONGRATULATIONS!              #" << endl;
    cout << "#   You completed Level " << currentLevel << "!             #" << endl;
    cout << "#                                      #" << endl;
    cout << "#   Final Score: " << score << "                    #" << endl;
    cout << "#   Moves Taken: " << movesTaken << "                    #" << endl;
    cout << "#                                      #" << endl;
    cout << "#   Press any key to return to menu    #" << endl;
    cout << "########################################" << endl;
    _getch();
}

void movePlayer() {
    if (levelCompleted) {
        return;
    }

    action = _getch();
    int oldX = posX, oldY = posY;
    int newX = posX, newY = posY;

    switch (action) {
        case 'w': case 'W': newY--; break;
        case 's': case 'S': newY++; break;
        case 'a': case 'A': newX--; break;
        case 'd': case 'D': newX++; break;
        case 'q': case 'Q': return;
        default: return;
    }

    if (maze[newY][newX] != 219) {
        movesTaken++;
        if (maze[newY][newX] == '*') {
            score++;
            maze[newY][newX] = ' ';
        }
        posX = newX;
        posY = newY;

        // Check if player reached exit
        if (maze[posY][posX] == 'E') {
            levelCompleted = true;
            showCongratulations();
            return;
        }
    }

    // Check for enemy collisions
    for (int i = 0; i < enemyCount; ++i) {
        if (enemies[i].active && posX == enemies[i].x && posY == enemies[i].y) {
            gotoxy(0, HEIGHT + 4);
            cout << "Game Over! Caught by enemy " << enemies[i].symbol << "    ";
            gotoxy(0, HEIGHT + 5);
            cout << "Moves Taken: " << movesTaken << " Score: " << score << "    ";
            gotoxy(0, HEIGHT + 6);
            cout << "Press any key to return to menu...";
            _getch();
            return;
        }
    }

    drawMaze(oldX, oldY);
}

int main() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);

    while (true) {
        displayMenu();
        char choice = _getch();
        bool exitGame = false;

        if (choice == '1') {
            currentLevel = 1;
            initializeLevel();
        } else if (choice == '2') {  // Added option for Level 2
            currentLevel = 2;
            initializeLevel();
        } else if (choice == 'q' || choice == 'Q') {
            system("cls");
            cout << "Thanks for playing" << endl;
            Sleep(1000);
            break;
        } else {
            continue;
        }

        while (!exitGame) {
            movePlayer();
            if (action == 'q' || action == 'Q' || levelCompleted) {
                exitGame = true;
            }
        }
    }
    return 0;
}
