#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>

#include"nlohmann/json.hpp"

using json = nlohmann::json;

int main()
{
	//Загрузить json из файла
	std::ifstream f("transactions.json");
	json data = json::parse(f);

	//Цикл прохода по всем транзакциям
	for (auto& item : data["transactions"].items())
	{
		//Получить идентификатор транзакции
		std::cout << item.key() << "\n";

		//Получить определенное значение
		std::cout << item.value()["date"] << std::endl;
	}

	return 0;
}