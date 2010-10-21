#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

struct Card
{
	int rang;
	int suit;

	Card(int i, int j)
	{
		rang = j;
		suit = i;
	}
	    
};

class AIPlayer {
private:

	double bluff;	// ���������� �����
	double risk;	// ���������� ����, ��� ������� 

	bool is_fold;	// �������� ��� ���
	bool is_shared;	// ��� ������� ����� ��� ���
	int money;

	vector <Card> cards;

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
	void setCards ( vector<Card> _cards ) {
		
		is_shared = false;

		cards = _cards;
	}

	// �������� ���������� �����
	void addCards ( vector<Card> exchanged_cards ) {
		
		is_shared = true;

		for ( int i = 0; i < exchanged_cards.size(); i++ ) {

			cards.push_back ( exchanged_cards[i] );
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

		if ( same_suit.size() < 3 && cards_sequence.size() < 3 ) {
			
			if ( rand() + risk > 0.8 ) {	// �������-������ ��� �����
				
				int arr[] = { 0,1,2,3,4 };
				deleteCards ( arr, 5 );
				return 5;
			}

			if ( cards[3].rang >= 10 ) {	// ��� ��������� ����� ������ ���� ����� ������
				
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
				
				// ������� ��������� � �������� 2-14 ( � ���� ������ ����� ������ )
				if ( cards[cards_sequence[0]].rang > 3 && cards[cards_sequence[cards_sequence.size() - 1]].rang < 13 ) {

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

		for ( int i = 0; i < cards.size(); i++ ) {

			suit = cards[i].suit;
			tmp_info.push_back ( i );

			for ( int j = 0; j < cards.size(); j++ ) {

				if ( i != j ) {
					
					if ( cards[j].suit == suit ) {
						
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

		for ( int i = 1; i < cards.size(); i ++ ) {
			
			if ( cards[i].rang != cards[i - 1].rang + 1 ) {
				
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

		int last_index = cards.size();

		while ( last_index > 1 ) {

			for ( int i = 0; i < last_index; i++ ) {
				
				if ( i + 1 < last_index ) {

					if ( cards[i].rang > cards[i + 1].rang ) {
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

		for ( int i = 0; i < cards.size(); i++ ) {

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
		
		Card* tmp = new Card ( cards[ind_1].rang, cards[ind_1].suit );

		cards[ind_1] = cards[ind_2];

		cards[ind_2].rang = tmp->rang;
		cards[ind_2].suit = tmp->suit;
	}

	// ������� ����� �� �������
	void deleteCard ( int index ) {

		vector<Card> tmp_cards;

		for ( int i = 0; i < cards.size(); i++ ) {
			
			if ( i != index ) {
				
				tmp_cards.push_back ( cards[i] );
			}
		}

		cards = tmp_cards;
	}

	// ������� �����
	void deleteCards ( int* cards, int count ) {
		
		for ( int i = count - 1; i >= 0; i-- ) {
			
			deleteCard ( cards[i] );
		}
	}
	
};
