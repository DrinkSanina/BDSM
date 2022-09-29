#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>

#include"nlohmann/json.hpp"

using json = nlohmann::json;

int main()
{
	//��������� json �� �����
	std::ifstream f("transactions.json");
	json data = json::parse(f);

	//���� ������� �� ���� �����������
	for (auto& item : data["transactions"].items())
	{
		//�������� ������������� ����������
		std::cout << item.key() << "\n";

		//�������� ������������ ��������
		std::cout << item.value()["date"] << std::endl;
	}

	return 0;
}