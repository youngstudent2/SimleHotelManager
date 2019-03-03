#include<iostream>
#include<cstdlib>
//#include<thread>
#include<ctime>
#include<cstring>
using namespace std;
void print(char (*ch)[300],int height)
{
	for(int i=0;i<height;i++){
		cout<<ch[i]<<'\n';
	}	
}
int main()
{
	system("mode 200,200");
	srand(time(NULL));
	char ch[50][300];
	memset(ch,0,sizeof(ch));
	for(int i=0;i<50;i++){
		for(int j=0;j<100;j++)
			ch[i][j]=30+rand()%60;
	}
	print(ch,30);
}