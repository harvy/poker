#pragma once
#include "AIPlayer.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Combo
{
public:
	vector<Card> plCards[5];
	int numCombo;
	string nameCombo;
	bool testFlush;
	bool testStrit;
	int massiv[5][2];
	Combo()
	{
		numCombo=11;
		testFlush=true;
		testStrit=false;
		int tmp=0;
		//	какие карты повтор€ютьс€
		for(int i=0;i<5;i++)
		{
			plCards[i]
			massiv[0][i]=plCards[i]->rang;
			massiv[1][i]=1;
		}
		for(int i=0; i<5; i++)
		{
			for(int j=5-i; j>i; j--)
			{
				if(massiv[0][j-1] > massiv[0][j])
				{
					tmp=massiv[0][j-1];
					massiv[0][j-1] = massiv[0][j];
					massiv[0][j]=tmp; 
				}
			}
		}
		for(int i=4; i>0; i--)
		{
			if(massiv[0][i] = massiv[0][i-1])
			{
				massiv[1][i-1] += massiv[1][i];
				massiv[1][i]=0;
			}
		}
		for(int i=0; i<5; i++)
		{
			for(int j=5-i; j>i; j--)
			{
				if(massiv[1][j-1] > massiv[1][j])
				{
					tmp=massiv[1][j-1];
					massiv[1][j-1] = massiv[1][j];
					massiv[1][j] = tmp; 
				}
			}
		}
		//тест на флэш	
		for(int i=0; i<4; i++)
		{
			if(plCarts[i]->suit != plCarts[i+1]->suit)
			{
				testFlush=false;
			}
		}
		//тест на стрит;
		for(int i=0; i<4; i++)
		{
			if(massiv[0][i]!=massiv[0][i]-1)
			{
				testStrit=false;
			}
		}
		Funk();
	}


	void Funk()
	{

		if(testFlush==true && testStrit==true)
		{
			if(massiv[0][1]=13)
			{
				numCombo = 1;
				nameCombo ="FR";
				return;
			}else{
				numCombo = 2;
				nameCombo ="SF";
				return;
			}
		}
		if(massiv[0][1]==3 && massiv[0][2]==2)
		{
			numCombo = 3;
			nameCombo ="FH";
			return;
		}
		if(massiv[0][1]==4)
		{
			numCombo = 4;
			nameCombo ="Kare";
			return;
		}
		if(testFlush==true)
		{
			numCombo = 5;
			nameCombo ="Flush";
			return;
		}	
		if(testStrit==true)
		{
			numCombo = 6;
			nameCombo ="Strit";
			return;
		}
		if(massiv[0][1]==3)
		{
			numCombo =7;
			nameCombo ="tri";
			return;
		}
			
		if(massiv[0][1]==2 && massiv[0][2]==2)
		{
			numCombo = 8;
			nameCombo ="2 par";
			return;
		}
		if(massiv[0][1]==3)
		{
			numCombo =9;
			nameCombo ="Para";
			return;
		}
		else
		{	
			numCombo =10;
			nameCombo ="VK";
			return;
		}
	}
	//если с1 больше то 0, если равны то 1, если меньше то 2
	int sravnenie(Combo c1, Combo c2)
{
	if(c1.numCombo > c2.numCombo)
	{
		return 0;
	}
	if(c1.numCombo < c2.numCombo)
	{
		return 2;
	}
	for(int i=0; i<5; i++)
	{
		if(c1.massiv[1][i]>c2.massiv[1][i])
		{
			return 0;
		}	
		if(c1.massiv[1][i]<c2.massiv[1][i])
		{
			return 2;
		}
	}
	return 1;
}
	//возращ€ет удачные индексы
	vector<int> getIndex()
	{
		if(testFlush==true || testStrit==true)
		{
			vector<int> res;
			for(int i=0; i<5;i++)
			{
				res[i]=i;
			}
			return res;
		}	
		
		//ƒќƒ≈Ћј“№!
		//for()
		//if(massiv[0][1]>1)
		//{
		//	vector<int> res;
		//	for(int i=0; i<5;i++)
		//	{
		//		res[i]=i;
		//	}
		//	return res;
		//}

	}

};