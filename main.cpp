#include "AIPlayer.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class Deck
{
	int CountOfCards;
	
	vector<Cart> cards[52];
	
	Deck()
	{
		CountOfCards = 52;
		int n = 0;
		for (int i = 0; i < 4; i++)
		{
		    for (int j = 2; j <= 14; j++)
		    {
		        cards[n] = Card(j, i);
				n++;
		    }
		}
	}

	void Shafl()
	{
        for (int i = 0; i < CountOfCards; i++)
        {
			int rndInd = rand() % CountOfCards ;
            Card tmp = cards[i];
            cards[i] = cards[rndInd];
            cards[rndInd] = tmp;
        }
	};
};



int main()
{
	return 0;
}

