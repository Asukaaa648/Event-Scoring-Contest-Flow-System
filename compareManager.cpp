#include <iostream>
#include "compareManager.h"
#include "competitor.h"
#include <fstream>
#include <string>
#include <deque>
using namespace std;

compareManager::compareManager()
{
	//��ʼ������������
	this->initCompetition();
}

compareManager::~compareManager()
{

}

void compareManager::Show_Menu()
{
	cout << "��ӭʹ�û�������̹���ϵͳ��" << endl;
	cout << "���롰1����ʼ�ݽ�����,���롰0���˳�����";
}

//������������������������ȡ�Լ��㷨��ȷ��
void compareManager::Design_Process(int choice)
{
	while (true)
	{
		if (choice != 1)
		{
			cout << "���������ѡ��������";
			cin >> this->first_Num;
		}
		else this->import_Competitor();
		cout << "���������������������������";
		cin >> this->scond_Num;
		cout << "��������ί������";
		cin >> this->judges_Num;
		int judge;
		cout << "����ʱ�Ƿ�ȥ��һ����߷ֺ���ͷ֣�����1����ʾ���ǡ�����0����ʾ���񡱣���";
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
		cout << "���α�����Ϊ�����;���������һ����" << this->first_Num << "�ˣ����н���" << this->scond_Num << "��"<<endl<<"�Ƿ���ȷ������1����ʾ���ǡ�����0����ʾ���񡱣���";
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

//ѡ����������ŵ�����
void compareManager::createCompetitor() 
{
	for (int i = 0; i < this->first_Num; i++)
	{
		string name;
		string song;
		cout << "����ѡ��" << i + 1 << "������:";
		cin >> name;
		cout << "����ѡ��" << i + 1 << "������:";
		cin >> song;
		Competitor ct;
		ct.name = name;
		ct.song = song;
		//��ʼ������
		ct.n_Score[0] = 0;
		ct.n_Score[1] = 0;
		
		//����ѡ�ֱ��
		this->v1.push_back(i + 10001);

		//ѡ�ֱ�������ֶ�Ӧ
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
		cout << "Error:���ļ�ʧ�ܣ���ȷ��Ŀ¼���и��ļ��������Զ��˳���" << endl;
		exit(1);
	}
	getline(f, line);//������һ��
	int count = 0;
	
	while (getline(f, line))
	{
		//cout << "��ȡһ�е����ݣ�" << line << endl;
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
		//��ʼ������
		ct.n_Score[0] = 0;
		ct.n_Score[1] = 0;
		//����ѡ�ֱ��
		this->v1.push_back(count + 10001);

		//ѡ�ֱ�������ֶ�Ӧ
		this->m_Competitor.insert(make_pair(count + 10001, ct));
		count++;
	}
	this->first_Num = count;
	//cout << "���ƣ�" << this->first_Num << endl;
}

void compareManager::Show_info()
{
	for (map<int, Competitor>::iterator it = this->m_Competitor.begin(); it != this->m_Competitor.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << it->first << "  ������" << it->second.name << "  ������" << it->second.n_Score[this->m_Index - 1] << endl;
	}
}

//��ʼ������
void compareManager::initCompetition()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Competitor.clear();
	this->first_Num = 0;
	this->scond_Num = 0;
	//����
	this->m_Index = 1;
}

void compareManager::Start_Competition()
{
	//��һ�ֱ���
	//��ǩ
	this->Competition_Draw();
	//����+��������
	this->Competition_Contest();
	//��ʾ��ʤ��
	this->show_Score();
	//�ڶ��ֱ���
	//��ǩ
	this->Competition_Draw();
	//����+��������
	this->Competition_Contest();
	//��ʾ��ʤ��
	this->show_Score();
}

void compareManager::Competition_Draw()
{
	cout << "��<<" << this->m_Index << ">>�������ڳ�ǩ��" << endl;
	cout << "����������������������������������������������������" << endl;
	cout << "��ǩ������£�" << endl;
	ofstream p;
	string file_Name = "��" + to_string(this->m_Index) + "�ֳ�ǩ˳��.csv";
	if (this->m_Index == 1)
	{
		p.open(file_Name, ios::out | ios::trunc);
		p << "���" << "," << "�༶" << "," << "����" << "," << "����" << "," << "��Ŀ" << endl;
		srand(static_cast<unsigned int>(time(0)));
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
			cout << m_Competitor[*it].class_<<" " << m_Competitor[*it].name<<"��"<<m_Competitor[*it].category 
				<<" "<<m_Competitor[*it].song << endl;
			//�ļ�д��
			p << *it << "," << m_Competitor[*it].class_ << "," << m_Competitor[*it].name << "," << m_Competitor[*it].category
				<< "," << m_Competitor[*it].song << endl;
		}
		cout << endl;
	}
	if (this->m_Index == 2)
	{
		p.open(file_Name, ios::out | ios::trunc);
		p << "���" << "," << "�༶" << "," << "����" << "," << "����" << "," << "��Ŀ" << endl;
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
			
			cout << this->m_Competitor[*it].name << endl;
			//�ļ�д��
			p << *it << "," << m_Competitor[*it].class_ << "," << m_Competitor[*it].name << "," << m_Competitor[*it].category
				<< "," << m_Competitor[*it].song << endl;
		}
		cout << endl;
	}
	p.close();
	cout << "����������������������������������������������������" << endl;
	cout << "��ǩ˳���Ѿ�������ļ�Ŀ¼�£�" << endl<<"���������ʼ����";
	system("pause");
	cout << endl;
}

void compareManager::Competition_Contest()
{
	cout << "��������������" << this->m_Index << "�ֱ�����ʽ��ʼ��������������" << endl;
	vector<int>v_Src;
	if (this->m_Index == 1) v_Src = v1; else v_Src = v2;//�жϵڼ���
	//�ļ������
	ofstream p;
	string file_Name1 = "��" + to_string(this->m_Index) + "��ѡ�ֵ÷�.csv";
	p.open(file_Name1, ios::out | ios::trunc);
	p << "���" << "," << "����" << "," << "ƽ����" << endl;

	multimap<double, int, greater<double>> Score;//��ʱ��������

	//����
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		deque<double> d;
		cout << "ѡ��" << *it <<" " << this->m_Competitor[*it].name << "���ڱ�����������Ϊ�����������!" << endl;
		for (int i = 0; i < this->judges_Num; i++)
		{
			cout << "��" << i + 1 << "λ��ί��֣�" ;
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
		double avg = sum / (double)d.size();//ƽ����
		cout << "��(��)��ƽ�����ǣ�" << avg;
		//д���ļ�
		p << *it << "," << this->m_Competitor[*it].name << "," << avg << endl;
		//ͬ����map������
		this->m_Competitor[*it].n_Score[this->m_Index - 1] = avg;
		//���ݷ�����ʱ����
		Score.insert(make_pair(avg, *it));
		
		cout << endl;
	}
	p.close();
	
	//�������
	
	for (multimap<double, int, greater<double>>::iterator it = Score.begin(); it != Score.end(); it++)
	{
		cout << " ��ţ�" << it->second << " ������" << this->m_Competitor[it->second].name << " ������"
			<< this->m_Competitor[it->second].n_Score[this->m_Index - 1] << endl;
	}
	
	//�ļ������
	ofstream f;
	string file_Name2 = "��" + to_string(this->m_Index) + "����ʤ������.csv";
	f.open(file_Name2, ios::out | ios::trunc);
	f << "���" << "," << "����" << "," << "����" << endl;
	//ȡǰscond_Num��
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
	cout << "��"<<this->m_Index<<"������ѡ�ֵ�ƽ�����Ѿ�������ļ�Ŀ¼�£�"<<endl;
	cout << "��������������" << this->m_Index << "�ֱ�������������������" << endl;
	
	system("pause");
}

void compareManager::show_Score()
{
	cout << "��������������" << this-> m_Index << "�ֱ�����ʤ�����¡�����������" << endl;
	vector<int> v;
	if (this->m_Index == 1) v = v2; else v = vVictory;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << "  ������" << this->m_Competitor[*it].name << "  ������"
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
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);

}