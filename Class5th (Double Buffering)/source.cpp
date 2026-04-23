#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

HANDLE screen[2];
int index = 0;
int size = sizeof(screen) / sizeof(screen[0]);

void initialize()
{
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    // for 축소
    for (int i = 0; i < 2; i++)
    {
        screen[i] = CreateConsoleScreenBuffer
        (
            GENERIC_READ | GENERIC_WRITE,
            0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL
        );
        SetConsoleCursorInfo(screen[i], &cursor);
    }

    // 화면 버퍼를 2개 생성합니다.
    //screen[0] = CreateConsoleScreenBuffer
    //(
    //    GENERIC_READ | GENERIC_WRITE,
    //    0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL
    //);
    //
    //screen[1] = CreateConsoleScreenBuffer
    //(
    //    GENERIC_READ | GENERIC_WRITE,
    //    0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL
    //);

    //cursor.bVisible = FALSE;

    //SetConsoleCursorInfo(screen[0], &cursor);
    //SetConsoleCursorInfo(screen[1], &cursor);
}

void flip()
{
    SetConsoleActiveScreenBuffer(screen[0]);
    //0       1
    index = !index;
#pragma region other

    //index = 1 - index;

    //if (index==0)
    //{
    //    index = 1;
    //}
    //else
    //{
    //    index = 0;
    //}
#pragma endregion

}

void clear()
{
    COORD position = { 0, 0 };

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
    for (int i = 0; i < size; i++)
    {
        CloseHandle(screen[i]);
    }
}

void render(int x, int y, const char* character)
{
    DWORD dword;
    COORD position = { x, y };

    SetConsoleCursorPosition(screen[index], position);
    WriteFile(screen[index], character, strlen(character), &dword, NULL);
}

int main()
{
    CONSOLE_SCREEN_BUFFER_INFO console;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(handle, &console);

    int width = console.srWindow.Right - console.srWindow.Left + 1;
    int height = console.srWindow.Bottom - console.srWindow.Top;

    initialize();

    int x = 0;
    int y = 0;

    char key = 0;


    while (1)
    {
        flip();

        clear();

        if (_kbhit())
        {
            key = _getch();

            if (key == -32 || key == 0)
            {
                key = _getch();
            }

            switch (key)
            {
            case UP: y--;
                if (y < 0) y = 0;
                break;
            case LEFT: x -= 2;
                if (x < 0) x = 0;
                break;
            case RIGHT:
                if (x < width)
                {
                    x += 2;
                }
                break;
            case DOWN:
                if (y < height)
                {
                    y++;
                }
                break;
            default: render(0, 0, "exception");
                break;
            }
        }
        render(x, y, "★");
    }

    release();

    return 0;
}