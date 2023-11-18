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

//������̹�����
class compareManager
{
public:
	compareManager();

	~compareManager();

	void Show_Menu();

	void Design_Process(int choice);//������������������������ȡ�Լ��㷨��ȷ��

	void createCompetitor();
	
	void import_Competitor();

	void Show_info();

	void Start_Competition();

	void Exit();

	void Competition_Draw();//��ǩ����

	void Competition_Contest();//�������г���

	void show_Score();

	int print_first_Num();

	int print_scond_Num();
	//��ʼ����������
	void initCompetition();

	//��һ��
	vector<int>v1;
	//����
	vector<int>v2;
	//ʤ��
	vector<int>vVictory;
	//��Ŷ�Ӧѡ��
	map<int, Competitor>m_Competitor;
	//��������
	int m_Index;

private:
	int first_Num;
	int scond_Num;
	int judges_Num;
	bool Whether_To_Remove;
};