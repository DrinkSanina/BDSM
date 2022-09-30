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

	//Загрузить json из файла
	std::ifstream f("transactions.json");
	json data = json::parse(f);


	//На всякий пожарный удобно иметь список всех ключей
	vector<string> transactionIDs;

	//Словарь транзакций по паспорту
	//Ключ - паспорт, вектор - операции
	map<string, vector<string>> peoplesTransactions;

	map<string, vector<string>> terminals;

	for (auto& item : data["transactions"].items())
	{
		//Получить идентификатор транзакции и добавить его в список
		transactionIDs.push_back(item.key());

		string passport = item.value()["passport"].dump();
		
		//Проверка банкоматов
		string terminal = item.value()["terminal"].dump();

		terminals.insert(pair<string, vector<string>>(terminal, {""}));
		


		//Добавить уникальный паспорт и пустой список транзакций в словарь
		peoplesTransactions.insert(pair<string, vector<string>>(passport, {""}));
	}

	//Пройти по всем транзакциям и добавить к определенному терминалу его город
	for (auto& item : data["transactions"].items())
	{
		string terminal = item.value()["terminal"].dump();

		if (!(std::find(terminals[terminal].begin(), terminals[terminal].end(), item.value()["city"].dump()) != terminals[terminal].end()))
		{
			terminals[terminal].push_back(item.value()["city"].dump());
		}

	}

	//Последняя разработка - список банкоматов с уникальными городами. В списке где больше одного уникального города
	//происходит что-то темное


	return 0;
}



