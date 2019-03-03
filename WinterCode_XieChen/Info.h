#pragma once
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;
struct room
{
	int id;
	int price;
	string kind;
};
struct hotel
{
	string name;
	string city;
	string location;
	vector<room> rooms;
};

class Info {
public:
	int loadFile(string fileName);
	int saveInfo(string fileName);
	int add(hotel h);
	int search(string hotelName);
	int insert(hotel h, int index);
	int deleteHotel(int index);
	void changeRoomPrice(int hotelIndex, int roomIndex, int price);
	hotel getHotel(int index);
	int hotels_count();
	void tcpAssist(string hotelInfo);
	void clear();
private:
	vector<hotel> hotels;
	int work(string tempInfo);
	int work_with_room(string roomInfo, hotel &h);

};