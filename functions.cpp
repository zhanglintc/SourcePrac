#include "stdafx.h"
#include "functions.h"


//#include "lexicon.dat"
extern void DaDouDou();

/*******************************************************
機能:
A game. Generate a 4 length number, then player guess.
If number and place match, A++. Only number match, B++.
8 chances.
引数:なし
戻る値:なし
*******************************************************/
void AB_Game()
{
	char input[100];
	int Guess;
	int A=0,B=0;
	int R1,R2,R3,R4;					//Rand  1,2,3,4
	int G1,G2,G3,G4;					//Guess 1,2,3,4

	R1=R2=R3=R4=randnum(0,9);			//generate numbers 

	while(R2==R1)						//to make sure there is no repetition ↓
	{
		R2=randnum(0,9);
	}
	while(R3==R1||R3==R2)
	{
		R3=randnum(0,9);
	}
	while(R4==R1||R4==R2||R4==R3)
	{
		R4=randnum(0,9);
	}									//to make sure there is no repetition ↑

	//printf("%d,%d,%d,%d\n",R1,R2,R3,R4);
	
	//Game start:
	for(int i=1;i<=8;i++)				//1→8, 8 chances
	{
		if(i<8)							//normal process
		{
			printf("Round %d:\n",i);
		}
		else							//last try, remind player
		{
			printf("Round %d:(last chance)\n",i);
		}
		
		gets(input);							//get the input
		while(!AB_GameInputCheck(input))		//check the input is valid or not
		{
			printf("Invalid input\n");
			gets(input);
		}
		
		Guess=String2Int(input);				//string to int
		//printf("%d\n",Guess);
		G1=Guess/1000%10;
		G2=Guess/100%10;
		G3=Guess/10%10;
		G4=Guess/1%10;

		//printf("%d,%d,%d,%d\n",G1,G2,G3,G4);

		if(G1==R1)A+=1;									//count A
		if(G2==R2)A+=1;
		if(G3==R3)A+=1;
		if(G4==R4)A+=1;
		if((G1==R2)||(G1==R3)||(G1==R4))B+=1;			//count B
		if((G2==R3)||(G2==R4)||(G2==R1))B+=1;
		if((G3==R4)||(G3==R1)||(G3==R2))B+=1;
		if((G4==R1)||(G4==R2)||(G4==R3))B+=1;
		
		printf("%dA,%dB\n",A,B);						//display the result
		
		if(A==4)										//everything is right, win
		{
			printf("Bingo!!!\n");break;
		}
		
		if(i==8)										//sorry, game over
		{
			printf("Game Over!!!\n");
		}
		
		
		A=B=0;
	}
	
	printf("Number is:%d\n",R1*1000+R2*100+R3*10+R4);	//show the right number(no matter player guess it or not)
}


/*******************************************************
機能:check the ABgame input number is valid or not
引数:char data[100]
戻る値:true:	valid
	   false:	not valid
*******************************************************/
bool AB_GameInputCheck(char data[100])
{
	//data -- -- -- --
	//     N1 N2 N3 N4
	//******************
	int check;
	int N1,N2,N3,N4;
	for(int i=0;i<GetLength(data);i++)
	{
		if(data[i]<48||data[i]>57)return false;					//contain letters, return false
	}
	check=String2Int(data);										//string to int
	
	N1=check/1000%10;
	N2=check/100%10;
	N3=check/10%10;
	N4=check/1%10;
	
	if(N1==0)													//if kilobit is 0, only check N2,N3,N4
	{
		check/=100;
		if((check<=0)||(check>9))return false;
		if((N1==N2)||(N1==N3)||(N1==N4))return false;
		if((N2==N3)||(N2==N4))return false;
		if((N3==N4))return false;
	}
	else
	{
		check/=1000;											//else check whole number, N1,N2,N3,N4
		if((check<=0)||(check>9))return false;
		if((N1==N2)||(N1==N3)||(N1==N4))return false;
		if((N2==N3)||(N2==N4))return false;
		if((N3==N4))return false;
	}
	return true;												//everything is OK, return true
}

void recursion()
{
	static int i=0;
	i+=1;
	if(i!=100)recursion();
	printf("%d\n",i);
}

void Big_Little_Endian_Judge()
{
	K_MSG MSG;
	int a=0x12346578;
	memcpy(MSG.abData,MSG.abData,sizeof(MSG.abData));
	TEST *p,*p1,*p2;
	p=(TEST *)MSG.abData;
	p->test1_1=1;
	p->test2=2;
	p1=(TEST *)p->test_next;
	p1->test1_2=3;
	p1->test2=4;
	p2=(TEST *)&MSG.abData[63];
	//p2->test1=5;
	MSG.abData[0]=0xab;

	uchar *pp=(uchar *)&a;
	if(0x78==*pp)
	{
		printf("little endian\n");
	}
	else
	{
		printf("big endian\n");
	}
	;
	;
	;
}

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void _stdcall Callwooords(void)
{
	char	word[30];															//store the input letters
	int		length=0;															//store the required length
	char	keyword=0;															//store the required letter

	char command[COMMAND_STR_LEN],para_1st[COMMAND_STR_LEN],para_2nd[COMMAND_STR_LEN];

	memset(command,'\0',sizeof(command));											//initialize command
	memset(para_1st,'\0',sizeof(para_1st));											//initialize parameter 1st
	memset(para_2nd,'\0',sizeof(para_2nd));											//initialize parameter 2nd
	memset(word,'\0',sizeof(word));

	while(true)
	{
		printf("\nControlDock\\Wooords>(word,length,key)");							//welcome words
		GetCommand(command,para_1st,para_2nd);										//get main command and parameters

		if(strcmp(command,"-exit")==0||strcmp(command,"exit")==0)					//exit
		{
			break;
		}
		else if(strcmp(command,"")==0)												//invalid input
		{
			printf("Invalid input\n\n");
		}
		else if(strcmp(command,"-show")==0)											//show last input
		{
			if(word[0]==0)
			{
				puts("NULL\n");														//no last input
			}
			else
			{
				printf("%s\n",word);												//show
			}
		}
		else if(strcmp(command,"-last")==0)											//use the last input
		{
			printf("please input length:");											//get the length
			scanf("%d",&length);
			getchar();

			printf("please input keyword:");										//get the keyword
			scanf("%c",&keyword);
			getchar();

			wooords(word,length,keyword);											//call wooords
		}
		else if(strcmp(command,"ok")==0)											//start wooords. annulment
		{
			printf("please input letters:");
			scanf("%s",&word);
			getchar();

			printf("please input length:");
			scanf("%d",&length);
			getchar();

			printf("please input keyword:");
			scanf("%c",&keyword);
			getchar();

			wooords(word,length,keyword);
			getchar();

		}
		else if(strcmp(command,"cls")==0||strcmp(command,"-cls")==0)				//clean screen
		{
			system("cls");
		}
		else																		//defalut mode. first command is the input
																					//para_1 is length
																					//para_2 is keyword
		{
			memcpy(word,command,sizeof(word));										//copy command to word
			length=String2Int(para_1st);											//copy para1 to length
			keyword=para_2nd[0];													//copy para2 to keyword

			if(String2Int(para_1st)==-1)											//when error, result of String2Int is -1
			{
				length=0;															//when error, length = 0
			}
			if(para_2nd[0]=='\0')													//covert '\0' to '0'
			{
				keyword='0';
			}

			wooords(word,length,keyword);											//call wooords
		}
	}	
}

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void ControlDock(void)
{
	char command[COMMAND_STR_LEN],para_1st[COMMAND_STR_LEN],para_2nd[COMMAND_STR_LEN];
	while(true)
	{
		printf("\nControlDock>");
		GetCommand(command,para_1st,para_2nd);

		if(strcmp(command,"-exit")==0||strcmp(command,"exit")==0)
		{
			break;
		}
		else if(strcmp(command,"cls")==0||strcmp(command,"-cls")==0)
		{
			system("cls");
		}
		else if(strcmp(command,"")==0)
		{
			printf("Invalid input\n\n");
		}
		else if(strcmp(command,"-help")==0||strcmp(command,"-?")==0||strcmp(command,"/?")==0)
		{
			help();
		}
		else if(strcmp(command,"-roll")==0)
		{
			roll(para_1st);
		}
		else if(strcmp(command,"-word")==0||strcmp(command,"word")==0)
		{
			Callwooords();
		}
		else if(strcmp(command,"abgame")==0)
		{
			AB_Game();
		}
		else if(strcmp(command,"doudou")==0)
		{
			doudouGenMain();
			DaDouDou();
		}
		else
		{
			printf("Unknown command\n\n");
		}
	}
}

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void help(void)
{
	puts("-exit	exit");
	puts("-help -? /?");
	puts("-roll xxx");
	puts("-word word\n");
}


/******************************************************/
bool findchar(char* string,char temp)
{
	int index=0;
	while(*string!='\0' &&*string++ !=temp  )index++;
	return index>GetLength(string)? false :true;
}
/******************************************************/

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void wooords(char *letters, int length, char keyword)
{
	//無効になる 2014.03.12 張麟 ↓
	//int _8kLength=CountArrayLength((int *)lexicon8k);//-CountArrayLength((int *)lexicon8k);		//calculate 8k length
	//int _36kLength=CountArrayLength((int *)lexicon36k);											//calculate 36k length
	//無効になる 2014.03.12 張麟 ↑

	/*
	when error, try to use 8k-36k to calculat length of 8k. 
	because sometimes length of 8k is wrongly caculated from 
	the very start to the very end. that means contain 8k and 36k=43k.
	the real length of 8k is about 8k.		--2013/5/13
	the real length of 36k is about 36k.	--2013/5/13
	*/
	int _90kLength_1=CountArrayLength((int *)lexicon90k_1);										//calculate 90k part 1
	int _90kLength_2=CountArrayLength((int *)lexicon90k_2);										//calculate 90k part 2
	int _90kLength_3=CountArrayLength((int *)lexicon90k_3);										//calculate 90k part 3
	
	int i=0,j=0,k=0;							//initialize i k j. 
												//i for lexicon length circle.
												//j for word length.
												//k for alphabeta length circle.

	int cnt_in[150];							//store the input alphabeta num. PS:150 is little more than ascll length
	int cnt_lex[150];							//store the lexicon alphabeta num. PS:150 is little more than ascll length
	int countWordExist=0;						//store the word num

	memset(cnt_in,0,sizeof(cnt_in));												//cnt_in initial
	memset(cnt_lex,0,sizeof(cnt_lex));												//cnt_lex intial	

	printf("The results are showing below\n\n");

	/*  count given word letters ↓  */
	for(j=0;j<GetLength(letters);j++)												//from first letter to last letter｢ﾙ. word
	{
		for(k='a';k<='z';k++)														//from a to z｢ﾚ. alphabeta
		{
			if(letters[j]==k)														//if contain this letter, 
			{
				cnt_in[k]++;														//alphabeta number++｢ﾛ
				break;
			}
		}
	}
	/*  count given word letters ↑  */

	/************************************************************************************************/
	/************************************************************************************************/
	//count lexicon words letters, the 1st ↓
	for(i=0;i<_90kLength_1;i++)														//for all of the lexiconXXk
	{
		if(length==0||length==GetLength(lexicon90k_1[i]))							//word length equals inquired length
		{
			for(j=0;j<GetLength(lexicon90k_1[i]);j++)								//from first letter to last letter｢ﾙ
			{
				for(k=0;k<='z';k++)													//from a to z｢ﾚ
				{					
					if(lexicon90k_1[i][j]==k)										//if contain this letter, alphabeta number++｢ﾛ
					{
						cnt_lex[k]++;
						break;
					}//end of if
				}//end of for,end of contain letter count
			}//end of word loop
			//determine to show this word or not｡
			for(k=0;k<='z';k++)
			{
				if(cnt_in[k]<cnt_lex[k])break;										//input lettters less than required letters, berak
				if(k=='z')															//to the end
				{
					if(*lexicon90k_1[i]>='A'&&*lexicon90k_1[i]<='Z')break;			//contain uppercase, break
					if(cnt_lex[keyword]==0&&keyword!='0')break;						//do not contain keyword, break
					if(GetLength(lexicon90k_1[i])<MIN_WORD_LENGTH)break;			//word length not enough, break

					if(countWordExist>=100&&countWordExist%100==0)getchar();		//split to small pages
					printf("%3d.%s\n",countWordExist+1,lexicon90k_1[i]);			//print the word
					countWordExist++;												//count num ++
				}
			}
			memset(cnt_lex,0,sizeof(cnt_lex));
		}//end of lexicon loop
	}
	//count lexicon words letters, the 1st ↑

	/************************************************************************************************/
	/************************************************************************************************/

	//count lexicon words letters, the 2nd ↓
	for(i=0;i<_90kLength_2;i++)//for all of the lexicon36k
	{
		if(length==0||length==GetLength(lexicon90k_2[i]))							//word length equals inquired length
		{
			for(j=0;j<GetLength(lexicon90k_2[i]);j++)								//from first letter to last letter｢ﾙ
			{
				for(k=0;k<='z';k++)													//from a to z｢ﾚ
				{					
					if(lexicon90k_2[i][j]==k)										//if contain this letter, alphabeta number++｢ﾛ
					{
						cnt_lex[k]++;
						break;
					}//end of if
				}//end of for,end of contain letter count
			}//end of word loop
			//determine to show this word or not｡
			for(k=0;k<='z';k++)
			{
				if(cnt_in[k]<cnt_lex[k])break;//not enough
				if(k=='z')
				{
					if(*lexicon90k_2[i]>='A'&&*lexicon90k_2[i]<='Z')break;
					if(cnt_lex[keyword]==0&&keyword!='0')break;
					if(GetLength(lexicon90k_2[i])<MIN_WORD_LENGTH)break;

					if(countWordExist>=100&&countWordExist%100==0)getchar();
					printf("%3d.%s\n",countWordExist+1,lexicon90k_2[i]);
					countWordExist++;
				}
			}
			memset(cnt_lex,0,sizeof(cnt_lex));
		}//end of lexicon loop
	}
	//count lexicon words letters, the 2st ↑

	/************************************************************************************************/
	/************************************************************************************************/

	//count lexicon words letters, the 3rd ↓
	for(i=0;i<_90kLength_3;i++)//for all of the lexicon36k
	{
		if(length==0||length==GetLength(lexicon90k_3[i]))							//word length equals inquired length
		{
			for(j=0;j<GetLength(lexicon90k_3[i]);j++)								//from first letter to last letter｢ﾙ
			{
				for(k=0;k<='z';k++)													//from a to z｢ﾚ
				{					
					if(lexicon90k_3[i][j]==k)										//if contain this letter, alphabeta number++｢ﾛ
					{
						cnt_lex[k]++;
						break;
					}//end of if
				}//end of for,end of contain letter count
			}//end of word loop
			//determine to show this word or not｡
			for(k=0;k<='z';k++)
			{
				if(cnt_in[k]<cnt_lex[k])break;//not enough
				if(k=='z')
				{
					if(*lexicon90k_3[i]>='A'&&*lexicon90k_3[i]<='Z')break;
					if(cnt_lex[keyword]==0&&keyword!='0')break;
					if(GetLength(lexicon90k_3[i])<MIN_WORD_LENGTH)break;

					if(countWordExist>=100&&countWordExist%100==0)getchar();
					printf("%3d.%s\n",countWordExist+1,lexicon90k_3[i]);
					countWordExist++;
				}
			}
			memset(cnt_lex,0,sizeof(cnt_lex));
		}//end of lexicon loop
	}
	//count lexicon words letters, the 3st ↑

	/************************************************************************************************/
	/************************************************************************************************/

	if(countWordExist==0)
	{
		printf("Sorry, no fit words\n");
	}
	else
	{
		printf("\nGreat, %d words are found\n",countWordExist);
	}
}//end of wooords

/*******************************************************
機能:なし
引数:なし
戻る値:なし
2014.03.12 張麟：
	Lexicon.datは紛失のため、この関数は無効になる
*******************************************************/
/*
void CheckLexicon(char *data,int st,int end)
{
    int i,k;
    if(st>end)
    {
        for(k=0;k<CountArrayLength((int *)&lexicon8k);k++)
		{
			if(strcmp(data,lexicon8k[k])==0)
			{
				printf("%s\n", data);
			}
		}
    }
    else
    {
        for(i=st;i<=end;i++)
        {
            swap(&data[st],&data[i]);
            CheckLexicon(data,st+1,end);
            swap(&data[st],&data[i]);
        }
    }
}
*/

/*******************************************************
機能:DotA似通う、Rollファンクション
引数:なし
戻る値:なし
*******************************************************/
int roll(char *para)
{
	int ret=0;
	int range=String2Int(para);
	if(range==0)range=100;
	srand((unsigned)time(NULL));
	ret=randnum(0,range);
	printf("Your rolled num: %d\n\n",ret);
	return ret;
}

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void LANE0124()
{
	signed char t=0;
//	int i;
	t=t-4;
	t>>=1;

	printf("%d",t);
}

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void LANE0117_1()
{
	int t1,t2=1459,*p1,*p2;
	p1=&t1;
	p2=&t2;
	memcpy(p1,p2,sizeof(t1));
	printf("t1 is:%d",t1);
}

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void LANE0117()
{
	int CH=3;
	date gasDate[4];//gasDate[y] このyと以下のyは同じ
	date asDate[1][4]=//asDate[x][y]
	{//これはデータから
		{//これはｘから
			{2013,1,17},//これはｙから
			{2014,2,18},
			{2015,3,19},
			{2016,4,20}
		}
	};
	memcpy(gasDate,asDate[0],sizeof(gasDate));
	//printf("%d",gasDate[2]);
	printf("%d/%d/%d",gasDate[CH].year,gasDate[CH].month,gasDate[CH].day);
}

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void do_it(char *str)
{
	printf("%s",str);
	while(*str!='\0')
	{
		putchar(*str);
		str++;
	}
	printf("%s",str);
}

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void Iterater()
{
	printf("\n");
	getchar();
	char var;
	printf("in\n");
	scanf("%c",&var);
	if(var=='y')Iterater();
	printf("out\n");
}

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void LastOne(int numbers,int keys)//numbersは人数、keysは報告の数
{
	int i=0;
	Man *p,*pt,*pp;//pt→p this       pp→p previous.
	//p is used for make new data.
	//pt is current data.
	//pp always cache pt.
	//data1  →   data2   →    data3(new one)
	//pp          pt             p

	//to make this circle↓
	Man *head=NULL;	//new a head←
	for(int i=1;i<=numbers;i++)
	{
		p=(Man *)malloc(sizeof(Man));
		p->num=i;
		if(head==NULL)//linked list is NULL
		{			
			head=p;
			pt=p;
		}			
		else
		{
			pt->next=p;
			pt=p;
		}
	}

	//pt=head;//find the last one
	//while(pt->num!=numbers)
	//{
	//	pt=pt->next;
	//}
	pp=pt;//キャッシュポインタ＝最後人
	pt->next=head;//to make it a circle
	pt=head;//from the start
	i=0;
	while(1)
	{
		i++;
		printf("I'm No.%-3d %-2d times\n",pt->num,(i%keys)+(i%keys==0?keys:0));//report current person's number
		if(i%keys==0)//kill this person
		{
			printf("No.%d has been killed\n",pt->num);//tell everyone this person has been killed
			pp->next=pt->next;
			//delete this data.
			//pp is cache of pt.pp->next=pt->next means jump over pt,means delete this person
			pt=pt->next;
		}
		else//not me, go ahead
		{
			pp=pt;
			pt=pt->next;
		}
		if(pt->next==pt)//only one person
			break;
	}
	printf("\nLast surviver is:\n★No.%d★\nCongradulations!!!\n",pt->num);
}





//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************

/*******************************************************
機能:天数計算-枠
引数:なし
戻る値:なし
*******************************************************/
void DateCalcMain()
{
	char StrIn[10];
	int year=0,month=0,day=0;
	printf("Please input year:");
	scanf("%s",&StrIn);
	getchar();
	while(CheckData(StrIn,"year",year,month,day)==false)
	{
		printf("Please input year:");
		scanf("%s",&StrIn);
		getchar();
	}
	year=String2Int(StrIn);
	printf("Please input month:");
	scanf("%s",&StrIn);
	getchar();
	while(CheckData(StrIn,"month",year,month,day)==false)
	{
		printf("Please input month:");
		scanf("%s",&StrIn);
		getchar();
	}
	month=String2Int(StrIn);
	printf("Please input day:");
	scanf("%s",&StrIn);
	getchar();
	while(CheckData(StrIn,"day",year,month,String2Int(StrIn))==false)
	{
		printf("Please input day:");
		scanf("%s",&StrIn);
		getchar();
	}
	day=String2Int(StrIn);
	CalcDate(year,month,day);
}
/*******************************************************
機能:閏年判断
引数:int
戻る値:bool
*******************************************************/
bool isLeapYear(int data)
{
	if(data%4==0&&data%100!=0)
	{
		//printf("leap\n");
		return true;
	}
	else if(data%400==0&&data%100==0)
	{
		//printf("leap\n");
		return true;
	}
	//printf("not leap\n");
	return false;
}

/*******************************************************
機能:入力合法性判断
引数:char[],char [],int ,int ,int
	 data[]:入力データ
	 type[]:データタイプ（年、月、日など）
	 year,month,day:時間データ
戻る値:int
*******************************************************/
//check if input is valid
bool CheckData(char data[],char type[10],int year,int month,int day)
{
	for(int i=0;i<GetLength(data);i++)//not numbers
	{
		if(data[i]<48||data[i]>57)
		{
			printf("Word is not allowed\n\n");
			return false;
		}
	}
	if(type=="year")
	{
		if (GetLength(data)>4)
		{
			printf("Data length is out of bound\n\n");
			return false;
		}
		isLeapYear(String2Int(data));
	}
	if(type=="month")
	{
		if (GetLength(data)>2)
		{
			printf("Data length is out of bound\n\n");
			return false;
		}
		if(String2Int(data)>12||String2Int(data)<1)
		{
			printf("Data is not valid\n\n");
			return false;
		}
	}
	if(type=="day")
	{
		if (GetLength(data)>2)
		{
			printf("Data length is out of bound\n\n");
			return false;
		}
		if(String2Int(data)>31||String2Int(data)<1)
		{
			printf("Data is not valid\n\n");
			return false;
		}
		if(isLeapYear(year)==true&&month==2&&day>29)
		{
			printf("Data is not valid\n\n");
			return false;
		}
		else if(isLeapYear(year)==false&&month==2&&day>28)
		{
			printf("Data is not valid\n\n");
			return false;
		}
		if((month==4||month==6||month==9||month==11)&&day>30)
		{
			printf("Data is not valid\n\n");
			return false;
		}
	}
	return true;
}

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void CalcDateinterface(date date)
{
	CalcDate(date.year,date.month,date.day);
}

/*******************************************************
機能:天計算-丸
引数:int ,int ,int 
戻る値:void
*******************************************************/
void CalcDate(int year,int month,int day)
{
	int ret=0;
	switch(month)
	{
		case 1:ret+=day;break;
		case 2:ret=31+day;break;
		case 3:ret=31+28+day;break;
		case 4:ret=31+28+31+day;break;
		case 5:ret=31+28+31+30+day;break;
		case 6:ret=31+28+31+30+31+day;break;
		case 7:ret=31+28+31+30+31+30+day;break;
		case 8:ret=31+28+31+30+31+30+31+day;break;
		case 10:ret=31+28+31+30+31+30+31+31+30+day;break;
		case 11:ret=31+28+31+30+31+30+31+31+30+31+day;break;
		case 12:ret=31+28+31+30+31+30+31+31+30+31+30+day;break;
	}
	if(month>=2&&isLeapYear(year)==true)ret+=1;
	printf("It is the %d days of this year\n",ret);
}
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
void monthshow(char i)
{
	char **p;
	char *s[]={"January","February","March"};
	p=s;
	//printf("%d\n%d\n%c\n",s,*s,**s);
	//printf("%d\n",**p);
	//for(int i=0;i<3;i++)
	{
		printf("%s\n",*(p+i-1));
	}
}

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void ball()
{
	register long double height=10000;
	long double last=0;
	long double distance=0;
	int i=0;
	for(i=1;i<=10;i++)
	{
		height/=2;
		printf("%d is: %10gm\n",i,height);
		distance+=2*height;
	}
	distance+=height;
	printf("distance is: %gm\n",distance);
}

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void perfect()
{
	int num,fac,sum=0;
	for(num=1;num<=1000;num++)
	{
		for(fac=1;fac<num;fac++)
		{
			if(num%fac==0)
			{
				sum+=fac;
			}
		}
		if(sum==num)
		{
			printf("factor of %d is:",sum);
			for(fac=1;fac<num;fac++)
			{
				if(num%fac==0)
				{
					printf(" %d",fac);
				}
			}
			printf("\n");
		}
		sum=0;
	}
}

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void sayhello()
{
	printf("hello\n");
	getchar();
}

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void ptrsth()
{
	int (*p)[4];
	int score[][4]={{60,70,80,90},{56,89,67,88},{37,78,90,66}};
	p=score;
	printf("%d\n",sizeof(p[4]));
//	printf("%d\n",p);
//	printf("%d\n",p+1);
	getchar();
}

/*******************************************************
機能:なし
引数:なし
戻る値:なし
*******************************************************/
void filesth()
{
	FILE *fp;
	uchar ch;
	if((fp=fopen("test_input_file.txt","rb"))==NULL)
	{
		printf("error\n");
	}
	else
	{
		printf("OK\n");
	}
	//fputs(ch,fp);
	//fprintf(fp,"\n");
	ch=fgetc(fp);
	while(1)
	{
		printf("%x %d\n",ch,sizeof(ch));
		ch=fgetc(fp);
		getchar();
	}
	fclose(fp);
	getchar();
}

/*******************************************************
機能:sort an array whose elements no more than 10. 
elements of this array are strings.
order of sorted array is:
value less in ascll, rank former.
front value the same, the longer, the latter.
引数:char * [10]	 
戻る値:なし
*******************************************************/
//function failed
void Sort(char *data[10])
{
	char **p=NULL,*tmp=NULL;							//p point data. tmp point to data[X]. **tmp can do the same thing
	int i=0,j=0,k=0;									//i for 1st num. j for 2nd num. k for letters
	int length=0;										//length of letter

	p=data;												//initialize p

	for(i=0;i<10;i++)									//find the longest length of array
	{
		if(length<GetLength(*p))
			length=/*length<*/GetLength(*p);
	}
	for(i=0;i<CountArrayLength((int *)data);i++)		//from start to end circle
	{
		for(j=i+1;j<CountArrayLength((int *)data);j++)	//from i+1 to end
		{
			for(k=0;k<length;k++)						//go through string
			{
				if(*(*(p+i)+k)>*(*(p+j)+k))				//data[i]>data[j], swap the two strings
				{
					tmp=*(p+i);
					*(p+i)=*(p+j);
					*(p+j)=tmp;
					break;
				}
				else if(*(*(p+i)+k)<*(*(p+j)+k))		//break this string
					break;
				else if(*(*(p+i)+k)==*(*(p+j)+k))		//jump over this letter
					continue;
			}
		}
	}
}

/*******************************************************
機能:輸出全部配列組み合わせ
引数:char data：配列
	 int length：配列有効位数
	 char type
戻る値:なし
*******************************************************/
void Sort(char data[],int length,char type)
{
    int i=0,j=0,k=0,z=0;
    for(i=Factorial(length);i>0;i--)					//全部の可能性個数
    {
		Exchange(&data[j],&data[j+1]);					//前後交換
        j++;	if(j==length-1)j=0;						//reach the end, go back to start        
		for(k=0;k<length;k++)							//print the answers
        {
			if(k==0)									//if it's the first num of each roll
            {
                z++;
                printf("\nNo.%-3d: ",z);				//then print the No.
            }
			switch(type)								//print the data by different parameters
			{
				case 'd':
					printf("%d ",data[k]);break;
				case 'c':
					printf("%c ",data[k]);break;
				default:
					break;
			}			
        }
    }
}

/*******************************************************
機能:輸出全部配列組み合わせ
引数:int data：配列
	 int length：配列有効位数
	 char type
戻る値:なし
*******************************************************/
void Sort(int data[],int length,char type)
{
    int i=0,j=0,k=0,z=0;
    for(i=Factorial(length);i>0;i--)					//全部の可能性個数
    {
		Exchange(&data[j],&data[j+1]);					//前後交換,from start to end
        j++;	if(j==length-1)j=0;						//reach the end, go back to start
		for(k=0;k<length;k++)							//print the answers
        {
			if(k==0)									//if it's the first num of each roll
            {
                z++;
                printf("\nNo.%-3d: ",z);				//then print the No.
            }
			switch(type)								//print the data by different parameters
			{
				case 'd':
					printf("%d ",data[k]);break;
				case 'c':
					printf("%c ",data[k]);break;
				default:
					break;
			}			
        }
    }
}