#include"help.h"



vector<string> ValidPasport(json data)
{

	std::string date_time_format = "%Y-%m-%d";

	//Выборка по паспорту и валидации
	map<string, vector<chrono::year_month_day>> passportsValidationDates;

	for (auto& item : data["transactions"].items())
	{
		string passport = item.value()["passport"].dump();
		passportsValidationDates.insert(pair<string, vector<chrono::year_month_day>>{passport, {}});
	}

	//Пройти по всем транзакциям и добавить к определенному номеру паспорта его валидность 
	for (auto& item : data["transactions"].items())
	{
		string passport = item.value()["passport"].dump();
		string valid_to = item.value()["passport_valid_to"].dump();

		valid_to = valid_to.substr(1, 10);
		chrono::year_month_day valid_to_date;

		istringstream ss{ valid_to };

		ss >> chrono::parse(date_time_format, valid_to_date);

		if (!(std::find(passportsValidationDates[passport].begin(), passportsValidationDates[passport].end(), valid_to_date) != passportsValidationDates[passport].end()))
		{
			passportsValidationDates[passport].push_back(valid_to_date);
		}
	}

	
	//удаление из словаря всех кто имеет одну валидность паспорта старше даты транзакции
	for (auto& item : data["transactions"].items())
	{
		string passport = item.value()["passport"].dump();

		if (passportsValidationDates.find(passport) != passportsValidationDates.end())
		{
			string valid_to = item.value()["date"].dump();
			valid_to = valid_to.substr(1, 10);
			chrono::year_month_day valid_to_date;

			istringstream ss{ valid_to };

			ss >> chrono::parse(date_time_format, valid_to_date);

			if (passportsValidationDates[passport].size() == 1 && passportsValidationDates[passport][0] > valid_to_date)
			{
				passportsValidationDates.erase(passport);
			}
			
		}
	}
	//создание вектора и добавление в него всех подозрительных транзакций 
	vector<string> transaction;
	for (auto& item : data["transactions"].items()) {
		string pass = item.value()["passport"].dump();
		if (passportsValidationDates.find(pass) != passportsValidationDates.end()) {
			transaction.push_back(item.key());
		}
	}
	

	//Последняя разработка -  добваили второй патерн

	return transaction;
}
