#include <stdio.h>
#include <conio.h>
#include <windows.h>

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

    FillConsoleOutputCharacter(screen[index],' ', width * height, position, &dword);
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
    int x = 5;
    initialize();

    while (1)
    {
        flip();

        clear();

        render(x, 5, "★");
       
        Sleep(50);
        
    }

    release();

    return 0;
}