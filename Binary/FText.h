#pragma once
#include <iostream>
#include <Windows.h>

#define F_BLACK 0
#define F_BLUE 1
#define F_GREEN 2
#define F_CYAN 3
#define F_RED 4
#define F_PURPLE 5
#define F_YELLOW 6
#define F_WHITE 7
#define F_GRAY 8
#define F_LIGHT_BLUE 9
#define F_LIGHT_GREEN 10
#define F_LIGHT_CYAN 11
#define F_LIGHT_RED 12
#define F_LIGHT_PURPLE 13
#define F_LIGHT_YELLOW 14
#define F_BRIGHT_WHITE 15

#define B_BLACK 0
#define B_BLUE 16
#define B_GREEN 32
#define B_CYAN 48
#define B_RED 64
#define B_PURPLE 80
#define B_YELLOW 96
#define B_WHITE 112
#define B_GRAY 128
#define B_LIGHT_BLUE 144
#define B_LIGHT_GREEN 160
#define B_LIGHT_CYAN 176
#define B_LIGHT_RED 192
#define B_LIGHT_PURPLE 208
#define B_LIGHT_YELLOW 224
#define B_BRIGHT_WHITE 240

class FColor
{
private:
	int fColor;
	int bColor;
public:
	FColor();
	FColor(int fColor);
	FColor(int fColor, int bColor);

	friend std::ostream& operator<<(std::ostream& os, const FColor& color);

	static FColor Reset;
} typedef fc;
