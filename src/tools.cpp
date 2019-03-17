#include "tools.h"
#include<windows.h>
#include<iostream>
using namespace std;
void CursorPosition(int x,int y)
{
    COORD cor;

    cor.X = x*2;
    cor.Y  = y+2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cor);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
