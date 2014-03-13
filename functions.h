/*******************************************************************************/
//includes
/*******************************************************************************/
#include "stdafx.h"
#include "stdio.h"
#include "math.h"
#include "time.h"
#include "limits.h"

/*******************************************************************************/
//defines
/*******************************************************************************/
#define MIN_WORD_LENGTH		0
#define INPUT_STRING_LEN	300
#define COMMAND_STR_LEN		100

#define ui_8	unsigned char
#define si_8	signed char
#define ui_16	unsigned int
#define si_16	signed int
#define uchar	unsigned char
#define uint	unsigned int
#define byte	unsigned char


/*******************************************************************************/
//typedefs
/*******************************************************************************/




/*******************************************************************************/
//externs
/*******************************************************************************/
extern char *lexicon8k[];					//declared in lexicon.dat, included in functions.cpp
extern char *lexicon36k[];					//declared in lexicon.dat, included in functions.cpp
extern char *lexicon90k_1[];				//declared in lex_1.cpp
extern char *lexicon90k_2[];				//declared in lex_2.cpp
extern char *lexicon90k_3[];				//declared in lex_3.cpp

/*******************************************************************************/
//sturctures
/*******************************************************************************/
typedef struct Man
{
	int num;
	Man *next;
}MAN;
typedef struct
{
	int color;
	int isDisplay;
}MAIN_GRID;
struct date
{
	int year;
	int month;
	int day;
};
struct stu
{
	int num;
	char name[20];
	char sex;
	int age;
	date birh;
};
struct packed_data
{
	char a;
};

typedef struct K_MSG
{
	byte abData[64];
}K_MSG;

typedef struct TEST
{
	byte test1_1:4;
	byte test1_2:4;
	byte test2;
	byte test_next[1];
}TEST;

/*******************************************************************************/
//functions
/*******************************************************************************/
int GetLength(char []);
bool CheckData(char [],char [],int ,int ,int);
int String2Int(char []);
int String2Int(char *,int );
void CalcDate(int ,int ,int );
void DateCalcMain();
void Sort(char *data[10]);
void CalcDateinterface(date date);
void Sort(char data[],int lenth,char type);
void Sort(int data[],int lenth,char type);
void Exchange(char *a,char *b);
void Exchange(int *a,int *b);
int Factorial(int data);
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
int randnum(int min,int max);
int roll(char *para);
void monthshow(char i);
int CountArrayLength(int arr[]);
void wooords(char *letters, int length, char keyword);
void CheckLexicon(char *data,int st,int end);
void swap(char *a, char *b);
void filesth();
void ControlDock(void);
void help(void);
void GetCommand(char command[300], char para_1st[300], char para_2nd[300]);
void __stdcall Callwooords(void);
void Big_Little_Endian_Judge();
void DataGen();
bool CheckColor(int );
void doudouGenMain();
void doudouInit();
void douClick(int row, int line);
int upSe(int *row,int *line);
int rightSe(int *row,int *line);
int downSe(int *row,int *line);
int leftSe(int *row,int *line);
void douProcess(int rowIn,int lineIn);
void recursion();
void AB_Game();
bool AB_GameInputCheck(char data[]);

/*******************************************************************************/
/*******************************************************************************/