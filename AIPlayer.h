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
	
	AIPlayer() {

		bluff = rand();
		risk = rand();

		is_fold = false;
		money = 10000;
	}

	~AIPlayer() {
	}

	// �������� �������
	void setCards ( vector<int> _cards, vector<int> _suits ) {
		
		is_shared = false;

		cards_card = _cards;
		cards_suit = _suits;
	}

	// �������� ���������� �����
	void addCards ( vector<int> exchanged_cards, vector<int> _suits ) {
		
		is_shared = true;

		for ( int i = 0; i < exchanged_cards.size(); i++ ) {

			cards_card.push_back ( exchanged_cards[i] );
			cards_suit.push_back ( _suits[i] );
		}
	}

	// ������ ���������� ����, ������� ����� ��������
	int CardsToShare() {

		cardSort();
		
		vector<int> same_suit = getSameSuit();
		vector<int> cards_sequence = getCardSequence();

		if ( true /* ���� ���������� */ ) {
			/* ������ �� �������� � ����������*/
		}

		if ( same_suit.size() < 3 && cards_suit.size() < 3 ) {
			
			if ( rand() + risk > 0.8 ) {	// �������-������ ��� �����
				
				int arr[] = { 0,1,2,3,4 };
				deleteCards ( arr, 5 );
				return 5;
			}

			if ( cards_card[3] >= 10 ) {	// ��� ��������� ����� ������ ���� ����� ������
				
				int arr[] = { 0,1,2 };
				deleteCards ( arr, 3 );
				return 3;
			}

			if ( same_suit.size() > 1 ) {
			
				deleteCards ( getOther ( same_suit ), 3 );
				return 3; 

			}

			int arr[] = { 0,1,2,3 };
			deleteCards ( arr, 4 );
			return 4;

		} else {
			
			if ( same_suit.size() > cards_sequence.size() ) {
				
				int tmp = 5 - same_suit.size();
				deleteCards ( getOther ( same_suit ), tmp );
				return tmp; 
			} 

			if ( same_suit.size() < cards_sequence.size() ) {
				
				int tmp = 5 - cards_sequence.size();
				deleteCards ( getOther ( cards_sequence ), tmp );
				return tmp; 
			}

			if ( same_suit.size() == cards_sequence.size() ) {
				
				// ������� ��������� � �������� 1-13 ( � ���� ������ ����� ������ )
				if ( cards_card[cards_sequence[0]] > 2 && cards_card[cards_sequence[cards_sequence.size() - 1]] < 12 ) {

					int tmp = 5 - cards_sequence.size();
					deleteCards ( getOther ( cards_sequence ), tmp );
					return tmp;

				} else {
					
					int tmp = 5 - same_suit.size();
					deleteCards ( getOther ( same_suit ), tmp );
					return tmp;
				}
			}
		}

		int arr[] = { 0,1,2,3,4 };
		deleteCards ( arr, 5 );
		return 5;

	} 

	// ������ ����� ���������� �����
	vector<int> getSameSuit() {
		
		int suit;
		vector<int> info; 
		vector<int> tmp_info;

		for ( int i = 0; i < cards_card.size(); i++ ) {

			suit = cards_suit[i];
			tmp_info.push_back ( i );

			for ( int j = 0; j < cards_card.size(); j++ ) {

				if ( i != j ) {
					
					if ( cards_suit[j] == suit ) {
						
						tmp_info.push_back ( j );
					}
				}
			}

			if ( tmp_info.size() >= 3 ) {
				
				info = tmp_info;
				break;
			} else if ( tmp_info.size() > info.size() ) {

				info = tmp_info;
			}

			tmp_info.clear();
		}

		return info;
	}

	// ������ ����� ����� �� �������
	vector<int> getCardSequence() {

		vector<int> best;
		vector<int> tmp;

		tmp.push_back ( 0 );

		for ( int i = 1; i < cards_card.size(); i ++ ) {
			
			if ( cards_card[i] != cards_card[i - 1] + 1 ) {
				
				if ( tmp.size() > best.size() ) {
					best = tmp;
				}
				tmp.clear();

			}

			tmp.push_back ( i );
		}

		if ( tmp.size() > best.size() ) {
			best = tmp;
		}

		return best;
	}

	// ���������� �� ������ �����
	void cardSort() {

		int last_index = cards_card.size();

		while ( last_index > 1 ) {

			for ( int i = 0; i < last_index; i++ ) {
				
				if ( i + 1 < last_index ) {

					if ( cards_card[i] > cards_card[i + 1] ) {
						swapCards ( i, i + 1 );
					}
				}
			}
			last_index--;
		}
	}

	// ������ ������� ��� ����, ������� �� ���������� � �������
	int* getOther ( vector<int> mass ) {

		int* result = new int[5 - mass.size()];
		int index = 0;

		for ( int i = 0; i < cards_card.size(); i++ ) {

			for ( int j = 0; j < mass.size(); i++ ) {
				
				if ( mass[j] == i ) { 
					break;
				} else if ( j + 1 == mass.size() ) {
					
					result[index] = i;
					index++;
				}
			}
		}

		return result;
	}

	// �������� �������
	void swapCards ( int ind_1, int ind_2 ) {
		
		int tmp_card = cards_card[ind_1];
		int tmp_suit = cards_suit[ind_1];

		cards_card[ind_1] = cards_card[ind_2];
		cards_suit[ind_1] = cards_suit[ind_2];

		cards_card[ind_2] = tmp_card;
		cards_suit[ind_2] = tmp_suit;
	}

	// ������� ����� �� �������
	void deleteCard ( int index ) {

		vector<int> tmp_cards;
		vector<int> tmp_suits;

		for ( int i = 0; i < cards_card.size(); i++ ) {
			
			if ( i != index ) {
				
				tmp_cards.push_back ( cards_card[i] );
				tmp_suits.push_back ( cards_suit[i] );
			}
		}

		cards_card = tmp_cards;
		cards_suit = tmp_suits;
	}

	// ������� �����
	void deleteCards ( int* cards, int count ) {
		
		for ( int i = count - 1; i >= 0; i-- ) {
			
			deleteCard ( cards[i] );
		}
	}
	
};
