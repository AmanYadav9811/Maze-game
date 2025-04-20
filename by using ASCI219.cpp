#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;


const int WIDTH = 31, HEIGHT = 15;
char player = 'P';
int posX = 1, posY = 1;
char action;
int countScore = 0;
int currentLevel = 0;


struct Enemy {
    char symbol;
    bool active;
    int x;
    int y;
};


unsigned char mazeLevel1[HEIGHT][WIDTH] = {
{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
{219,' ',' ',' ',219,219,219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',' ',' ',' ','E',219},
{219,219,' ',219,219,' ',' ',' ',219,' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,219,219},
{219,' ',' ',219,' ',' ',' ',219,219,' ',219,' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219},
{219,' ',219,219,219,219,' ',219,' ',' ',219,' ',219,219,219,219,219,' ',219,' ',219,219,219,219,219,' ',219,219,219,219,219},
{219,' ',' ',' ',' ',' ',' ',219,' ',219,219,' ',219,' ',' ',' ',' ',' ',219,' ',219,' ',' ',' ',' ',' ',219,' ',' ',' ',219},
{219,219,219,219,219,219,' ',219,' ',219,' ',' ',219,219,219,219,219,' ',219,' ',219,219,219,219,219,' ',219,219,219,219,219},
{219,' ',' ',' ',' ',' ',' ',219,' ',219,' ',' ',219,' ',' ',' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',219},
{219,' ',219,219,219,219,' ',219,' ',219,219,' ',219,219,219,219,219,' ',219,219,219,219,219,219,219,' ',219,219,219,219,219},
{219,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',219,' ',' ',' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',219},
{219,219,219,219,219,219,' ',219,219,219,219,' ',219,219,219,219,219,' ',219,219,219,219,219,219,219,' ',219,219,219,219,219},
{219,' ',' ',' ',' ',' ',' ',219,' ',' ',' ',' ',219,' ',' ',' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',219,' ',' ',' ',219},
{219,' ',219,219,219,219,' ',219,' ',219,219,' ',219,219,219,219,219,' ',219,219,219,219,219,219,219,' ',219,219,219,219,219},
{219,' ',' ',' ',' ',' ',' ',219,' ',219,' ',' ',' ',' ',' ',' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',219,' ',' ',' ',219},
{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219}
};

unsigned char mazeLevel2[HEIGHT][WIDTH] = {
{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219},
{219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','E',219},
{219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,219,219,219,219,219,219,219,219},
{219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',' ',' ',219},
{219,' ',219,' ',219,219,219,' ',219,219,219,' ',219,' ',219,219,219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219},
{219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,219,' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',219},
{219,219,' ',219,219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219},
{219,' ',' ',219,' ',' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',' ',' ',219,' ',219,' ',219},
{219,' ',219,219,219,219,219,' ',219,219,219,' ',219,' ',219,219,219,219,219,' ',219,219,219,' ',' ',219,219,' ',219,219,219},
{219,' ',' ',' ',' ',' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',' ',' ',219},
{219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,219,219,219,219},
{219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',219,' ',' ',' ',' ',' ',219},
{219,' ',219,' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,219,' ',219,219,' ',' ',' ',' ',219,' ',219,219,219},
{219,' ',' ',' ',219,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',219,' ',' ',' ',' ',' ',' ',219,' ',' ',' ',' ',219,' ',219},
{219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219}
};


unsigned char (*maze)[WIDTH] = mazeLevel1;


Enemy enemiesLevel1[3] = {
    {'X', true, 6, 3},
    {'Y', true, 1, 8},
    {'Z', true, 27, 6}
};

Enemy enemiesLevel2[4] = {
    {'X', true, 8, 4},
    {'Y', true, 2, 10},
    {'Z', true, 25, 8},
    {'W', true, 15, 5}
};

Enemy* enemies = enemiesLevel1;
int enemyCount = 3;


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void displayMenu() {
    system("cls");
    cout << "#*****Maze Game******#" << endl;
    cout << "Welcome!" << endl;
    cout << "1. Play Level 1" << endl;
    cout << "2. Play Level 2" << endl;
    cout << "E. Exit Game" << endl;
    cout << "Enter your choice: ";
}

void drawInstructions() {
    gotoxy(0, HEIGHT + 2);
    cout << "Controls: W (Up), A (Left), S (Down), D (Right), E (Exit)" << endl;
    cout << "Objective: Reach 'E' to win, avoid enemies (X, Y, Z";
    if (currentLevel == 2) cout << ", W";
    cout << ")" << endl;
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
    cout << "Level: " << currentLevel << " | Score: " << countScore << "    ";


    drawInstructions();
}

void initializeLevel(int level) {
    currentLevel = level;
    posX = 1;
    posY = 1;
    countScore =0 ;

    if (level == 1) {
        maze = mazeLevel1;
        enemies = enemiesLevel1;
        enemyCount = 3;
    } else {
        maze = mazeLevel2;
        enemies = enemiesLevel2;
        enemyCount = 4;
    }


    for (int y = 0; y < HEIGHT; y++) {
        gotoxy(0, y);
        for (int x = 0; x < WIDTH; x++) {
            cout << maze[y][x];
        }
    }


    drawMaze();
}

void movePlayer() {
    action = _getch();

    int oldX = posX, oldY = posY;
    int newX = posX, newY = posY;
    switch (action) {
        case 'w': case 'W': newY--; break;
        case 's': case 'S': newY++; break;
        case 'a': case 'A': newX--; break;
        case 'd': case 'D': newX++; break;
        case 'e': case 'E': return;
        default: return;
    }

    if (maze[newY][newX] != 219) {
        posX = newX;
        posY = newY;
        countScore ++;


        if (maze[posY][posX] == 'E') {
            gotoxy(0, HEIGHT + 4);
            cout << "Congratulations Level " << currentLevel << " Complete Score: " << countScore << "    ";
            gotoxy(0, HEIGHT + 5);
            cout << "Press any key to return to menu...";
            _getch();
            return;
        }
    }


    for (int i = 0; i < enemyCount; ++i) {
        if (enemies[i].active && posX == enemies[i].x && posY == enemies[i].y) {
            gotoxy(0, HEIGHT + 4);
            cout << "Game Over! Caught by enemy " << enemies[i].symbol << "    ";
            gotoxy(0, HEIGHT + 5);
            cout << "Final Score: " << countScore << "    ";
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
            initializeLevel(1);
        } else if (choice == '2') {
            initializeLevel(2);
        } else if (choice == 'e' || choice == 'E') {
            system("cls");
            cout << "Thanks for playing" << endl;
            Sleep(1000);
            break;
        } else {
            continue;
        }

        while (!exitGame) {
            movePlayer();
            if (action == 'e' || action == 'E' || maze[posY][posX] == 'E' ||
                (posX == enemies[0].x && posY == enemies[0].y) ||
                (posX == enemies[1].x && posY == enemies[1].y) ||
                (posX == enemies[2].x && posY == enemies[2].y) ||
                (currentLevel == 2 && posX == enemies[3].x && posY == enemies[3].y)) {
                exitGame = true;
            }
        }
    }
    return 0;
}
