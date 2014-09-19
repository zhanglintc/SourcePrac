// SourceMain.cpp : Console application entry point

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
//Happy birthday!!! 2014.06.23 --Lane to myself
//Macbook Air!!! 2014.07.27 --Lane
//////////////////

int _tmain(int argc, _TCHAR* argv[])
{
	char ch[10];
	int lst[] = {1,1};
	ListNode *head = new ListNode(0);
	ListNode *pt = head;
	ListNode *node = NULL;

	Initialize();
	//ControlDock();
	//TwentyOnePointGame();\
	
	for(int i=0;i<2;i++)
	{
		node = new ListNode(lst[i]);
		if(head->next == NULL)
		{
			head->next = node;
		}
		else
		{
			pt->next = node;
		}
		pt = pt->next;
	}

	pt = head->next;

	insertionSortList(pt);

	gets(ch);
	if(ch[0]=='s')
	{
		SocketServer();
	}
	else if(ch[0]=='c')
	{
		SocketClient();
	}
	else;
	{
		GetLocalIP();
	}
	
/********************************************************************************************/
/********************************************************************************************/
/****************************  Below is the end mark  ***************************************/
/********************************************************************************************/
/********************************************************************************************/
	setTextColor(TEAL);
	printf("\n\n\n");
	printf("********Test over*********\n");
	printf("Press any key to exit...\n");
	printf("**************************\n");
	getchar();
	return 0;
}

