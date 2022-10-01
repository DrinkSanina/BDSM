#include"help.h"

vector<string> ValidAccount(json data)
{
	std::string date_time_format = "%Y-%m-%d";

	//������� �� �������� � ���������
	map<string, chrono::year_month_day> accountValidationDates;

	for (auto& item : data["transactions"].items())
	{
		string passport = item.value()["account"].dump();
		accountValidationDates.insert(pair<string, chrono::year_month_day>{passport, {}});
	}

	//������ �� ���� ����������� � �������� � ������������� �������� ��� ���������� 
	for (auto& item : data["transactions"].items())
	{
		string passport = item.value()["account"].dump();
		string valid_to = item.value()["account_valid_to"].dump();

		valid_to = valid_to.substr(1, 10);
		chrono::year_month_day valid_to_date;

		istringstream ss{ valid_to };

		ss >> chrono::parse(date_time_format, valid_to_date);

		accountValidationDates[passport] = valid_to_date;
	}



	//�������� �� ������� ���� ��� ����� ���� ���������� �������� ������ ���� ����������
	for (auto& item : data["transactions"].items())
	{
		string passport = item.value()["account"].dump();

		if (accountValidationDates.find(passport) != accountValidationDates.end())
		{
			string valid_to = item.value()["date"].dump();
			valid_to = valid_to.substr(1, 10);
			chrono::year_month_day valid_to_date;

			istringstream ss{ valid_to };

			ss >> chrono::parse(date_time_format, valid_to_date);

			if (accountValidationDates[passport] > valid_to_date)
			{
				accountValidationDates.erase(passport);
			}

		}
	}
	//�������� ������� � ���������� � ���� ���� �������������� ���������� 
	vector<string> transaction;
	for (auto& item : data["transactions"].items()) {
		string pass = item.value()["account"].dump();
		if (accountValidationDates.find(pass) != accountValidationDates.end()) {
			transaction.push_back(item.key());
		}
	}


	//��������� ���������� -  �������� ������ ������

	return transaction;
}