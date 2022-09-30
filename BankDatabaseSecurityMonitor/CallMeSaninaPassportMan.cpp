#include"help.h"

using json = nlohmann::json;

using namespace std;

int main()
{
	setlocale(LC_ALL, "en_us.utf8");

	//��������� json �� �����
	ifstream f("transactions.json");
	json data = json::parse(f);
	std::string date_time_format = "%Y-%m-%d";

	//������� �� �������� � ���������
	map<string, vector<chrono::year_month_day>> passportsValidationDates;

	for (auto& item : data["transactions"].items())
	{
		string passport = item.value()["passport"].dump();
		passportsValidationDates.insert(pair<string, vector<chrono::year_month_day>>{passport, {}});
	}

	//������ �� ���� ����������� � �������� � ������������� ��������� ��� �����
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

	//����� ������� ��������� � ���� ���������
	for (map<string, vector<chrono::year_month_day>>::iterator it = passportsValidationDates.begin(); it != passportsValidationDates.end(); it++)
	{
		cout << "passport " << it->first << " validations: ";
		for (int i = 0; i < it->second.size(); i++)
		{
			cout << it->second[i] << " ";
		}
		cout << endl;
	}

	//��������� ���������� - ������ ���������� � ����������� ��������. � ������ ��� ������ ������ ����������� ������
	//���������� ���-�� ������


	return 0;
}
