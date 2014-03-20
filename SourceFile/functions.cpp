#include "stdafx.h"
#include "headers.h"


/*******************************************************
Function:
	for the uncertain parameters functions study.
Argument:... *
Return	:None
*******************************************************/
void UncertainParaTestFun(int Para, ...)
{
/*
typedef char *  va_list;

#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

#define va_start(ap,v)  ( ap = (va_list)&v + _INTSIZEOF(v) )
#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (va_list)0 )
*/
	va_list Valist_P;
	va_start(Valist_P,Para);			//va_start(), make Valist_P point to the Para
	while(Para!=0)
	{
		printf("%d\n",Para);
		Para=va_arg(Valist_P,int);		//va_arg(), make Valist_P point to the one after Para, and then return the value to Para
	}
	va_end(Valist_P); /* clean up when done */
}


/*******************************************************
Function:
	Another function for the uncertain parameters functions study.
Argument:... *
Return	:None
*******************************************************/
void minprintf(char *fmt, ...)

{
/*//below is the test code
	int i = 1234;
	int j = 5678;
	char *s="nihao";
	double f=0.11f;
	fum(1,2,3,4,5,6,7);
	minprintf("the first test:i=%d\n",i,j);

	minprintf("the secend test:i=%d; %x;j=%d;\n",i,0xabcd,j);
	minprintf("the 3rd test:s=%s\n",s);
	minprintf("the 4th test:f=%f\n",f);
	minprintf("the 5th test:s=%s,f=%f\n",s,f);
//above is the test code*/

	va_list ap; /* points to each unnamed arg in turn */
	char *p, *sval;
	int ival;
	double dval;
	va_start(ap, fmt); /* make ap point to 1st unnamed arg */
	for (p = fmt; *p; p++)
	{
		if (*p != '%') 
		{
			putchar(*p);
			continue;
		}
		switch (*++p)
		{
			 case 'd':
					ival = va_arg(ap, int);
					printf("%d", ival);
					break;
			 case 'x':
					ival=va_arg(ap,int);
					printf("%#x",ival);
					break;
			 case 'f':
					dval = va_arg(ap, double);
					printf("%f", dval);
					break;
			 case 's':
					for (sval = va_arg(ap, char *); *sval; sval++)
					{
						putchar(*sval);
					}
					break;
			 default:
					putchar(*p);
					break;
		  }
   }
   va_end(ap); /* clean up when done */
}


/*******************************************************
Function:
	Convert and card's Uni_Num to card's Int and set Int to card
Argument:Cards *
Return	:None
*******************************************************/
void CardUni2Int(Cards *card)
{
	if(card->uni_num==52)		//Black_joker
	{
		card->suit_int=52;		//set both suit and point int as 52
		card->point_int=52;
	}
	else if(card->uni_num==53)	//Red_Joker
	{
		card->suit_int=53;		//set both suit and point int as 53
		card->point_int=53;
	}
	else						//0 to 51
	{
		card->suit_int=(card->uni_num)/13;						//set suit.
		
																//suit:
																//0 for Spade
																//1 for Heart
																//2 for Club
																//3 for Diamond
		
																//here the uni_number couldn't be over 51
																//if the number over 51, such as 52
																//52 / 13 = 4, or even bigger, which means nothing

		card->point_int=card->uni_num%13+1;						//set point_int, eg: 0%13=0, 0+1=1 means Ace, thus here should be added 1
	}
}


/*******************************************************
Function:
	Convert card's int to card's str.
	If this card is a Joker, then set both its suit and point
	string as Joker.
Argument:Cards *
Return	:None
*******************************************************/
void CardInt2StrConvertor(Cards *card)
{
	if		(card->suit_int==Spade)			strcpy(card->suit_str, "Spade");	//convert suit_int to suit_str
	else if	(card->suit_int==Heart)			strcpy(card->suit_str, "Heart");
	else if	(card->suit_int==Club)			strcpy(card->suit_str, "Club");
	else if	(card->suit_int==Diamond)		strcpy(card->suit_str, "Diamond");
	else if	(card->suit_int==Black_Joker)	strcpy(card->suit_str, "Blk");
	else if	(card->suit_int==Red_Joker)		strcpy(card->suit_str, "Red");

	if		(card->point_int==Ace)			strcpy(card->point_str, "A");		//convert point_int to point_str
	else if	(card->point_int==Jack)			strcpy(card->point_str, "J");
	else if	(card->point_int==Queen)		strcpy(card->point_str, "Q");
	else if	(card->point_int==King)			strcpy(card->point_str, "K");
	else if	(card->point_int==1)			strcpy(card->point_str, "1");
	else if	(card->point_int==2)			strcpy(card->point_str, "2");
	else if	(card->point_int==3)			strcpy(card->point_str, "3");
	else if	(card->point_int==4)			strcpy(card->point_str, "4");
	else if	(card->point_int==5)			strcpy(card->point_str, "5");
	else if	(card->point_int==6)			strcpy(card->point_str, "6");
	else if	(card->point_int==7)			strcpy(card->point_str, "7");
	else if	(card->point_int==8)			strcpy(card->point_str, "8");
	else if	(card->point_int==9)			strcpy(card->point_str, "9");
	else if	(card->point_int==10)			strcpy(card->point_str, "10");
	else if	(card->point_int==Black_Joker)	strcpy(card->point_str, "Blk");
	else if	(card->point_int==Red_Joker)	strcpy(card->point_str, "Red");
}


/*******************************************************
Function:
	Generate one card, this card is available or not should
	be controled by the function which has called CardGenerator(),
	gives an Available_List to CardGenerator() to tell CardGenerator
	which card can be used.
	And the caller should tell CardGenerator should generate jokers or not.
Argument:
	int Available_List[]
	bool with_joker
Return:
	Cards
*******************************************************/
Cards CardGenerator(int Available_List[54], bool with_joker)
{
	Cards card;													//new a card
	
	with_joker==true ? card.uni_num=randnum(0,53) : card.uni_num=randnum(0,51);
	//if with_joker is true, 1 to 54
	//if with_joker is false, 1 to 52
	
	while(Available_List[card.uni_num]!=AVAILABLE)				//if this card is not available, generate again
	{
		with_joker==true ? card.uni_num=randnum(0,53) : card.uni_num=randnum(0,51);
		//if with_joker is true, 1 to 54
		//if with_joker is false, 1 to 52
	}
	Available_List[card.uni_num]=NON_AVAILABLE;					//after one successful generation, set this card number unavailable
	
	
	CardUni2Int(&card);											//Convert Uni_Num to Int, and set it to card
	CardInt2StrConvertor(&card);								//set this card's string
	
	return card;												//return this new generated card
}

/*******************************************************
Function	:Call LastOne() function
Argument	:None
Return		:None
*******************************************************/
void CallLastOne()
{
	char para_1st[COMMAND_STR_LEN];
	char para_2nd[COMMAND_STR_LEN];
	char para_3rd[COMMAND_STR_LEN];//Infact, useless, just to fill up the GetCommand()'s three parameters

	memset(para_1st,'\0',sizeof(para_1st));											//initialize para_1st
	memset(para_2nd,'\0',sizeof(para_2nd));											//initialize para_2nd
	memset(para_3rd,'\0',sizeof(para_3rd));											//initialize para_3rd
	
	while(true)
	{
		printf("\nControlDock\\LastOne>(people,keys)");							//welcome words
		GetCommand(para_1st,para_2nd,para_3rd);										//get input

		if( Equal(para_1st,"-exit") || Equal(para_1st,"exit") )						//exit
		{
			break;
		}
		else if( Equal(para_1st,"") )												//invalid input
		{
			;																		//do nothing, out put another line
		}
		else if( Equal(para_1st,"cls") || Equal(para_1st,"-cls") )					//clean screen
		{
			system("cls");
		}
		else if( Str2Int(para_1st)==ERROR_MARK || Str2Int(para_2nd)==ERROR_MARK )	//invalid input
		{
			printf("Sorry, invalid input, please check and try again.\n");
		}
		else if( Str2Int(para_1st)==0 || Str2Int(para_2nd)==0 )						//invalid input(people and times cannot be 0)
		{
			printf("Sorry, invalid input, please check and try again.\n");
		}
		else
		{
			LastOne( Str2Int(para_1st),Str2Int(para_2nd) );							//call lastone
		}
	}
}


/*******************************************************
Function	:is trips judgement
Argument	:None
Return:
	ture: 	is trips
	false:	is not trips
*******************************************************/
bool isTrips(Cards *card_1st, Cards *card_2nd, Cards *card_3rd)
{
	bool is_trips=false;
	
	if(card_1st->point_int==card_2nd->point_int && card_2nd->point_int==card_3rd->point_int)
	//point: 1st == 2nd == 3rd
	{
		is_trips=true;
	}
	else
	{
		is_trips=false;
	}
	
	return is_trips;
}


/*******************************************************
Function	:is StraightFlush judgement
Argument	:None
Return:
	ture: 	is StraightFlush
	false:	is not StraightFlush
*******************************************************/
bool isStraightFlush(Cards *card_1st, Cards *card_2nd, Cards *card_3rd)
{
	bool is_StraightFlush=false;
	
	if(isFlush(card_1st, card_2nd, card_3rd)==true && isStraight(card_1st, card_2nd, card_3rd)==true)
	//             isFlush                        and                        isStraight
	{
		is_StraightFlush=true;
	}
	else
	{
		is_StraightFlush=false;
	}
	
	return is_StraightFlush;
}


/*******************************************************
Function	:is flush judgement
Argument	:None
Return:
	ture: 	is flush
	false:	is not flush
*******************************************************/
bool isFlush(Cards *card_1st, Cards *card_2nd, Cards *card_3rd)
{
	bool is_flush=false;
	
	if(card_1st->suit_int==card_2nd->suit_int && card_2nd->suit_int==card_3rd->suit_int)
	//suit: 1st == 2nd == 3rd
	{
		is_flush=true;
	}
	else
	{
		is_flush=false;
	}
	
	return is_flush;
}


/*******************************************************
Function	:is straight judgement
Argument	:None
Return:
	ture: 	is straight
	false:	is not straight
*******************************************************/
bool isStraight(Cards *card_1st, Cards *card_2nd, Cards *card_3rd)
{
	bool is_straight=false;
	int _1st=0,_2nd=0,_3rd=0;
	int seq[3];
	int i=0,j=0;
	
	seq[0]=card_1st->point_int;
	seq[1]=card_2nd->point_int;
	seq[2]=card_3rd->point_int;
	
	Sort_Int(seq,3);								//sort the three numbers, from small to large
	
	if(seq[2]-seq[1]==1 && seq[1]-seq[0]==1)		//n,n+1,n+2, can be a straight
	{
		if(seq[0]!=Ace)								//n,n+1,n+2, and n!=Ace make it real straight, because A,2,3 is not straight
		{
			is_straight=true;
		}
		else
		{
			is_straight=false;
		}
	}
	else
	{
		is_straight=false;
	}
	
	return is_straight;
}


/*******************************************************
Function	:is pairs judgement
Argument	:None
Return:
	ture: 	is pairs
	false:	is not pairs
*******************************************************/
bool isPairs(Cards *card_1st, Cards *card_2nd, Cards *card_3rd)
{
	bool is_pairs=false;
	
	if(
		(card_1st->point_int==card_2nd->point_int || card_1st->point_int==card_3rd->point_int || card_2nd->point_int==card_3rd->point_int) &&
		(isTrips(card_1st, card_2nd, card_3rd)==false)
		//contain 2 same cards
		//but not 3 same cards
	)
	{
		is_pairs=true;
	}
	else
	{
		is_pairs=false;
	}
	
	return is_pairs;
}

/*******************************************************
Function	:Deal three cards(nothing special, just three cards)
Argument	:None
Return		:None
*******************************************************/
void DealThreeCards(Cards *card_1st, Cards *card_2nd, Cards *card_3rd)						//Deal 3 card
{
	int Available_List[54];
	memset(Available_List,AVAILABLE,sizeof(Available_List));
	
	*card_1st=CardGenerator(Available_List,NOJOKER);
	*card_2nd=CardGenerator(Available_List,NOJOKER);
	*card_3rd=CardGenerator(Available_List,NOJOKER);
}


/*******************************************************
Function:
	Generate some types of card combination in ThreeCardBrag
	game depends on input parameter "type".
Argument:
	Cards *, Cards *, Cards *, char type
	(type for Trips, Flush, Straight, etc)
Return:
	times to generate this type
*******************************************************/
int ThreeCardBrag(Cards *card_1st, Cards *card_2nd, Cards *card_3rd, char type)
{
	int i=0;			//for loop
	int times=0;		//for times to generate one type
	bool isDone=false;	//for finished judgment
	
	if(type==Trips)								//generate Trips
	{
		while(isDone==false)
		{
			DealThreeCards(card_1st, card_2nd, card_3rd);
			isDone=isTrips(card_1st, card_2nd, card_3rd);
			times++;
		}
	}
	
	if(type==Straight_Flush)					//generate Straight_Flush
	{
		while(isDone==false)
		{
			DealThreeCards(card_1st, card_2nd, card_3rd);
			if(isStraightFlush(card_1st, card_2nd, card_3rd)==true)
			{
				isDone=true;
			}
			else
			{
				isDone=false;
			}
			times++;
		}
	}	
	
	if(type==Flush)								//generate Flush
	{
		while(isDone==false)
		{
			DealThreeCards(card_1st, card_2nd, card_3rd);
			isDone=isFlush(card_1st, card_2nd, card_3rd);
			times++;
		}
	}
	
	if(type==Straight)							//generate Straight
	{
		while(isDone==false)
		{
			DealThreeCards(card_1st, card_2nd, card_3rd);
			isDone=isStraight(card_1st, card_2nd, card_3rd);
			times++;
		}
	}
	
	if(type==Pairs)								//generate Pairs
	{
		while(isDone==false)
		{
			DealThreeCards(card_1st, card_2nd, card_3rd);
			isDone=isPairs(card_1st, card_2nd, card_3rd);
			times++;
		}
	}
	
	return times;
}


/*******************************************************
Function:
	Initialize all the thing. Put everything you want to
	initial here.
Argument:None
Return	:None
*******************************************************/
void Initialize()
{
	srand((unsigned)time(NULL));						//Random number seed initial, 2014.03.16 zhanglin
}

/*******************************************************
Function:
	A game. Generate a 4 length number, then player guess.
	If number and place match, A++. Only number match, B++.
	8 chances.
Argument:None
Return	:None
*******************************************************/
void AB_Game()
{
	char input[100];
	int Guess;
	int A=0,B=0;
	int R1,R2,R3,R4;					//Rand  1,2,3,4
	int G1,G2,G3,G4;					//Guess 1,2,3,4

	R1=R2=R3=R4=randnum(0,9);			//generate numbers

	while(R2==R1)						//to make sure there is no repetition -S
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
	}									//to make sure there is no repetition -E

	//printf("%d,%d,%d,%d\n",R1,R2,R3,R4);
	
	//Game start:
	for(int i=1;i<=8;i++)				//1 to 8, 8 chances
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
		
		Guess=Str2Int(input);					//string to int
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
Function:check the ABgame input number is valid or not
Argument:char data[100]
Return:	true for valid
	   	false for not valid
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
	check=Str2Int(data);										//string to int
	
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
}

/*******************************************************
Function	:Call woords() function
Argument	:None
Return		:None
*******************************************************/
void _stdcall Callwooords(void)
{
	char	word[30];															//store the input word
	int		length=0;															//store the required word length
	char	keyword=0;															//store the required key letter

	char command[COMMAND_STR_LEN];
	char para_1st[COMMAND_STR_LEN];
	char para_2nd[COMMAND_STR_LEN];

	memset(command,'\0',sizeof(command));											//initialize command
	memset(para_1st,'\0',sizeof(para_1st));											//initialize parameter 1st
	memset(para_2nd,'\0',sizeof(para_2nd));											//initialize parameter 2nd
	memset(word,'\0',sizeof(word));

	while(true)
	{
		printf("\nControlDock\\Wooords>(word,length,key)");							//welcome words
		GetCommand(command,para_1st,para_2nd);										//get main command and parameters

		if( Equal(command,"-exit") || Equal(command,"exit") )						//exit
		{
			break;
		}
		else if( Equal(command,"") )												//invalid input
		{
			//printf("Invalid input\n\n");	//2014.03.14 zhanglin make it invalid
			;								//2014.03.14 zhanglin do nothing
		}
		else if( Equal(command,"-show") )											//show last input
		{
			if(word[0] )
			{
				puts("NULL\n");														//no last input
			}
			else
			{
				printf("%s\n",word);												//show
			}
		}
		else if( Equal(command,"-last") )											//use the last input
		{
			printf("please input length:");											//get the length
			scanf("%d",&length);
			getchar();

			printf("please input keyword:");										//get the keyword
			scanf("%c",&keyword);
			getchar();

			wooords(word,length,keyword);											//call wooords
		}
		else if( Equal(command,"ok") )												//start wooords. annulment
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
		else if( Equal(command,"cls") || Equal(command,"-cls") )					//clean screen
		{
			system("cls");
		}
		else																		//defalut mode. first command is the input
																					//para_1 is length
																					//para_2 is keyword
		{
			memcpy(word,command,sizeof(word));										//copy command to word
			length=Str2Int(para_1st);												//copy para1 to length
			keyword=para_2nd[0];													//copy para2 to keyword

			if(Str2Int(para_1st)==ERROR_MARK)										//when error, result of Str2Int is -1
			{
				length = NO_RESTRICT_LENGTH;										//when error, convert to no restrict length
			}
			if(para_2nd[0]=='\0' || para_2nd[0]=='0')								//convert to default no restrict keyword
			{
				keyword = NO_RESTRICT_KEYWORD;
			}

			wooords(word,length,keyword);											//call wooords
		}
	}	
}

/*******************************************************
Function	:The CMD like process entry point
Argument	:None
Return		:None
*******************************************************/
void ControlDock(void)
{
	char command[COMMAND_STR_LEN];
	char para_1st[COMMAND_STR_LEN];
	char para_2nd[COMMAND_STR_LEN];
	
	while(true)																	//Loops, waiting for the command
	{
		printf("\nControlDock>");												//Always prompt "ControlDock>"
		GetCommand(command,para_1st,para_2nd);									//Then get the user's command
		
		//Exit
		if( Equal(command,"-exit") || Equal(command,"exit") )
		{
			break;
		}
		
		//Clean the screen
		else if( Equal(command,"cls") || Equal(command,"-cls") )
		{
			system("cls");
		}
		
		//No input, do nothing, just show a new prompt
		else if( Equal(command,"") )
		{
			;
		}
		
		//Show user's help
		else if( Equal(command,"-help") || Equal(command,"help") || Equal(command,"-?") || Equal(command,"/?") )
		{
			help();
		}
		
		//Call DotA's roll function
		else if( Equal(command,"-roll") || Equal(command,"roll") )
		{
			roll(para_1st, para_2nd);
		}
		
		//Call iOS game woords' assistant function
		else if( Equal(command,"-word") || Equal(command,"word") )
		{
			Callwooords();
		}
		
		//Play the AB game
		else if( Equal(command,"abgame") )
		{
			AB_Game();
		}
		
		else if( Equal(command,"lastone") )
		{
			CallLastOne();
		}
		
		//Not match any case, re-input
		else
		{
			printf("Sorry, unknown command,\n");
			printf("please check your input and try again.\n\n");
		}
	}
}

/*******************************************************
Function:None
Argument:None
Return	:None
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
Function:
														
	iOS game woords's Plug-in function:
														
	1.Count each letter's numbers of input word,
	  then count each letter's number of lexicon word,
	  if input letter's number of input is the same or
	  bigger than letter's number of lexicon, means this
	  word can be form by input letters, so show it.
														
	2.The 1st parameter is limited length and the
	  2nd parameter is the needed keyword.
	  If length is not match or lexicon word do not
	  contain keyword, not show it.
	  But if 1st para is 0, means no length limited,
	  2nd para is 0,means no keyword limited.
														
Argument:char *, int, char
Return	:None
*******************************************************/
void wooords(char *letters, int length, char keyword)
{
	//make it invalid 2014.03.12 zhanglin -S
	//because the lexicon.dat is missing 2014.03.12
	//int _8kLength=CountArrayLength((int *)lexicon8k);//-CountArrayLength((int *)lexicon8k);		//calculate 8k length
	//int _36kLength=CountArrayLength((int *)lexicon36k);											//calculate 36k length
	//make it invalid 2014.03.12 zhanglin -E

	/********************************************************
	when error, try to use 8k-36k to calculat length of 8k. 
	because sometimes length of 8k is wrongly caculated from 
	the very start to the very end. that means contain 8k and 36k=43k.
	the real length of 8k is about 8k.		--2013/5/13
	the real length of 36k is about 36k.	--2013/5/13
	********************************************************/
	
	/********************************************************
	Any time if the comment of 2nd part or 3rd part is different from 1st part,
	please subject to 1st part's comment, because I may not update 2nd and 3rd
	in time.			zhanglin 2014.03.16
	********************************************************/
	
	int _90kLength_1=CountArrayLength((int *)lexicon90k_1);										//calculate 90k part 1
	int _90kLength_2=CountArrayLength((int *)lexicon90k_2);										//calculate 90k part 2
	int _90kLength_3=CountArrayLength((int *)lexicon90k_3);										//calculate 90k part 3
	
	int i=0,j=0,k=0;							//initialize i k j. 
												//i for lexicon length circle.		(about 30k)
												//j for word length.				(about 5~10)
												//k for alphabeta circle.			(about 26)

	int cnt_in[150];							//the input alphabeta counter. 		PS:150 is little more than ascll length
	int cnt_lex[150];							//the lexicon alphabeta counter.	PS:150 is little more than ascll length
	int countWordExist=0;						//founded words counter

	memset(cnt_in,0,sizeof(cnt_in));												//cnt_in initial
	memset(cnt_lex,0,sizeof(cnt_lex));												//cnt_lex initial	

	printf("The results are showing below\n\n");

	/*  count given word letters -S  */
	for(j=0;j<GetLength(letters);j++)												//from first letter to last letter. word
	{
		for(k='a';k<='z';k++)														//from a to z, alphabeta
		{
			if(letters[j]==k)														//if contain this letter
			{
				cnt_in[k]++;														//corresponding alphabeta counter++
				break;
			}
		}
	}
	/*  count given word letters -E  */

/************************************************************************************************/
/************************************************************************************************/
	//count lexicon words letters, the 1st -S
	for(i=0;i<_90kLength_1;i++)														//for all of the lexiconXXk
	{
		if( length==GetLength(lexicon90k_1[i]) || length==NO_RESTRICT_LENGTH )		//word length equals inquired length || 0 for no restrict
		{
			for(j=0;j<GetLength(lexicon90k_1[i]);j++)								//from word's first letter to last letter
			{
				for(k=0;k<='z';k++)													//from 0 to 'z'(ASCii), to avoid some show erratic characters
				{					
					if(lexicon90k_1[i][j]==k)										//if contain this letter, corresponding alphabeta counter++
					{
						cnt_lex[k]++;
						break;
					}//end of contain letter judgment
				}//end of ASCii count
			}//end of word's length loop
			
			//below to determine to show this word or not
			for(k=0;k<='z';k++)
			{
				if(cnt_in[k]<cnt_lex[k])break;										//corresponding input lettter number less than required number, berak(not show it)
				if(k=='z')															//until the end
				{
					if(lexicon90k_1[i][0]>='A' && lexicon90k_1[i][0]<='Z')break;	//if the first lettter of the word contains uppercase, break(not show it)
					if(cnt_lex[keyword]==0 && keyword!=NO_RESTRICT_KEYWORD)break;	//do not contain keyword and not no restrict command(if keyword is '0',not break, will show), break(not show it)
					if(GetLength(lexicon90k_1[i]) < MIN_WORD_LENGTH)break;			//word length not enough, break(not to show)

					if(countWordExist>=100 && countWordExist%100==0)getchar();		//split to small pages
					printf("%3d.%s\n",countWordExist+1,lexicon90k_1[i]);			//everything is fine, then print the word
					countWordExist++;												//founded words counter++
				}
			}
			memset(cnt_lex,0,sizeof(cnt_lex));										//clear lexicon alphabeta counter
		}//end of word length judgment
	}//end of _90kLength_1 loop 
	//count lexicon words letters, the 1st -E

/************************************************************************************************/
/************************************************************************************************/

	//count lexicon words letters, the 2nd -S
	for(i=0;i<_90kLength_2;i++)														//for all of the lexiconXXk
	{
		if( length==GetLength(lexicon90k_2[i]) || length==NO_RESTRICT_LENGTH )		//word length equals inquired length || 0 for no restrict
		{
			for(j=0;j<GetLength(lexicon90k_2[i]);j++)								//from word's first letter to last letter
			{
				for(k=0;k<='z';k++)													//from 0 to 'z'(ASCii), to avoid show some erratic characters
				{					
					if(lexicon90k_2[i][j]==k)										//if contain this letter, corresponding alphabeta counter++
					{
						cnt_lex[k]++;
						break;
					}//end of contain letter judgment
				}//end of ASCii count
			}//end of word's length loop
			
			//below to determine to show this word or not
			for(k=0;k<='z';k++)
			{
				if(cnt_in[k]<cnt_lex[k])break;										//corresponding input lettter number less than required number, berak(not show it)
				if(k=='z')															//until the end
				{
					if(lexicon90k_1[i][0]>='A' && lexicon90k_2[i][0]<='Z')break;	//if the first lettter of the word contains uppercase, break(not show it)
					if(cnt_lex[keyword]==0 && keyword!=NO_RESTRICT_KEYWORD)break;	//do not contain keyword and not no restrict command(if keyword is '0',not break, will show), break(not show it)
					if(GetLength(lexicon90k_2[i]) < MIN_WORD_LENGTH)break;			//word length not enough, break(not to show)

					if(countWordExist>=100 && countWordExist%100==0)getchar();		//split to small pages
					printf("%3d.%s\n",countWordExist+1,lexicon90k_2[i]);			//everything is fine, then print the word
					countWordExist++;												//founded words counter++
				}
			}
			memset(cnt_lex,0,sizeof(cnt_lex));										//clear lexicon alphabeta counter
		}//end of word length judgment
	}//end of _90kLength_2 loop
	//count lexicon words letters, the 2st -E

/************************************************************************************************/
/************************************************************************************************/

	//count lexicon words letters, the 3rd -S
	for(i=0;i<_90kLength_3;i++)														//for all of the lexiconXXk
	{
		if( length==GetLength(lexicon90k_3[i]) || length==NO_RESTRICT_LENGTH )		//word length equals inquired length || 0 for no restrict
		{
			for(j=0;j<GetLength(lexicon90k_3[i]);j++)								//from word's first letter to last letter
			{
				for(k=0;k<='z';k++)													//from 0 to 'z'(ASCii), to avoid show some erratic characters
				{					
					if(lexicon90k_3[i][j]==k)										//if contain this letter, corresponding alphabeta counter++
					{
						cnt_lex[k]++;
						break;
					}//end of contain letter judgment
				}//end of ASCii count
			}//end of word's length loop
			
			//below to determine to show this word or not
			for(k=0;k<='z';k++)
			{
				if(cnt_in[k]<cnt_lex[k])break;										//corresponding input lettter number less than required number, berak(not show it)
				if(k=='z')															//until the end
				{
					if(lexicon90k_1[i][0]>='A' && lexicon90k_3[i][0]<='Z')break;	//if the first lettter of the word contains uppercase, break(not show it)
					if(cnt_lex[keyword]==0 && keyword!=NO_RESTRICT_KEYWORD)break;	//do not contain keyword and not no restrict command(if keyword is '0',not break, will show), break(not show it)
					if(GetLength(lexicon90k_3[i]) < MIN_WORD_LENGTH)break;			//word length not enough, break(not to show)

					if(countWordExist>=100 && countWordExist%100==0)getchar();		//split to small pages
					printf("%3d.%s\n",countWordExist+1,lexicon90k_3[i]);			//everything is fine, then print the word
					countWordExist++;												//founded words counter++
				}
			}
			memset(cnt_lex,0,sizeof(cnt_lex));										//clear lexicon alphabeta counter
		}//end of word length judgment
	}//end of _90kLength_3 loop
	//count lexicon words letters, the 3st -E

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
}//end of wooords()

/*******************************************************
Function:None
Argument:None
Return:None
2014.03.12 zhanglin:
	Lexicon.dat is missing, so make this invalid
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
Function:DotA like, Roll game
Argument:None
Return:None
*******************************************************/
int roll(char *para_1, char *para_2)
{
	int ret=0;
	int para1=0;
	int para2=0;
	
	para1=Str2Int(para_1);
	para2=Str2Int(para_2);
	
	ret=randnum(para1,para2);
	
	printf("Your rolled num: %d\n\n",ret);
	
	return ret;
	
	/*
	int ret=0;
	int range=Str2Int(para);
	if(range==0)range=100;
	ret=randnum(0,range);
	printf("Your rolled num: %d\n\n",ret);
	return ret;
	*/
}

/*******************************************************
Function:None
Argument:None
Return	:None
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
Function:None
Argument:None
Return	:None
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
Function:None
Argument:None
Return	:None
*******************************************************/
void LANE0117()
{
	int CH=3;
	date gasDate[4];//gasDate[y]  All y below this y is the same
	date asDate[1][4]=//asDate[x][y]
	{//data start from here
		{//x start from here
			{2013,1,17},//y start from here
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
Function:None
Argument:None
Return	:None
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
Function:None
Argument:None
Return	:None
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
Function:
	"numbers" people numbered off, the one who yells "keys" 
	number will be excuted. Who can survive at last?
Argument:int int
Return	:None
*******************************************************/
void LastOne(int numbers,int keys)//numbers is people's numbers, keys is the "death" number
{
	int i=0;
	MAN *p,*pt,*pp;//pt to p this       pp to p previous.
	//p is used for make new data.
	//pt is current data.
	//pp always cache pt.
	//data1  to   data2   to    data3(new one)
	//pp          pt             p

	//to make this circle(below)
	MAN *head=NULL;	//new a head
	for(i=1;i<=numbers;i++)
	{
		p=(MAN *)malloc(sizeof(MAN));
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
	pp=pt;//make the cache equal the last people
	pt->next=head;//to make it a circle
	pt=head;//from the start
	i=0;
	while(1)
	{
		i++;
		printf("I'm No.%-3d %-2d times\n",pt->num,(i%keys)+(i%keys==0?keys:0));//report current person's number
		if(i%keys==0)//kill this person
		{
			printf("No.%d has been killed\n\n",pt->num);//tell everyone this person has been killed
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
	printf("\n");
	printf("Last surviver is:\n");
	printf("No.%d\n",pt->num);
	printf("Congradulations!!!\n");
}





//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************

/*******************************************************
Function:Frame of count day in a year
Argument:None
Return	:None
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
	year=Str2Int(StrIn);
	printf("Please input month:");
	scanf("%s",&StrIn);
	getchar();
	while(CheckData(StrIn,"month",year,month,day)==false)
	{
		printf("Please input month:");
		scanf("%s",&StrIn);
		getchar();
	}
	month=Str2Int(StrIn);
	printf("Please input day:");
	scanf("%s",&StrIn);
	getchar();
	while(CheckData(StrIn,"day",year,month,Str2Int(StrIn))==false)
	{
		printf("Please input day:");
		scanf("%s",&StrIn);
		getchar();
	}
	day=Str2Int(StrIn);
	CalcDate(year,month,day);
}
/*******************************************************
Function:Leap year judge
Argument:int
Return	:bool
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
Function:Check the input valid or not
Argument:char[],char [],int ,int ,int
	 data[]:input data
	 type[]:data type(year, month, day, etc)
	 year,month,day:time data
Return:int
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
		isLeapYear(Str2Int(data));
	}
	if(type=="month")
	{
		if (GetLength(data)>2)
		{
			printf("Data length is out of bound\n\n");
			return false;
		}
		if(Str2Int(data)>12||Str2Int(data)<1)
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
		if(Str2Int(data)>31||Str2Int(data)<1)
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
Function:None
Argument:date
Return	:None
*******************************************************/
void CalcDateinterface(date date)
{
	CalcDate(date.year,date.month,date.day);
}

/*******************************************************
Function:Core of count the day in a year
Argument:int ,int ,int 
Return:void
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
Function:None
Argument:None
Return	:None
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
Function:None
Argument:None
Return	:None
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
Function:None
Argument:None
Return	:None
*******************************************************/
void sayhello()
{
	printf("hello\n");
	getchar();
}

/*******************************************************
Function:None
Argument:None
Return	:None
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
Function:None
Argument:None
Return	:None
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
Function:
	sort an array whose elements no more than 10. 
	elements of this array are strings.
	order of sorted array is:
	value less in ascll, rank former.
	front value the same, the longer, the latter.
Argument:char * [10]	 
Return	:None
*******************************************************/
//function failed
void Sort_Str(char *data[10])
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
Function:Output all the arrangement
Argument:
	char data:array
	int length:array length
	char type:string or int or something
Return:None
*******************************************************/
void Arrangement(char data[],int length,char type)
{
    int i=0,j=0,k=0,z=0;
    for(i=Factorial(length);i>0;i--)					//number of all the possibilities
    {
		Exchange(&data[j],&data[j+1]);					//swap 1st 2nd numbers
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
	printf("\n");
}

/*******************************************************
Function:Output all the arrangement
Argument:
	int data:array
	int length:array length
	char type:string or int or something
Return:None
*******************************************************/
void Arrangement(int data[],int length,char type)
{
    int i=0,j=0,k=0,z=0;
    for(i=Factorial(length);i>0;i--)					//number of all the possibilities
    {
		Exchange(&data[j],&data[j+1]);					//swap 1st 2nd numbers
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
	printf("\n");
}