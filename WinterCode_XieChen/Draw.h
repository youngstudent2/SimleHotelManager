#pragma once
#include<windows.h>
#include<iostream>
class draw
{
public:
	static void gotoxy(int x, int y) {
		COORD pos;
		HANDLE hOutput;
		pos.X = y;
		pos.Y = x;
		hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hOutput, pos);
	}
	static void printRow(int x, int y, int width, char ch = '*') {
		gotoxy(x, y);
		for (int i = 0; i < width; i++) {
			std::cout << ch;
		}
	}
	static void printCol(int x, int y, int height, char ch = '*') {
		for (int i = 0; i < height; i++) {
			gotoxy(x + i, y);
			std::cout << ch;
		}
	}
	static 
		void printRect(int x, int y, int width, int height) {
		printRow(x, y, width);
		printRow(x + height - 1, y, width);
		printCol(x + 1, y, height - 2);
		printCol(x + 1, y + width - 1, height - 2);
	}
};