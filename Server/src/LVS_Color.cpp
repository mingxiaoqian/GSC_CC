#include "stdio.h"
#include "windows.h"

#include "LVS_Color.h"

void set_console_color(unsigned short color_index)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_index);
}