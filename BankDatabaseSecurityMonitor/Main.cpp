#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
#include <io.h>
#include <fcntl.h>

#include"nlohmann/json.hpp"

using json = nlohmann::json;

using namespace std;


int main()
{
	setlocale(LC_ALL, "en_us.utf8");

	//��������� json �� �����
	std::ifstream f("transactions.json");
	json data = json::parse(f);


	//�� ������ �������� ������ ����� ������ ���� ������
	vector<string> transactionIDs;

	//������� ���������� �� ��������
	//���� - �������, ������ - ��������
	map<string, vector<string>> peoplesTransactions;

	map<string, vector<string>> terminals;

	for (auto& item : data["transactions"].items())
	{
		//�������� ������������� ���������� � �������� ��� � ������
		transactionIDs.push_back(item.key());

		string passport = item.value()["passport"].dump();
		
		//�������� ����������
		string terminal = item.value()["terminal"].dump();

		terminals.insert(pair<string, vector<string>>(terminal, {""}));
		


		//�������� ���������� ������� � ������ ������ ���������� � �������
		peoplesTransactions.insert(pair<string, vector<string>>(passport, {""}));
	}

	//������ �� ���� ����������� � �������� � ������������� ��������� ��� �����
	for (auto& item : data["transactions"].items())
	{
		string terminal = item.value()["terminal"].dump();

		if (!(std::find(terminals[terminal].begin(), terminals[terminal].end(), item.value()["city"].dump()) != terminals[terminal].end()))
		{
			terminals[terminal].push_back(item.value()["city"].dump());
		}

	}

	//��������� ���������� - ������ ���������� � ����������� ��������. � ������ ��� ������ ������ ����������� ������
	//���������� ���-�� ������


	return 0;
}



