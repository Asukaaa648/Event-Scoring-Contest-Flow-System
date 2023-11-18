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
			cout << "是否有选手名单？（“1”表示“是”，“0”表示“否”）：";
			cin >> choice;
			cm.Design_Process(choice); //程序流程人数、晋级人数获取以及算法的确定
			if (choice == 0)  cm.createCompetitor(); //选手姓名、编号的生成
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