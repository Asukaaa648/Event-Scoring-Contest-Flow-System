#include <iostream>
#include "compareManager.h"
#include "competitor.h"
#include <string>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

int main()
{
	compareManager cm;
	int choice = 0;
	while (true)
	{
		cm.Show_Menu();
		cin >> choice;
		switch (choice)
		{
		case(1):
			int choice;
			cout << "�Ƿ���ѡ������������1����ʾ���ǡ�����0����ʾ���񡱣���";
			cin >> choice;
			cm.Design_Process(choice); //������������������������ȡ�Լ��㷨��ȷ��
			if (choice == 0)  cm.createCompetitor(); //ѡ����������ŵ�����
			cm.Start_Competition();
			cm.Exit();
			break;
			
		case(0):
			cm.Exit();
		default:
			system("cls");
			break;
		}
	}
	
	system("pause");
}