#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

#define ScreenSize 2

#define MAP_WIDTH 30
#define MAP_HEIGHT 30

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

void MAP()
{
    int i;
    int j;

    for (i = 0; i < MAP_WIDTH; i++)
    {

    }
}

int main()
{
    CONSOLE_SCREEN_BUFFER_INFO console;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(handle, &console);

    int width = console.srWindow.Right - console.srWindow.Left - 2;
    int height = console.srWindow.Bottom - console.srWindow.Top + 1;

    initialize();

    int x = 2;
    int y = 2;

    char key = 0;

    while (1)
    {
        flip();

        clear();

        key = _getch();

        if (key == -32 || key == 0)
        {
            key = _getch();
        }

        switch (key)
        {
        case UP:
            if (y > 0)
            {
                y--;
            }
            break;
        case LEFT:
            if (x > 0)
            {
                x -= 2;
            }
            break;
        case RIGHT:
            if (width > x)
            {
                x += 2;
            }
            break;
        case DOWN:
            if (height > y)
            {
                y++;
            }
            break;
        default:
            render(0, 0, "exception");
            break;
        }

        render(x, y, "■");
    }

    release();

    return 0;
}