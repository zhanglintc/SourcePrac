// SourceMain.cpp : Console application entry point

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
//////////////////////////////////////////////

int main(int argc, char *argv[])
{
    Initialize();
	ControlDock();
    //ShellExecute(NULL, _T("open"), _T("explorer.exe"), _T("http://www.baidu.com"), NULL, SW_SHOW);

    //SocketCaller();
/********************************************************************************************/
/********************************************************************************************/
/****************************  Below is the end mark  ***************************************/
/********************************************************************************************/
/********************************************************************************************/
#ifdef WIN32
    setTextColor(TEAL);
#endif //WIN32
    printf("\n\n\n");
    printf("********Test over*********\n");
    printf("Press any key to exit...\n");
    printf("**************************\n");
    getchar();
    return 0;
}

