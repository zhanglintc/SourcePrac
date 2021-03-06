﻿#ifndef _HEADERS_H_
#define _HEADERS_H_

/*******************************************************************************/
//includes
/*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdarg.h>
#include <iostream>
#include <vector>
#include <map>

#ifdef WIN32
#include <tchar.h>
#include <winsock2.h>
#include <windows.h>
#pragma comment (lib, "ws2_32")         //socket库文件
#endif

using namespace std;

/*******************************************************************************/
//defines
/*******************************************************************************/
#define MIN_WORD_LENGTH         0       //minimum length of required word
#define INPUT_STRING_LEN        300     //input length
#define COMMAND_STR_LEN         100     //command length
#define NO_RESTRICT_LENGTH      0       //word's length no limitation
#define NO_RESTRICT_KEYWORD     0       //keyword no limitation
#define ERROR_MARK              -1      //means something wrong
#define NON_AVAILABLE           1       //not available
#define AVAILABLE               0       //available
#define JOKER                   true    //with jokers
#define NOJOKER                 false   //with out jokers

//defines for ThreeCardBrag -S
#define Spade                   0
#define Heart                   1
#define Club                    2
#define Diamond                 3
#define Black_Joker             52      //card uni_number from 0 to 53, thus Black_Joker is 52
#define Red_Joker               53      //card uni_number from 0 to 53, thus Black_Joker is 53

#define Ace                     1
#define Jack                    11
#define Queen                   12
#define King                    13

#define Trips                   1
#define Straight_Flush          2
#define Flush                   3
#define Straight                4
#define Pairs                   5
#define High                    6
//defines for ThreeCardBrag -E

#define ui_8                    unsigned char
#define si_8                    signed char
#define ui_16                   unsigned int
#define si_16                   signed int
#define uchar                   unsigned char
#define uint                    unsigned int
#define byte                    unsigned char

/*******************************************************************************/
//typedefs
/*******************************************************************************/
//-------------------------------------------------------------------------------------
typedef struct Cards
{
    int  uni_num;               // 0-53 for All
                                // 0-12 for Spade
                                //13-25 for Heart
                                //26-38 for Club
                                //39-51 for Diamond
                                //53    for Black_joker
                                //54    for Red_Joker
    
    int  suit_int;              //int for Spade, Heart, Club, Diamond, Black_joker, Red_Joker
    char suit_str[10];          //string for Spade, Heart, Club, Diamond, Black_joker, Red_Joker
    int  point_int;             //int for Ace,2,3,4,5,6,7,8,9,10,Jack,Queen,King
    char point_str[10];         //stringfor Ace,2,3,4,5,6,7,8,9,10,Jack,Queen,King
}Cards;
//-------------------------------------------------------------------------------------
typedef struct K_MSG
{
    byte abData[64];
}K_MSG;
//-------------------------------------------------------------------------------------
typedef struct TEST
{
    byte test1_1:4;
    byte test1_2:4;
    byte test2;
    byte test_next[1];
}TEST;
//-------------------------------------------------------------------------------------
typedef enum _PCCOLOR
{
    BLACK        = 0,
    BLUE         = 1,
    DARK_GREEN   = 2,
    LIGHT_BLUE   = 3,
    RED          = 4,
    PURPLE       = 5,
    ORANGE       = 6,
    GREY         = 7,
    DARKER_GREY  = 8,
    MEDIUM_BLUE  = 9,
    LIGHT_GREEN  = 10,
    TEAL         = 11,
    RED_ORANGE   = 12,
    LIGHT_PURPLE = 13,
    YELLOW       = 14,
    WHITE        = 15
}PCCOLOR;
//-------------------------------------------------------------------------------------

/*******************************************************************************/
//externs
/*******************************************************************************/
extern char *lexicon90k_1[];                //declared in lex_1.cpp
extern char *lexicon90k_2[];                //declared in lex_2.cpp
extern char *lexicon90k_3[];                //declared in lex_3.cpp


/*******************************************************************************/
//sturctures
/*******************************************************************************/
//-------------------------------------------------------------------------------------
struct date
{
    int year;
    int month;
    int day;
};
//-------------------------------------------------------------------------------------
struct stu
{
    int num;
    char name[20];
    char sex;
    int age;
    date birh;
};
//-------------------------------------------------------------------------------------
struct packed_data
{
    char a;
};
//-------------------------------------------------------------------------------------
struct MAN
{
    int num;
    MAN *next;
};
//-------------------------------------------------------------------------------------
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
//-------------------------------------------------------------------------------------


/*******************************************************************************/
//functions
/*******************************************************************************/

//temporary
#ifdef WIN32
void SocketServer();
void SocketClient();
void GetLocalIP();
#endif //WIN32
char *StrConcatenate(char *head, ...);
char *Int2Str(int data);
ListNode *insertionSortList(ListNode *head);

//void
void CalcDate(int ,int ,int );
void DateCalcMain();
void Sort_Str(char *data[10]);
void Sort_Int(int data[],int length);
void Sort_Int(char data[],int length);
void CalcDateinterface(date date);
void Arrangement(char data[],int lenth,char type);
void Arrangement(int data[],int lenth,char type);
void Exchange(char *a,char *b);
void Exchange(int *a,int *b);
void LastOne(int ,int );
void Iterater();
void perfect();
void ball();
void do_it(char *str);
void TGA0117();
void LANE0117();
void LANE0117_1();
void LANE0124();
void getbits(int value,char n1,char n2);
void monthshow(char i);
void wooords(char *letters, int length, char keyword);
void CheckLexicon(char *data,int st,int end);
void swap(char *a, char *b);
void swap(int *a, int *b);
void filesth();
void ControlDock(void);
void help(void);
void GetCommand(char command[300], char para_1st[300], char para_2nd[300]);
void Callwooords(void);
void Big_Little_Endian_Judge();
void recursion();
void AB_Game();
void Initialize();
void DealThreeCards(Cards *card_1st, Cards *card_2nd, Cards *card_3rd);
void CallLastOne();
void CardUni2Int(Cards *card);
void CardInt2StrConvertor(Cards *card);
void UncertainParaTestFun(int a, ...);
void minprintf(char *fmt, ...);
void TwentyOnePointGame();
void LANE20140414();
#ifdef WIN32
void color_20140512();
void SocketCaller();
#endif //WIN32

//int
int GetLength(char []);
int Str2Int(char []);
int Str2Int(char *,int );
int Str2Int(char *,int );
int Factorial(int data);
int randnum(int min,int max);
int roll(char *, char *);
int CountArrayLength(intptr_t arr[]);
int CountArrayLength(Cards *cards);
int ThreeCardBrag(Cards *card_1st, Cards *card_2nd, Cards *card_3rd, char type);
#ifdef WIN32
int setTextColor(unsigned char fColor);
int setBackColor(unsigned char bColor);
#endif //WIN32

//float
float TwentyOnePointCalculator(Cards cards[]);
float TwentyOnePointConvertor(Cards card);
float TwentyOnePointOverflowProbability(Cards cards[], int Available_List[]);

//bool
bool CheckData(char [],char [],int ,int ,int);
bool AB_GameInputCheck(char data[]);
bool Equal(char command_in[], char command_require[]);
bool isTrips(Cards *card_1st, Cards *card_2nd, Cards *card_3rd);
bool isStraightFlush(Cards *card_1st, Cards *card_2nd, Cards *card_3rd);
bool isFlush(Cards *card_1st, Cards *card_2nd, Cards *card_3rd);
bool isStraight(Cards *card_1st, Cards *card_2nd, Cards *card_3rd);
bool isPairs(Cards *card_1st, Cards *card_2nd, Cards *card_3rd);
bool TwentyOnePointAI(Cards cards[], int Available_List[]);

//others
Cards CardGenerator(int Available_List[54], bool with_joker);

/*******************************************************************************/
/*******************************************************************************/

#endif /* _HEADERS_H_ */
