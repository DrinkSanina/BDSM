#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
#include <sstream>
#include<chrono>
#include"nlohmann/json.hpp"
using namespace std;
using json = nlohmann::json;
vector<string> ValidPasport(json);
void OutputMAP(vector<string>,int);
vector<string> ParsePOS(json);
//������ �� ���� ����������� � �������� � ������������� �������� ��� ����������
//for (auto& item : data["transactions"].items())
//{
//	string passport = item.value()["passport"].dump();

//	peoplesTransactions[passport].push_back(item.key());
//}

////�������� �������
	////�� ����� ����� ��� ���� �������, ������� �� ������������� �������� ������
	//for (auto it = passportsValidationDates.cbegin(); it != passportsValidationDates.cend();)
	//{
	//	//���� ������ ���� ���� - ������� �� �������
	//	if (it->second.size() == 1)
	//		passportsValidationDates.erase(it++);
	//	else
	//		++it;
	//}
	// 
	// 
////����� ���� ���������� ������������� ��������
//for (map<string, vector<string>>::iterator it = terminals.begin(); it != terminals.end(); it++)
//{
//	cout << "Terminal " << it->first << " locations: ";
//	for (int i = 0; i < it->second.size(); i++)
//	{
//		cout << it->second[i] << " ";
//	}
//	cout << endl;	
//}

////����� ���� ���������� ������������� ��������
//for (map<string, vector<string>>::iterator it = peoplesTransactions.begin(); it != peoplesTransactions.end(); it++)
//{
//	cout << "passport " << it->first << " transactions: ";
//	for (int i = 0; i < it->second.size(); i++)
//	{
//		cout << it->second[i] << " ";
//	}
//	cout << endl;
//}

//��� ���������� � ������������ ���������� �� � ����
//cout << data["transactions"]["<���� - �� ����������>"]["<����� ����>"] << endl;


