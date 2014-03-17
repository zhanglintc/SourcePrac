// SourceMain.cpp : Console application entry point

#include "stdafx.h"
#include "headers.h"

#define TIMES 110000

extern void DaDouDou();

int _tmain(int argc, _TCHAR* argv[])
{
	int times=0;
	int i=0;
	int seq_1[TIMES];
	int seq_2[TIMES];
	int sum1=0;
	int sum2=0;
	int trips=0;
	int flush_straight=0;
	
	Initialize();
	//ControlDock();
	Cards card_1st;
	Cards card_2nd;
	Cards card_3rd;
	
	//for(i=0;i<TIMES;i++)
	//{
	//	DealCards(&card_1st, &card_2nd, &card_3rd);
	//	if(isTrips(&card_1st, &card_2nd, &card_3rd)==true)trips++;
	//	if(isFlush(&card_1st, &card_2nd, &card_3rd)==true && isStraight(&card_1st, &card_2nd, &card_3rd)==true)flush_straight++;
	//}
	//printf("%d times contains %d times trips\n",TIMES,trips);
	//printf("%d times contains %d times flush_straight\n",TIMES,flush_straight);
	
	/*
	for(i=0;i<TIMES;i++)
	{
		seq_1[i]=ZhaJinHua(&card_1st, &card_2nd, &card_3rd, Trips);
		seq_2[i]=ZhaJinHua(&card_1st, &card_2nd, &card_3rd, Straight_Flush);
	}
	for(i=0;i<TIMES;i++)
	{
		sum1+=seq_1[i];
		sum2+=seq_2[i];
	}
	printf("Average one Trips per times:          %d\n",sum1/10);
	printf("Average one Straight_Flush per times: %d\n",sum2/10);
	*/
	

	times=ZhaJinHua(&card_1st, &card_2nd, &card_3rd, Straight_Flush);
	printf("card 1: %-8s%2s\n",card_1st.suit_str,card_1st.point_str);
	printf("card 2: %-8s%2s\n",card_2nd.suit_str,card_2nd.point_str);
	printf("card 3: %-8s%2s\n",card_3rd.suit_str,card_3rd.point_str);
	printf("times:%d",times);

	
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

