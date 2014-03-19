// SourceMain.cpp : Console application entry point

#include "stdafx.h"
#include "headers.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Initialize();
	//ControlDock();
	
	int Available_List[54];
	int times=1;
	memset(Available_List,AVAILABLE,sizeof(Available_List));
	
	Cards card;
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

