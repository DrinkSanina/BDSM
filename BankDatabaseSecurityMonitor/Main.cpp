
#include"help.h"




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
	OutputMAP(terminals,1);
	OutputMAP(passportsValidationDates,2);
	

	

	


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
	for (auto& item : data["transactions"].items()) {
		string term = item.value()["terminal"].dump();
		if (terminals.find(term) != terminals.end()) {
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
