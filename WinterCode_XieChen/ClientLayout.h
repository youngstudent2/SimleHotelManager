#pragma once
#include"TcpClient.h"
#include<iostream>
#include<string>
#include<thread>
#include"Info.h"
using namespace std;


class ClientLayout
{
public:
	ClientLayout() {
		connected = 0;
	}
	int exec() {		
		get_IP();
		render();
		tcpThread = thread(&ClientLayout::tcpRequest, this);
		tcpThread.join();
		//////////输出来自server方的问候
		draw::gotoxy(39, 5);
		cout << tcpClient.getGreetWord();
		//////////////////////////////
		currPage = 0;
		printPage(currPage);
		detailWidgetInit();
		int choice = 0;
		currHotel = 0;
		printHotelRooms(info.getHotel(currHotel + currPage * 14));
		hotelHighlight(currHotel);
		choiceHighlight(choice);
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
				chooseFunction(choice);
				break;
			case InputHandle::KEY_Q://上一页
				printPage(--currPage);
				printHotelRooms(info.getHotel(currHotel + currPage * 14));
				break;
			case InputHandle::KEY_E://下一页
				printPage(++currPage);
				printHotelRooms(info.getHotel(currHotel + currPage * 14));
				break;
			case InputHandle::KEY_W:
				hotelUp(currHotel);
				printHotelRooms(info.getHotel(currHotel + currPage * 14));
				break;
			case InputHandle::KEY_S:
				hotelDown(currHotel);
				printHotelRooms(info.getHotel(currHotel + currPage * 14));
				break;
			default:
				break;
			}
		}
		return 1;
	}
private:
	Info info;
	int page, currPage;
	int currHotel;


	void render() {
		system("cls");
		system("color 0B");
		draw::printRect(2, 5, 140, 35);

		drawWidget();
		printFunction();
		
	}
	void drawWidget()
	{
		draw::gotoxy(3, 48);
		cout << "酒店信息表";
		draw::printRow(4, 44, 18);
		draw::gotoxy(5, 9);
		cout << "序号     酒店名称     城市        地址                房间类型     ";

		for (int i = 0; i < 15; i++) {
			draw::printRow(6 + i * 2, 6, 75, '-');
		}

		draw::printCol(5, 6, 30, '|');
		draw::printCol(5, 15, 29, '|');
		draw::printCol(5, 28, 29, '|');
		draw::printCol(5, 37, 29, '|');
		draw::printCol(5, 52, 29, '|');
		draw::printCol(5, 81, 30, '|');
	}
	void printFunction() {
		draw::gotoxy(22, 85);
		cout << "查找";
		draw::gotoxy(26, 85);
		cout << "刷新";
		draw::gotoxy(30, 85);
		cout << "退出";
	}
	/*******************功能键光标移动*********************/
	void choiceUp(int &choice) {
		choiceHide(choice);
		choice--;
		if (choice < 0)choice = 2;
		choiceHighlight(choice);
	}
	void choiceDown(int &choice) {
		choiceHide(choice);
		choice++;
		if (choice > 2)choice = 0;
		choiceHighlight(choice);
	}
	void choiceHighlight(int choice) {
		draw::gotoxy(22 + choice * 4, 83);
		cout << '#';
	}
	void choiceHide(int choice) {
		draw::gotoxy(22 + choice * 4, 83);
		cout << ' ';
	}
	/*****************************************/

	/*******************酒店光标移动*********************/
	void hotelUp(int &choice) {
		hotelHide(choice);
		choice--;
		if (choice < 0)choice += 14;
		hotelHighlight(choice);
	}
	void hotelDown(int &choice) {
		hotelHide(choice);
		choice++;
		if (choice > 13)choice = 0;
		hotelHighlight(choice);
	}
	void hotelHighlight(int choice) {
		draw::gotoxy(7 + choice * 2, 2);
		cout << '@';
	}
	void hotelHide(int choice) {
		draw::gotoxy(7 + choice * 2, 2);
		cout << ' ';
	}
	void hotelJump(int index) {
		if (index < currPage * 14 || index>(currPage + 1) * 14) {
			currPage = index / 14;
			printPage(currPage);
		}
		hotelHide(currHotel);
		currHotel = index % 14;
		hotelHighlight(currHotel);
	}
	/*****************************************/
	void printPage(int &currPage) {
		this->page = (info.hotels_count() - 1) / 14;
		if (currPage < 0)currPage = page;
		if (currPage > this->page)currPage = 0;

		//eraseAll();
		printHotels(14 * currPage, 14);
	}
	void printHotels(int begin, int count) {
		//vector<thread> printThreads;
		for (int i = 0; i < count; i++) {
			if (i + begin < info.hotels_count()) {
				//printThreads.push_back(thread(&AdminLayout::printHotel, this, 7 + i * 2, i + begin));				
				//printThreads.back().join();
				printHotel(7 + i * 2, i + begin);
			}
			else {
				erase(7 + i * 2);
			}
		}
	}
	void printHotel(int x, int index) {
		hotel h = info.getHotel(index);
		draw::gotoxy(x, 7);
		cout << std::right << setfill('0') << setw(3) << index + 1;
		draw::gotoxy(x, 16);
		cout << setfill(' ') << std::left << setw(12) << h.name;
		draw::gotoxy(x, 29);
		cout << std::left << setw(8) << h.city;
		draw::gotoxy(x, 38);
		cout << std::left << setw(14) << h.location;
		draw::gotoxy(x, 53);
		string allKind;
		for (auto r : h.rooms) {
			allKind += r.kind + " ";
		}
		cout << setw(28) << allKind;
	}
	static void erase(int x) {
		draw::gotoxy(x, 7);
		cout << setfill(' ') << setw(3) << ' ';
		draw::gotoxy(x, 16);
		cout << setw(12) << ' ';
		draw::gotoxy(x, 29);
		cout << setw(8) << ' ';
		draw::gotoxy(x, 38);
		cout << setw(14) << ' ';
		draw::gotoxy(x, 53);
		cout << setw(28) << ' ';
	}
	/*
	void eraseAll() {
		thread eraseThread[15];
		for (int i = 0; i < 14; i++) {
			eraseThread[i].~thread();
			eraseThread[i] = thread(AdminLayout::erase,7 + i * 2);
		}
		for (int i = 0; i < 14; i++) {
			eraseThread[i].join();
		}
	}
	*/
	
	void chooseFunction(int choice) {
		switch (choice)
		{

		case 0://查找
			search();
			printHotelRooms(info.getHotel(currHotel + currPage * 14));
			break;
		case 1://刷新
			refresh();
			break;
		case 2://退出
			exit(0);
			break;
		default:
			break;
		}
	}
	void clearRow(int x, int y, int width) {
		draw::gotoxy(x, y);
		cout << setfill(' ') << setw(width) << ' ';
	}
	/********************必要功能的实现*******************************/
	
	void search() {
		draw::gotoxy(23, 85);
		cout << "请输入的序号或酒店名称:";
		draw::gotoxy(24, 85);
		string tmp;
		cin >> tmp;
		int index;
		if (is_num(tmp)) {
			index = search_by_index(atoi(tmp.c_str()));

			if (index == -1) {
				clearRow(23, 85, 45);
				draw::gotoxy(23, 85);
				cout << "序号超出范围";
				Sleep(3000);
			}

		}
		else {
			index = search_by_name(tmp);

			if (index == -1) {
				clearRow(23, 85, 45);
				draw::gotoxy(23, 85);
				cout << "找不到该酒店";
				Sleep(1500);
			}
		}
		if (index > 0)hotelJump(index);
		clearRow(23, 85, 45);
		clearRow(24, 85, 45);
	}
	bool is_num(string s) {
		for (char ch : s) {
			if (ch<'0' || ch>'9')return false;
		}
		return true;
	}
	int search_by_index(int index) {
		if (index > info.hotels_count())return -1;
		return index - 1;
	}
	int search_by_name(string name) {
		return info.search(name);
	}

	void refresh() {
		info.clear();
		tcpThread = thread(&ClientLayout::tcpRequest, this);
		tcpThread.join();
		if (connected) {
			this->currPage = 0;
			printPage(this->currPage);
			printHotelRooms(info.getHotel(currHotel + currPage * 14));
		}
	}

	/******************************************************************/

	/************************小窗拓展功能************************************/
	void detailWidgetInit() {
		draw::printRect(4, 85, 55, 10);
		draw::gotoxy(5, 100);
		cout << "房间信息";
		for (int i = 0; i < 4; i++) {
			draw::gotoxy(6 + i * 2, 86);
			cout << std::left << setfill(' ') << setw(15) << "房号:"
				<< setw(15) << "价格:"
				<< setw(20) << "房型:";
		}
	}
	void printHotelRooms(hotel h) {
		int x = 4;
		for (auto &r : h.rooms) {
			x += 2;
			draw::gotoxy(x, 91);
			cout << setfill(' ') << setw(10) << r.id;
			draw::gotoxy(x, 106);
			cout << setw(10) << r.price;
			draw::gotoxy(x, 121);
			cout << setw(18) << r.kind;
		}
		while (x < 12) {
			x += 2;
			draw::gotoxy(x, 91);
			cout << setfill(' ') << setw(10) << ' ';
			draw::gotoxy(x, 106);
			cout << setw(10) << ' ';
			draw::gotoxy(x, 121);
			cout << setw(18) << ' ';
		}
	}
	/***************************************************************/
	string ip;
	TcpClient tcpClient;
	thread tcpThread;
	string greetWord;
	volatile int connected;
	void get_IP() {
		system("cls");
		cout << "please input the server ip:";
		cin >> ip;
	}
	void tcpRequest() {
		string temp;
		while (!tcpClient.init(ip)) {
			connected = 0;
			Sleep(200);
		}
		connected = 1;

		greetWord = tcpClient.getGreetWord();

		temp = tcpClient.recvMessage();
		while (temp != "EOF") {			
			if (temp != "error") {
				info.tcpAssist(temp);
			}	
			temp = tcpClient.recvMessage();
		}
		tcpClient.close();	
		
	}
};