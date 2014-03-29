﻿// SourceMain.cpp : Console application entry point

#include "stdafx.h"
#include "headers.h"

#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

//#define printf(fmt, args...) myprintf(fmt, ##args)
//#define DEBUG_PRINT(x,...) wprintf(x,__VA_ARGS__)
//#define LOG(format, ...) printf(format,__VA_ARGS__)
//#define DEBUG_PRINT#(
#define DEBUG_PRINT minprintf

//2014.03.20 ZhangLin -S
//ADVANCED LEARNER'S English-Chinese Dictionary
//roll 2056 resulted 1830
//roll   16 resulted 5
//-----theodolite-----
//2014.03.20 ZhangLin -E

char str0[][5]={{"abcd"},{"cde"}};
wchar_t str1[]={L"桃111111111"};
char str2[]={0x68,0x43,0};
char str3[]={0x43,0x68,0};

int _tmain(int argc, _TCHAR* argv[])
{
	_tsetlocale(LC_ALL, L"CHS");
	//setlocale(LC_ALL,"CHS");
	//printf(("%d",str0));
	//DEBUG_PRINT(("%s\n",str1));
	//minprintf("%s",str1);
	DEBUG_PRINT("%s",str1);
	
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

