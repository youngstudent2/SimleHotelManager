#pragma once
#include<iostream>
#include<conio.h>
using namespace std;
class InputHandle 
{
public:
	static const int KEY_UP = 0;
	static const int KEY_DOWN = 1;
	static const int KEY_LEFT = 2;
	static const int KEY_RIGHT = 3;
	static const int KEY_ENTER = 4;
	static const int KEY_W = 5;
	static const int KEY_S = 6;
	static const int KEY_E = 7;
	static const int KEY_Q = 8;

	static int getKeyInput() {
		int ch = _getch();
		if (ch == 224) {
			ch = _getch();
			switch (ch)
			{
				case 72:return KEY_UP;
				case 80:return KEY_DOWN;
				case 75:return KEY_LEFT;
				case 77:return KEY_RIGHT;
			}
		}
		else {
			//Debug:
			//_getch();
			//release:

			switch (ch)
			{
				case 'w':return KEY_W;
				case 's':return KEY_S;
				case 'q':return KEY_Q;
				case 'e':return KEY_E;
				case '\r':return KEY_ENTER;
			}
		}
	}
};
