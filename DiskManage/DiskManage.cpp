// TrackManage.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
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
typedef vector<Process> vP;
vP vPage;
vP vManage;
default_random_engine e(time(0));
enum direct{DOWN=0,UP = 1};//DOWN为磁道减小方向，UP为磁道增大方向
int nCount = 0;//辅助生成ID

int curDirect;
int curTrack;
void Init();
void print();
void manage();
void request();
void updateData(int nTrack);
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
			manage();
		}
		else
		{
			request();
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
	for (auto v : vPage)
		vManage.push_back(v);
	curDirect = UP;
	curTrack = ui(e);
	cout << "curDirect: " << (curDirect == UP ? "UP" : "DOWN") << "\n"
		<< "curTrack: " << curTrack << "\n";
	print();

}
void print() 
{
	cout << "curPage: " << endl;
	cout << "\n\t" << "ID" << "\t" << "Track" << endl;
	for (auto process : vPage)
	{
		cout << "\t" << process.m_ID << "\t" << process.m_nTrack<< endl;
	}
}
void manage()
{
	cout << "start Manage............................." << endl<<endl;
	if (vManage.empty())
	{
		cout << "No process is waitting" << endl;
		return;
	}
	stable_sort(vManage.begin(), vManage.end(), [](const Process &a,const Process &b)
	{return a.m_nTrack < b.m_nTrack; });
	if (curDirect==UP)
	{
		vP::iterator viUp= find_if(vManage.begin(), vManage.end(), []( Process &a)
								{return a.m_nTrack > curTrack; });
		if (viUp != vManage.end())
		{
			updateData((*viUp).m_nTrack);
		}
		else
		{
			vP::reverse_iterator viDown = find_if(vManage.rbegin(), vManage.rend(), []( Process &a)
			{return a.m_nTrack <= curTrack; });
			if (viDown != vManage.rend())
			{
				
				updateData((*viDown).m_nTrack);
			}
			else
			{
				cerr << "unknown error\n"<<endl;
			}
		}

	}
	else
	{
		vP::reverse_iterator viDown = find_if(vManage.rbegin(), vManage.rend(), []( Process &a)
		{return a.m_nTrack <= curTrack; });
		if (viDown != vManage.rend())
		{
			updateData((*viDown).m_nTrack);
		}
		else
		{
			vP::iterator viUp = find_if(vManage.begin(), vManage.end(), []( Process &a)
			{return a.m_nTrack > curTrack; });
			if (viUp != vManage.end())
			{
				updateData((*viUp).m_nTrack);
			}
			else
			{
				cerr << "unknown error\n";
			}
		}
	}
	cout <<"end manage............................."<< endl << endl << endl;
}
void request()
{
	cout << "start request............................." << endl<<endl;
	cout << "Please iput track:\t";
	int nTrack;
	cin >> nTrack;
	vPage.push_back(Process(nCount++,nTrack));
	vManage.push_back(vPage.back());
	stable_sort(vManage.begin(), vManage.end(), [](const Process &a, const Process &b)
	{return a.m_nTrack < b.m_nTrack; });
	print();

	cout <<"end request............................."<< endl<<endl<<endl;
}
void updateData(int n_Track)
{
	vP::iterator pdel = find_if(vPage.begin(), vPage.end(), [n_Track]( Process &a)
	{return a.m_nTrack == n_Track; });
	vP::iterator mdel = find_if(vManage.begin(), vManage.end(), [n_Track](Process &a)
	{return a.m_nTrack == n_Track; });
	if (pdel != vPage.end()&&mdel!=vManage.end())
	{
		cout << "chosed process:\t" << (*pdel).m_ID << "\t" << (*pdel).m_nTrack << endl;
		vPage.erase(pdel);
		vManage.erase(mdel);
	}
	else
	{
		cout << "error!" << endl;
	}
	
}