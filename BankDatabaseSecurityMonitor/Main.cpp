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

	//Загрузить json из файла
	std::ifstream f("transactions.json");
	json data = json::parse(f);

	//На всякий пожарный удобно иметь список всех ключей
	vector<string> transactionIDs;

	//Словарь транзакций по паспорту
	//Ключ - паспорт, вектор - операции
	map<string, vector<string>> peoplesTransactions;

	for (auto& item : data["transactions"].items())
	{
		//Получить идентификатор транзакции и добавить его в список
		transactionIDs.push_back(item.key());

		string passport = item.value()["passport"].dump();

		//Добавить уникальный паспорт и пустой список транзакций в словарь
		peoplesTransactions.insert(pair<string, vector<string>>(passport, {""}));
	}


	//Пройти по всем транзакциям и добавить к определенному паспорту его транзакцию
	for (auto& item : data["transactions"].items())
	{
		string passport = item.value()["passport"].dump();

		peoplesTransactions[passport].push_back(item.key());
	}

	//Вывод всех транзакций определенного паспорта
	for (map<string, vector<string>>::iterator it = peoplesTransactions.begin(); it != peoplesTransactions.end(); it++)
	{
		cout << "passport " << it->first << " transactions: ";
		for (int i = 0; i < it->second.size(); i++)
		{
			cout << it->second[i] << " ";
		}
		cout << endl;
	}

	//Как обратиться к определенной транзакции по её дате
	//cout << data["transactions"]["459273621"]["date"] << endl;


	return 0;
}


