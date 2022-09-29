#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>

#include"nlohmann/json.hpp"

using json = nlohmann::json;

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	//��������� json �� �����
	std::ifstream f("transactions.json");
	json data = json::parse(f);

	//�� ������ �������� ������ ����� ������ ���� ������
	vector<string> transactionIDs;

	//������� ���������� �� ��������
	//���� - �������, ������ - ��������
	map<string, vector<string>> peoplesTransactions;

	for (auto& item : data["transactions"].items())
	{
		//�������� ������������� ���������� � �������� ��� � ������
		transactionIDs.push_back(item.key());

		string passport = item.value()["passport"].dump();

		//�������� ���������� ������� � ������ ������ ���������� � �������
		peoplesTransactions.insert(pair<string, vector<string>>(passport, {""}));
	}


	//������ �� ���� ����������� � �������� � ������������� �������� ��� ����������
	for (auto& item : data["transactions"].items())
	{
		string passport = item.value()["passport"].dump();

		peoplesTransactions[passport].push_back(item.key());
	}

	//����� ���� ���������� ������������� ��������
	for (map<string, vector<string>>::iterator it = peoplesTransactions.begin(); it != peoplesTransactions.end(); it++)
	{
		cout << "passport " << it->first << " transactions: ";
		for (int i = 0; i < it->second.size(); i++)
		{
			cout << it->second[i] << " ";
		}
		cout << endl;
	}

	//��� ���������� � ������������ ���������� �� � ����
	//cout << data["transactions"]["459273621"]["date"] << endl;


	return 0;
}


