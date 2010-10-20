#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;


class AIPlayer {
private:

	double bluff;	// ���������� �����
	double risk;	// ���������� ����, ��� ������� 

	bool is_fold;	// �������� ��� ���
	bool is_shared;	// ��� ������� ����� ��� ���
	int money;

	vector <int> cards_card;
	vector <int> cards_suit;

public:

	
};
