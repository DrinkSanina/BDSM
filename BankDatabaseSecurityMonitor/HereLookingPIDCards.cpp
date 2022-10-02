#include"help.h"



vector<string> AccountClient(json data)
{

	

	map<string, vector<string>> clients;
	for (auto& item : data["transactions"].items())
	{



		//ДОБАВЛЕНИЕ КЛИЕНТОВ В СЛОВАРЬ
		string client = item.value()["client"].dump();

		clients.insert(pair<string, vector<string>>(client, {}));

	}
	//добавление аккаунтов для клиентов
	for (auto& item : data["transactions"].items())
	{
		string client = item.value()["client"].dump();

		if (!(std::find(clients[client].begin(), clients[client].end(), item.value()["client"].dump()) != clients[client].end()))
		{
			clients[client].push_back(item.value()["account"].dump());
		}

	}
	//удаление словарей с клиентами у которых 1 аккаунт
	for (map<string, vector<string>>::iterator it = clients.begin(); it != clients.end();) {
		if (it->second.size() <= 3) {
			clients.erase(it++);
		}
		else {
			++it;
		}
	}
	/*for (map<string, vector<string>>::iterator it = clients.begin(); it != clients.end(); it++)
{
	cout << "client " << it->first << " account: ";
	for (int i = 0; i < it->second.size(); i++)
	{
		cout << it->second[i] << " ";
	}
	cout << endl;	
}*/
	vector<string> transaction;
	for (auto& item : data["transactions"].items())
	{
		string client = item.value()["client"].dump();
		if (clients.find(client) != clients.end())
		{
			transaction.push_back(item.key());
		}
	}
	return transaction;
}

