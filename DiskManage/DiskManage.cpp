// TrackManage.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;
struct Process
{
	int m_ID;
	int m_nTrack;
	Process(int ID,int track):m_ID(ID),m_nTrack(track){}
};
vector<Process> vPage;
default_random_engine e;
enum direct{UP=0,Down=1};
int nCount = 0;//辅助生成ID

int curDirect;
int curTrack;
void Init();
void print();
int main()
{
	Init();
	uniform_int_distribution<int> ran(0, 10);
	double chose;
	char cFlag='y';
	while (cFlag=='y')
	{
		chose=ran(e) / 10.0;
		if (chose > 0.5)
		{

		}
		else
		{

		}
		cout << "continue?(y/n)\t";
		cin >> cFlag;
	}
	
	system("pause");
    return 0;
}
void Init()
{
	uniform_int_distribution<int> ui(0, 1000);
	for(int i=0;i<4;i++)//初始化表
		vPage.push_back(Process(nCount++, ui(e)));
	curDirect = UP;
	curTrack = ui(e);
	cout << "curDirect: " << (curDirect == UP ? "UP" : "DOWN") << "\n"
		<< "curTrack: " << curTrack << "\n";
	cout << "curPage: " << endl;
	print();

}
void print() 
{
	cout << "\n\t" << "ID" << "\t" << "Track" << endl;
	for (auto process : vPage)
	{
		cout << "\t" << process.m_ID << "\t" << process.m_nTrack<< endl;
	}
}