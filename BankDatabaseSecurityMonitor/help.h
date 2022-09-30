#pragma once


//Пройти по всем транзакциям и добавить к определенному паспорту его транзакцию
//for (auto& item : data["transactions"].items())
//{
//	string passport = item.value()["passport"].dump();

//	peoplesTransactions[passport].push_back(item.key());
//}


////Вывод всех транзакций определенного паспорта
//for (map<string, vector<string>>::iterator it = terminals.begin(); it != terminals.end(); it++)
//{
//	cout << "Terminal " << it->first << " locations: ";
//	for (int i = 0; i < it->second.size(); i++)
//	{
//		cout << it->second[i] << " ";
//	}
//	cout << endl;	
//}

////Вывод всех транзакций определенного паспорта
//for (map<string, vector<string>>::iterator it = peoplesTransactions.begin(); it != peoplesTransactions.end(); it++)
//{
//	cout << "passport " << it->first << " transactions: ";
//	for (int i = 0; i < it->second.size(); i++)
//	{
//		cout << it->second[i] << " ";
//	}
//	cout << endl;

//	
//}

//Как обратиться к определенной транзакции по её дате
//cout << data["transactions"]["459273621"]["date"] << endl;