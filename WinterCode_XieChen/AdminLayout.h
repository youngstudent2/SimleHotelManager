#pragma once
#include"TcpServer.h"
#include"Info.h"
#include"Draw.h"
#include<iostream>
#include"InputHandle.h"
#include<thread>

using namespace std;
class AdminLayout
{
public:
	AdminLayout() {
		info.loadFile("hotel.txt");
		saved = true;
		tcpThread = thread(&AdminLayout::tcpServe, this);	
	}

	int exec() {
		render();
		tcpThread.detach();
		detailWidgetInit();
		int choice=0;
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
				case InputHandle::KEY_Q://��һҳ
					printPage(--currPage);
					printHotelRooms(info.getHotel(currHotel + currPage * 14));
					break;
				case InputHandle::KEY_E://��һҳ
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
	bool saved;

	void render() {
		system("cls");
		system("color 0B");
		draw::printRect(2, 5, 140, 35);

		drawWidget();
		printFunction();
		currPage = 0;
		printPage(currPage);
	}
	void drawWidget()
	{
		draw::gotoxy(3, 48);
		cout << "�Ƶ���Ϣ��";
		draw::printRow(4, 44, 18);
		draw::gotoxy(5, 9);
		cout << "���     �Ƶ�����     ����        ��ַ                ��������     ";

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
		draw::gotoxy(14, 85);
		cout << "���";
		draw::gotoxy(18, 85);
		cout << "�޸�";
		draw::gotoxy(22, 85);
		cout << "ɾ��";
		draw::gotoxy(26, 85);
		cout << "����";
		draw::gotoxy(30, 85);
		cout << "����";
		draw::gotoxy(34, 85);
		cout << "�˳�";
	}
	/*******************���ܼ�����ƶ�*********************/
	void choiceUp(int &choice) {
		choiceHide(choice);
		choice--;
		if (choice < 0)choice += 6;
		choiceHighlight(choice);
	}
	void choiceDown(int &choice) {
		choiceHide(choice);
		choice++;
		if (choice > 5)choice = 0;
		choiceHighlight(choice);
	}
	void choiceHighlight(int choice) {
		draw::gotoxy(14 + choice * 4, 83);
		cout << '#';
	}
	void choiceHide(int choice) {
		draw::gotoxy(14 + choice * 4, 83);
		cout << ' ';
	}
	/*****************************************/

	/*******************�Ƶ����ƶ�*********************/
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
		if (index < currPage * 14 || index>=(currPage + 1) * 14) {
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
	void printHotels(int begin,int count) {
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
	void printHotel(int x,int index) {
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
			case 0://���
				add();
				printPage(currPage);//ˢ��
				break;
			case 1://�޸�
				modify();
				break;
			case 2://ɾ��
				deleteHotel();
				break;
			case 3://����
				search();
				printHotelRooms(info.getHotel(currHotel + currPage * 14));
				break;
			case 4://����
				save();
				break;
			case 5://�˳�
				if (!saved) {
					if (MessageBox(0, " �Ƿ񱣴棿", "δ����", 1) == 1) {
						info.saveInfo("hotel.txt");
					}
				}
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
	/********************��Ҫ���ܵ�ʵ��*******************************/
	void add() {
		draw::gotoxy(15, 85);
		cout << "(�����ĩβ/��ǰλ��/�˳� (y/n/q) ";
		char ch;
		cin >> ch;
		clearRow(15, 85, 40);
		
		if (ch == 'q')return;
		
		hotel h;
		draw::gotoxy(15, 85);
		cout << "�Ƶ�����:"; cin >> h.name;
		clearRow(15, 85, 40);
		draw::gotoxy(15, 85);
		cout << "����:"; cin >> h.city;
		clearRow(15, 85, 40);
		draw::gotoxy(15, 85);
		cout << "��ַ:"; cin >> h.location;
		clearRow(15, 85, 40);
		draw::gotoxy(15, 85);
		cout << "������ �۸� ����(�س���������-1����)";
		draw::gotoxy(16, 85);
		room r;
		for (int i = 0; i < 4; i++) {
			cin >> r.id;
			if (r.id == -1)break;
			cin >> r.price >> r.kind;
			h.rooms.push_back(r);
			clearRow(16, 85, 40);
			draw::gotoxy(16, 85);
		}
		clearRow(15, 85, 40);
		clearRow(16, 85, 40);
		if (ch == 'y') {
			info.add(h);
		}
		else if (ch == 'n') {
			info.insert(h, currPage * 14 + currHotel);
		}
		saved = false;
	}

	void modify() {
		draw::gotoxy(19, 85);
		cout << "��Ҫ�޸ļ۸�ķ���:";
		int id, price, index=0;
		bool flag=false;
		cin >> id;
		for (auto &r : info.getHotel(currHotel + currPage * 14).rooms) {
			if (id == r.id) {
				draw::gotoxy(20, 85);
				cout << "����" << r.id << " �۸� " << r.price << "->";
				cin >> price;
				info.changeRoomPrice(currHotel + currPage * 14, index, price);
				flag = true;
				printHotelRooms(info.getHotel(currHotel + currPage * 14));
			}
			++index;
		}
		if (!flag) {
			draw::gotoxy(19, 85);
			cout << setfill(' ') << setw(30) << "�Ҳ����÷���";
			Sleep(3000);
		}
		else {
			saved = false;
		}
		clearRow(19, 85, 45);
		clearRow(20, 85, 45);
		
	}

	void search() {
		draw::gotoxy(27, 85);
		cout << "���������Ż�Ƶ�����:";
		draw::gotoxy(28, 85);
		string tmp;
		cin >> tmp;
		int index;
		if (is_num(tmp)) {
			index = search_by_index(atoi(tmp.c_str()));
			
			if (index == -1) {
				clearRow(27, 85, 45);
				draw::gotoxy(27, 85);
				cout << "��ų�����Χ";
				Sleep(3000);
			}

		}
		else {
			index = search_by_name(tmp);

			if (index == -1) {
				clearRow(27, 85, 45);
				draw::gotoxy(27, 85);
				cout << "�Ҳ����þƵ�";
				Sleep(1500);
			}
		}
		if (index >= 0)hotelJump(index);
		clearRow(27, 85, 45);
		clearRow(28, 85, 45);
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

	void save() {
		draw::gotoxy(31, 85);
		cout << "�����뱣���ַ���ļ���(ֱ�ӻس�ʹ��Ĭ��·��)";
		draw::gotoxy(32, 85);
		char ch;
		ch = _getche();
		if (ch == '\r') {//Ĭ�ϵ�ַ
			_getche();
			info.saveInfo("hotel.txt");
			saved = true;
		}
		else{
			_getche();		
			string path;
			cin >> path;
			if (!info.saveInfo(ch + path)) {
				clearRow(31, 85, 45);
				draw::gotoxy(31, 85);
				cout << "����·������,eg: e://hotelInfo//hotel.txt";
				Sleep(3000);
			}
		}
		clearRow(31, 85, 45);
		clearRow(32, 85, 45);
	}

	void deleteHotel() {
		int sure;
		string cont = "����ɾ��:" + info.getHotel(currHotel + currPage * 14).name;
		sure = MessageBox(GetForegroundWindow(), cont.c_str(), "ȷ��ɾ���þƵ���", 1);
		if (sure == 1) {
			if (info.deleteHotel(currHotel + currPage * 14)) {
				printPage(currPage);
				saved = false;
			}
			else {
				MessageBox(GetForegroundWindow(), " û�иþƵ�", "", 1);
			}
		}
	}
	/******************************************************************/

	/************************С����չ����************************************/
	void detailWidgetInit() {
		draw::printRect(4, 85, 55, 10);
		draw::gotoxy(5, 100);
		cout << "������Ϣ";
		for (int i = 0; i < 4; i++) {
			draw::gotoxy(6 + i * 2, 86);
			cout << std::left << setfill(' ') << setw(15) << "����:"
				<< setw(15) << "�۸�:"
				<< setw(20) << "����:";
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

	/***********************TCP�������*********************************/
	TcpServer tcpServer;
	thread tcpThread;
	void tcpServe() {			
		while (1) {
			tcpServer.init();
			tcpServer.acceptSocket();
			fstream file("hotel.txt", ios::in);
			char tempInfo[200];
			while (file.getline(tempInfo, 200)) {
				tcpServer.sendHotelInfo(tempInfo);
			}
			tcpServer.sendHotelInfo("EOF");
			file.close();
			tcpServer.close();
		}
		
	}
	/************************************************************/
};
