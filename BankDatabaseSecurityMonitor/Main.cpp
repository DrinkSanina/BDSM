
#include"help.h"

struct Fraud
{
	int temp_number;
	vector<string> transactions;

	string toString()
	{
		string result = "[" + to_string(temp_number) + "]\t[";

		for (string id : transactions)
		{
			result += id + ", ";
		}
		result.pop_back();
		result.pop_back();
		result += "]";

		return result;
	}

	Fraud(int temp_number, vector<string> transactions)
	{
		this->temp_number = temp_number;
		this->transactions = transactions;
	}
};


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


	vector<string> passportsValidationDates = ValidPasport(data);
	vector<string> terminals = ParsePOS(data);
	vector<string> accounts = ValidAccount(data);

	Fraud terminal_fraud(1, terminals);
	Fraud passport_fraud(2, passportsValidationDates);
	Fraud account_fraud(3, accounts);

	cout << terminal_fraud.toString() << endl;
	cout << passport_fraud.toString() << endl;
	cout << account_fraud.toString() << endl;


	//OutputMAP(terminals,1);
	//OutputMAP(passportsValidationDates,2);
	//OutputMAP(accounts, 3);

	return 0;
}

vector<string> ParsePOS(json data) {
	

	map<string, vector<string>> terminals;
	for (auto& item : data["transactions"].items())
	{
		


		//Проверка банкоматов и создание словаря с терминалами и городами
		string terminal = item.value()["terminal"].dump();

		terminals.insert(pair<string, vector<string>>(terminal, {}));

	}
	//добавление городов где был каждый банкомат
	for (auto& item : data["transactions"].items())
	{
		string terminal = item.value()["terminal"].dump();

		if (!(std::find(terminals[terminal].begin(), terminals[terminal].end(), item.value()["city"].dump()) != terminals[terminal].end()))
		{
			terminals[terminal].push_back(item.value()["city"].dump());
		}

	}
	//удаление словарей с посами у которых 1 город
	for (map<string, vector<string>>::iterator it = terminals.begin(); it != terminals.end();) {
		if (it->second.size() == 1) {
			terminals.erase(it++);
		}
		else {
			++it;
		}
	}
	vector<string> transaction;
	for (auto& item : data["transactions"].items()) 
	 {
		string term = item.value()["terminal"].dump();
		if (terminals.find(term) != terminals.end()) 
		{
			transaction.push_back(item.key());
		}
	}
	return transaction;
}



void OutputMAP(vector<string> output, int shablon) {
	for (int i =0; i<output.size();i++)
	{
		cout << "bad transaction " << output[i] << " Shablon: " << shablon << endl;;
		
	}
}


vector<string> AssEater(vector<string> pos_naeberi, vector<string> account_naeberi, vector<string> passport_naeberi)
{
	vector<string> result;

	for (string id : pos_naeberi)
	{
		result.push_back(id);
	}

	for (string id : account_naeberi)
	{
		if (!(find(result.begin(), result.end(), id) != result.end()))
		{
			result.push_back(id);
		}
	}

	for (string id : passport_naeberi)
	{
		if (!(find(result.begin(), result.end(), id) != result.end()))
		{
			result.push_back(id);
		}
	}

	return result;
}
