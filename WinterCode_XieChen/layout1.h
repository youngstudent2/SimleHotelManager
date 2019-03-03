#pragma once
#include<windows.h>
#include<conio.h>
#include<iostream>
#include"Draw.h"
#include"InputHandle.h"
using namespace std;
class layout1
{
public:
	int exec() {
		render();
		int choice = 0;
		while (1) {
			switch (InputHandle::getKeyInput())
			{
			case InputHandle::KEY_UP:
			case InputHandle::KEY_LEFT:
				choiceUp(choice);
				break;
			case InputHandle::KEY_DOWN:
			case InputHandle::KEY_RIGHT:
				choiceDown(choice);
				break;
			case InputHandle::KEY_ENTER:
				return chooseFuntion(choice);
				break;
			
			default:
				break;
			}
			
		}
	}
	

private:
	int chooseFuntion(int choice) {
		switch (choice)
		{
		case 0:
			if (adminLayout())return 0;
			else return -1;
			break;
		case 1:
			if (userLayout())return 1;
			break;
		case 2:
			exit(0);
			break;
		default:
			break;
		}
	}
	void choiceUp(int &choice) {
		choiceHide(choice);
		choice--;
		if (choice < 0)choice += 3;
		choiceHighlight(choice);
	}
	void choiceDown(int &choice) {
		choiceHide(choice);
		choice++;
		if (choice > 2)choice = 0;
		choiceHighlight(choice);
	}
	void choiceHighlight(int choice) {
		draw::gotoxy(15 + choice * 5, 23);
		cout << '#';
	}
	void choiceHide(int choice) {
		draw::gotoxy(15 + choice * 5, 23);
		cout << ' ';
	}
	boolean adminLayout() {
		system("cls");
		system("color 0B");
		draw::printRect(2, 5, 100, 35);//绘制外边框

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		draw::gotoxy(10, 20);
		cout << "请输入用户名:";
		draw::gotoxy(15, 20);
		cout << "请输入密码:";
		draw::gotoxy(30, 28);
		cout << "#回车登录#";
		draw::gotoxy(10, 35);
		string name, key;
		cin >> name;
		draw::gotoxy(15, 35);
		cin >> key;
		if (name == "liuguotao"&&key == "hhh")
			return true;
		return false;
	}
	boolean userLayout() {
		return true;
	}
	void render() {
		system("color 0B");
		draw::printRect(2, 5, 140, 35);//绘制外边框

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		draw::gotoxy(15, 23);
		cout << '#';
		draw::gotoxy(15, 25);
		cout << "管理员登录";
		draw::gotoxy(20, 25);
		cout << "普通用户登录";
		draw::gotoxy(25, 25);
		cout << "退出";
	}
};