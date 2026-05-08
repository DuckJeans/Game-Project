#pragma once
#include <Windows.h>
#include <conio.h>

#define ScreenSize 2

int index = 0;

HANDLE screen[ScreenSize];

void initialize()
{
    CONSOLE_CURSOR_INFO cursor;

    // 화면 버퍼를 2개 생성합니다.

    cursor.bVisible = FALSE;

    for (int i = 0; i < ScreenSize; i++)
    {
        screen[i] = CreateConsoleScreenBuffer
        (
            GENERIC_READ | GENERIC_WRITE,
            0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL
        );

        SetConsoleCursorInfo(screen[i], &cursor);
    }
}

void flip()
{
    SetConsoleActiveScreenBuffer(screen[index]);

    index = !index;
}

void clear()
{
    COORD position = { 0,0 };

    DWORD dword;

    CONSOLE_SCREEN_BUFFER_INFO buffer;

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(console, &buffer);

    int width = buffer.srWindow.Right - buffer.srWindow.Left + 1;
    int height = buffer.srWindow.Bottom - buffer.srWindow.Top + 1;

    FillConsoleOutputCharacter(screen[index], ' ', width * height, position, &dword);
}

void release()
{
    for (int i = 0; i < ScreenSize; i++)
    {
        CloseHandle(screen[i]);
    }
}

void render(int x, int y, const char* character)
{
    DWORD dword;
    COORD position = { x,y };

    SetConsoleCursorPosition(screen[index], position);
    WriteFile(screen[index], character, strlen(character), &dword, NULL);
}