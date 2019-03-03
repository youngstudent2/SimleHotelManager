#include<iostream>
#include"AdminLayout.h"
#include"ClientLayout.h"
#include"Info.h"
#include"layout1.h"

#pragma comment(lib,"ws2_32.lib")
using namespace std;
int main()
{
	system("mode 150,40");
	layout1 l;
	int exec_result;
	while (1) {
		exec_result = l.exec();
		if (exec_result == -1) {

		}
		else if (exec_result == 0) {
			AdminLayout admin;
			admin.exec();
			break;
		}
		else if (exec_result == 1) {
			ClientLayout client;
			client.exec();
			break;
		}
		system("cls");
	}

	return 0;
}