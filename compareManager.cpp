#include <iostream>
#include "compareManager.h"
#include "competitor.h"
#include <fstream>
#include <string>
#include <deque>
using namespace std;

compareManager::compareManager()
{
	//初始化容器和属性
	this->initCompetition();
}

compareManager::~compareManager()
{

}

void compareManager::Show_Menu()
{
	cout << "欢迎使用活动比赛流程管理系统！" << endl;
	cout << "输入“1”开始演讲比赛,输入“0”退出程序：";
}

//程序流程人数、晋级人数获取以及算法的确定
void compareManager::Design_Process(int choice)
{
	while (true)
	{
		if (choice != 1)
		{
			cout << "请输入参赛选手人数：";
			cin >> this->first_Num;
		}
		else this->import_Competitor();
		cout << "请输入晋级（决赛）参赛人数：";
		cin >> this->scond_Num;
		cout << "请输入评委人数：";
		cin >> this->judges_Num;
		int judge;
		cout << "评分时是否去掉一个最高分和最低分？（“1”表示“是”，“0”表示“否”）：";
		cin >> judge;
		if (judge == 1)
		{
			this->Whether_To_Remove = true;
		}
		else if(judge== 0)
		{
			this->Whether_To_Remove = false;
		}
		else 
		{
			continue;
		}
		cout << "本次比赛分为初赛和决赛，初赛一共有" << this->first_Num << "人，其中晋级" << this->scond_Num << "人"<<endl<<"是否正确？（“1”表示“是”，“0”表示“否”）：";
		cin >> judge;
		if (judge == 1)
		{
			break;
		}
		else
		{
			continue;
		}

	}
	
}

//选手姓名、编号的生成
void compareManager::createCompetitor() 
{
	for (int i = 0; i < this->first_Num; i++)
	{
		string name;
		string song;
		cout << "输入选手" << i + 1 << "的姓名:";
		cin >> name;
		cout << "输入选手" << i + 1 << "歌曲名:";
		cin >> song;
		Competitor ct;
		ct.name = name;
		ct.song = song;
		//初始化分数
		ct.n_Score[0] = 0;
		ct.n_Score[1] = 0;
		
		//创建选手编号
		this->v1.push_back(i + 10001);

		//选手编号与名字对应
		this->m_Competitor.insert(make_pair(i + 10001, ct));
	}
}

void compareManager::import_Competitor()
{
	ifstream f;
	string line;
	f.open("Competitor_Data.csv", ios::in);
	
	if (!f.is_open())
	{
		cout << "Error:打开文件失败，请确保目录下有该文件！程序自动退出…" << endl;
		exit(1);
	}
	getline(f, line);//跳过第一行
	int count = 0;
	
	while (getline(f, line))
	{
		//cout << "读取一行的数据：" << line << endl;
		string str;
		vector<string> v_data;

		Competitor ct;
		istringstream readstr(line);
		while (getline(readstr, str, ','))
		{
			//cout << str << endl;
			v_data.push_back(str);
		}
		ct.class_ = v_data[0];
		ct.name = v_data[1];
		ct.category = v_data[2];
		ct.song = v_data[3];
		//cout << ct.name<<" "<<ct.song<<endl;

		v_data.clear();
		//初始化分数
		ct.n_Score[0] = 0;
		ct.n_Score[1] = 0;
		//创建选手编号
		this->v1.push_back(count + 10001);

		//选手编号与名字对应
		this->m_Competitor.insert(make_pair(count + 10001, ct));
		count++;
	}
	this->first_Num = count;
	//cout << "共计：" << this->first_Num << endl;
}

void compareManager::Show_info()
{
	for (map<int, Competitor>::iterator it = this->m_Competitor.begin(); it != this->m_Competitor.end(); it++)
	{
		cout << "选手编号：" << it->first << "  姓名：" << it->second.name << "  分数：" << it->second.n_Score[this->m_Index - 1] << endl;
	}
}

//初始化函数
void compareManager::initCompetition()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Competitor.clear();
	this->first_Num = 0;
	this->scond_Num = 0;
	//轮数
	this->m_Index = 1;
}

void compareManager::Start_Competition()
{
	//第一轮比赛
	//抽签
	this->Competition_Draw();
	//比赛+保存数据
	this->Competition_Contest();
	//显示优胜者
	this->show_Score();
	//第二轮比赛
	//抽签
	this->Competition_Draw();
	//比赛+保存数据
	this->Competition_Contest();
	//显示优胜者
	this->show_Score();
}

void compareManager::Competition_Draw()
{
	cout << "第<<" << this->m_Index << ">>比赛正在抽签…" << endl;
	cout << "——————————————————————————" << endl;
	cout << "抽签结果如下：" << endl;
	ofstream p;
	string file_Name = "第" + to_string(this->m_Index) + "轮抽签顺序.csv";
	if (this->m_Index == 1)
	{
		p.open(file_Name, ios::out | ios::trunc);
		p << "编号" << "," << "班级" << "," << "姓名" << "," << "种类" << "," << "节目" << endl;
		srand(static_cast<unsigned int>(time(0)));
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
			cout << m_Competitor[*it].class_<<" " << m_Competitor[*it].name<<"的"<<m_Competitor[*it].category 
				<<" "<<m_Competitor[*it].song << endl;
			//文件写入
			p << *it << "," << m_Competitor[*it].class_ << "," << m_Competitor[*it].name << "," << m_Competitor[*it].category
				<< "," << m_Competitor[*it].song << endl;
		}
		cout << endl;
	}
	if (this->m_Index == 2)
	{
		p.open(file_Name, ios::out | ios::trunc);
		p << "编号" << "," << "班级" << "," << "姓名" << "," << "种类" << "," << "节目" << endl;
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
			
			cout << this->m_Competitor[*it].name << endl;
			//文件写入
			p << *it << "," << m_Competitor[*it].class_ << "," << m_Competitor[*it].name << "," << m_Competitor[*it].category
				<< "," << m_Competitor[*it].song << endl;
		}
		cout << endl;
	}
	p.close();
	cout << "——————————————————————————" << endl;
	cout << "抽签顺序已经输出在文件目录下！" << endl<<"按任意键开始比赛";
	system("pause");
	cout << endl;
}

void compareManager::Competition_Contest()
{
	cout << "——————第" << this->m_Index << "轮比赛正式开始！——————" << endl;
	vector<int>v_Src;
	if (this->m_Index == 1) v_Src = v1; else v_Src = v2;//判断第几轮
	//文件输出流
	ofstream p;
	string file_Name1 = "第" + to_string(this->m_Index) + "轮选手得分.csv";
	p.open(file_Name1, ios::out | ios::trunc);
	p << "编号" << "," << "姓名" << "," << "平均分" << endl;

	multimap<double, int, greater<double>> Score;//临时数据排序

	//遍历
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		deque<double> d;
		cout << "选手" << *it <<" " << this->m_Competitor[*it].name << "正在比赛！下面请为他（她）打分!" << endl;
		for (int i = 0; i < this->judges_Num; i++)
		{
			cout << "第" << i + 1 << "位评委打分：" ;
			double score;
			cin >> score;
			d.push_back(score);

		}
		sort(d.begin(), d.end(), greater<double>());
		if (this->Whether_To_Remove)
		{
			d.pop_front();
			d.pop_back();
		}
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();//平均分
		cout << "他(她)的平均分是：" << avg;
		//写入文件
		p << *it << "," << this->m_Competitor[*it].name << "," << avg << endl;
		//同步到map容器中
		this->m_Competitor[*it].n_Score[this->m_Index - 1] = avg;
		//数据放入临时容器
		Score.insert(make_pair(avg, *it));
		
		cout << endl;
	}
	p.close();
	
	//输出分数
	
	for (multimap<double, int, greater<double>>::iterator it = Score.begin(); it != Score.end(); it++)
	{
		cout << " 编号：" << it->second << " 姓名：" << this->m_Competitor[it->second].name << " 分数："
			<< this->m_Competitor[it->second].n_Score[this->m_Index - 1] << endl;
	}
	
	//文件输出流
	ofstream f;
	string file_Name2 = "第" + to_string(this->m_Index) + "轮优胜者名单.csv";
	f.open(file_Name2, ios::out | ios::trunc);
	f << "编号" << "," << "姓名" << "," << "分数" << endl;
	//取前scond_Num名
	int count = 0;
	for (multimap<double, int, greater<double>>::iterator it = Score.begin(); it != Score.end() && count<this->scond_Num; it++,count++)
	{
		if (this->m_Index == 1)
		{
			v2.push_back((*it).second);
			
		}
		else
		{
			vVictory.push_back((*it).second);
		}
		f << (*it).second << "," << this->m_Competitor[it->second].name << ","
			<< this->m_Competitor[it->second].n_Score[this->m_Index - 1] << endl;
	}
	
	Score.clear();
	f.close();
	cout << "第"<<this->m_Index<<"轮所有选手的平均分已经输出在文件目录下！"<<endl;
	cout << "——————第" << this->m_Index << "轮比赛结束——————" << endl;
	
	system("pause");
}

void compareManager::show_Score()
{
	cout << "——————第" << this-> m_Index << "轮比赛优胜者如下——————" << endl;
	vector<int> v;
	if (this->m_Index == 1) v = v2; else v = vVictory;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << "  姓名：" << this->m_Competitor[*it].name << "  分数："
			<< this->m_Competitor[*it].n_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	if(this->m_Index==1) system("cls");

	this->m_Index++;
}

int compareManager::print_first_Num()
{
	return this->first_Num;
}

int compareManager::print_scond_Num()
{
	return this->scond_Num;
}

void compareManager::Exit()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);

}