#pragma once
#include <iostream>
#include "competitor.h"
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <sstream>
using namespace std;

//设计流程管理类
class compareManager
{
public:
	compareManager();

	~compareManager();

	void Show_Menu();

	void Design_Process(int choice);//程序流程人数、晋级人数获取以及算法的确定

	void createCompetitor();
	
	void import_Competitor();

	void Show_info();

	void Start_Competition();

	void Exit();

	void Competition_Draw();//抽签程序

	void Competition_Contest();//比赛进行程序

	void show_Score();

	int print_first_Num();

	int print_scond_Num();
	//初始化容器属性
	void initCompetition();

	//第一轮
	vector<int>v1;
	//晋级
	vector<int>v2;
	//胜出
	vector<int>vVictory;
	//编号对应选手
	map<int, Competitor>m_Competitor;
	//比赛轮数
	int m_Index;

private:
	int first_Num;
	int scond_Num;
	int judges_Num;
	bool Whether_To_Remove;
};