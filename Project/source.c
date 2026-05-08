#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h> 
#include <time.h>   

#include "buffer.h"

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

#define MAX_SNAKE_LENGTH 100

int map[MAP_WIDTH][MAP_HEIGHT] = {0};

void MAP()
{
    int i,j;

    for (i = 0; i < MAP_HEIGHT; i++)
    {
        for (j = 0; j < MAP_WIDTH; j++)
        {
            if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1)
            {
                map[i][j] = 1;
            }
            else
            {
                map[i][j] = 0;
            }

            if (map[i][j] == 1)
            {
                render(j * 2, i, "■");
            }
        }
    }
}

int main()
{
    CONSOLE_SCREEN_BUFFER_INFO console;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(handle, &console);

    srand((unsigned int)time(NULL));

    //int width = console.srWindow.Right - console.srWindow.Left - 2;
    //int height = console.srWindow.Bottom - console.srWindow.Top + 1;

    initialize();

    int snakeX[MAX_SNAKE_LENGTH];
    int snakeY[MAX_SNAKE_LENGTH];

    int snakeLength = 1;

    snakeX[0] = 10;
    snakeY[0] = 10;

    int x = 10;
    int y = 10;
    int dir = 0; // 0은 정지상태

    int score = 0;

    int appleX = (rand() % (MAP_WIDTH - 2) + 1) * 2;
    int appleY = rand() % (MAP_HEIGHT - 2) + 1;

    while (1)
    {
        clear();
        MAP();

        if (_kbhit())
        {
            int key = _getch();
            if (key == -32 || key == 0) key = _getch();

            if (dir == 0) dir = key;
            else {
                if (key == UP && dir != DOWN) dir = key;
                else if (key == DOWN && dir != UP) dir = key;
                else if (key == LEFT && dir != RIGHT) dir = key;
                else if (key == RIGHT && dir != LEFT) dir = key;
            }
        }

        if (dir != 0)
        {
            for (int i = snakeLength - 1; i > 0; i--)
            {
                snakeX[i] = snakeX[i - 1];
                snakeY[i] = snakeY[i - 1];
            }

            switch (dir)
            {
            case UP:    snakeY[0]--; break;
            case DOWN:  snakeY[0]++; break;
            case LEFT:  snakeX[0] -= 2; break;
            case RIGHT: snakeX[0] += 2; break;
            }
        }

        if (snakeX[0] == appleX && snakeY[0] == appleY)
        {
            score++;
            if (snakeLength < MAX_SNAKE_LENGTH) snakeLength++;
            appleX = (rand() % (MAP_WIDTH - 2) + 1) * 2;
            appleY = rand() % (MAP_HEIGHT - 2) + 1;
        }

        if (snakeX[0] <= 0 || snakeX[0] >= (MAP_WIDTH - 1) * 2 || snakeY[0] <= 0 || snakeY[0] >= MAP_HEIGHT - 1)
        {
            render(MAP_WIDTH, MAP_HEIGHT / 2, "G A M E  O V E R");
            flip();
            Sleep(2000);
            break;
        }

        render(appleX, appleY, "●");
        for (int i = 0; i < snakeLength; i++)
        {
            render(snakeX[i], snakeY[i], "■");
        }
        
        char scoreStr[20];
        sprintf_s(scoreStr, sizeof(scoreStr), "Score: %d", score);
        render(MAP_WIDTH * 2 + 2, MAP_HEIGHT - 1, scoreStr);

        flip();
        Sleep(200);
    }

    release();

    return 0;
}