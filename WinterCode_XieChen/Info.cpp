#include"Info.h"
int Info::loadFile(string fileName) {
	fstream file(fileName, ios::in);
	if (!file.is_open())return 0;
	char tempInfo[200];
	while (file.getline(tempInfo,200)) {
		work(tempInfo);
	}
	file.close();
	return 1;
}

int Info::saveInfo(string fileName) {
	if (fileName.find('.') == string::npos)return 0;
	fstream file(fileName, ios::out);
	if (!file.is_open())return 0;
	for (int i = 0; i < hotels.size(); i++) {
		file << setfill('0') << setw(3) << (i + 1) << ','
			<< hotels.at(i).name << ','
			<< hotels.at(i).city << ','
			<< hotels.at(i).location << '|';
		for (auto &r : hotels.at(i).rooms) {
			file << r.id << ',' << r.price << ',' << r.kind << '|';
		}
		file << "\r\n";
	}
	file.close();
	return 1;
}

int Info::add(hotel h)
{
	hotels.push_back(h);
	return 1;
}

int Info::search(string hotelName)
{
	for (int i = 0; i < hotels.size(); i++) {
		if (hotels.at(i).name == hotelName) {
			return i;
		}
	}
	return -1;
}

int Info::insert(hotel h, int index)
{
	hotels.insert(hotels.begin() + index, h);
	return 0;
}

int Info::deleteHotel(int index)
{
	if (index<0 || index>hotels.size())return NULL;
	else hotels.erase(hotels.begin() + index);
	return 1;
}

void Info::changeRoomPrice(int hotelIndex, int roomIndex, int price)
{
	hotels[hotelIndex].rooms[roomIndex].price = price;
}

hotel Info::getHotel(int index)
{
	if (index<0 || index>hotels.size() - 1) {
		hotel h;
		return h;
	}		
	return hotels.at(index);
}

int Info::hotels_count()
{
	return hotels.size();
}

void Info::tcpAssist(string hotelInfo)
{
	work(hotelInfo);
}

void Info::clear()
{
	hotels.clear();
}

int Info::work(string tempInfo) {
	hotel h;
	int position = tempInfo.find(",") + 1;
	int next_position = tempInfo.find(",", position);
	h.name = tempInfo.substr(position, next_position - position);//获取名称
	position = next_position + 1;
	next_position = tempInfo.find(",", position);
	h.city = tempInfo.substr(position, next_position - position);//获取城市
	position = next_position + 1;
	next_position = tempInfo.find("|", position);
	h.location = tempInfo.substr(position, next_position - position);//获取地址

	position = next_position + 1;
	next_position = tempInfo.find("|", position);
	while (next_position != string::npos) {
		work_with_room(tempInfo.substr(position, next_position - position), h);
		position = next_position + 1;
		next_position = tempInfo.find("|", position);
	}

	hotels.push_back(h);
	return 1;
}

int Info::work_with_room(string roomInfo, hotel &h) {
	room r;
	int aPos = roomInfo.find(",") + 1;
	int bPos = roomInfo.find(",", aPos);
	r.id = atoi(roomInfo.substr(0U, aPos - 1).c_str());
	r.price = atoi(roomInfo.substr(aPos, bPos - aPos).c_str());
	r.kind = roomInfo.substr(bPos + 1);

	h.rooms.push_back(r);
	return 1;
}


