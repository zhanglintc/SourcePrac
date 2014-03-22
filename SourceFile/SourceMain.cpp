// SourceMain.cpp : Console application entry point

#include "stdafx.h"
#include "headers.h"

#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
//2014.03.20 ZhangLin -S
//ADVANCED LEARNER'S English-Chinese Dictionary
//roll 2056 resulted 1830
//roll   16 resulted 5
//-----theodolite-----
//2014.03.20 ZhangLin -E

//some modification made by lane
//some modification made by lane again
//some modification made by lane again and again
//some modification made by bernard 1st
//org from bernard
//org from lane
//last

int _tmain(int argc, _TCHAR* argv[])
{
	Initialize();
	ControlDock();

	Cards card;
	int times=0;
	int Available_List[54]; 
	memset(Available_List,AVAILABLE,sizeof(Available_List));

	FILE *f;
	f=fopen("result.txt","w");
	for(times=1;times<=54;times++)
	{		
		card=CardGenerator(Available_List, JOKER);
		//fprintf(f,"Card %2d: %-10s||%10s\n",times, card.suit_str, card.point_str);
		fprintf(f,"Card %d: \t%s\t||\t%s\n",times, card.suit_str, card.point_str);
	}
	fclose(f);
	
	/*
	Cards card_1st;
	Cards card_2nd;
	Cards card_3rd;
	
	times=ThreeCardBrag(&card_1st, &card_2nd, &card_3rd, Straight_Flush);
	printf("card 1: %-8s%2s\n",card_1st.suit_str,card_1st.point_str);
	printf("card 2: %-8s%2s\n",card_2nd.suit_str,card_2nd.point_str);
	printf("card 3: %-8s%2s\n",card_3rd.suit_str,card_3rd.point_str);
	printf("times:%d",times);
	*/
	
/********************************************************************************************/
/********************************************************************************************/
/****************************  Below is the end mark  ***************************************/
/********************************************************************************************/
/********************************************************************************************/
	printf("\n\n\n");
	printf("********Test over*********\n");
	printf("Press any key to exit...\n");
	printf("**************************\n");
	getchar();
	return 0;
}

