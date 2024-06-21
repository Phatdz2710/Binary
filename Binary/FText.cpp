#include "FText.h"

FColor::FColor() : fColor(0), bColor(0) {}

FColor::FColor(int fColor) : fColor(fColor), bColor(0) {}

FColor::FColor(int fColor, int bColor) : fColor(fColor), bColor(bColor) {}

std::ostream& operator<<(std::ostream& os, const FColor& color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color.fColor + color.bColor);
	return os;
}

FColor FColor::Reset(7, 0);