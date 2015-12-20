#include "headers.h"

/*******************************************************
Function:
    calulate probability of overflow if ask another card
Argument:
    Cards cards[], int Available_List[]
Return:
    float: overflow probability
*******************************************************/
float TwentyOnePointOverflowProbability(Cards cards[], int Available_List[])
{
    int i = 0;              //index
    int numerator = 0;      //A in A/B
    int denominator = 0;    //B in A/B
    float currentPts = 0;   //current POINT
    float capacity = 0;     //hwo to describle?
    Cards Card_Set[52]; 

    currentPts = TwentyOnePointCalculator(cards);
    capacity = 21 - currentPts;

    for(i=0;i<52;i++)                               //initialieze card set
    {
        Card_Set[i].uni_num=i;                      //get uninum
        CardUni2Int(&Card_Set[i]);                  //Convert Uni_Num to Int, and set it to card
        CardInt2StrConvertor(&Card_Set[i]);         //set this card's string
    }

    //calculate probabiblity of card's value no more than capacity
    for(i=0;i<52;i++)
    {
        if(TwentyOnePointConvertor(Card_Set[i]) <= capacity && Available_List[i]==AVAILABLE)
        {
            numerator++;    //A in A/B
        }
    }
    
    for(i=0;i<52;i++)
    {
        if(Available_List[i]==AVAILABLE)
        {
            denominator++;  //B in A/B
        }
    }

    return (float)numerator/denominator; //return probabiblity
}

/*******************************************************
Function:
    AI decide require card or not (alpha)
Argument:
    Cards card[]
Return:
    true for need card
    false for not need card
*******************************************************/
bool TwentyOnePointAI(Cards cards[], int Available_List[])
{
    //todo: add request card judgement
    if(TwentyOnePointOverflowProbability(cards, Available_List) > 0.5) //more than 50%
    {
        return true;
    }
    else //less than 50%
    {
        return false;
    }
}

/*******************************************************
Function:
    convert and return cars's value.
Argument:
    Cards card
Return:
    float
*******************************************************/
float TwentyOnePointConvertor(Cards card)
{
    float pts = 0;                  //init pts
    switch (card.point_int)         //switch
    {
        case Ace:                   //Ace is one point
            pts = 1;
            break;
        case Jack:                  //Jack is 0.5 point
            pts = 0.5;
            break;
        case Queen:                 //Queen is 0.5 point
            pts = 0.5;
            break;
        case King:                  //King is 0.5 point
            pts = 0.5;
            break;
        default:                    //others is its original value
            pts = (float)card.point_int;
            break;
    }
    return pts;                     //return pts
}

/*******************************************************
Function:
    calculate input cards array's value.
Argument:
    Cards cards[]
Return:
    float pts
*******************************************************/
float TwentyOnePointCalculator(Cards cards[])
{
    int i=0;                        //index
    float pts=0;                    //points

    for(i=0;i<CountArrayLength(cards);i++)  //calculate the sum of input cards array
    {
        pts+=TwentyOnePointConvertor(cards[i]);
    }

    return pts;                     //return
}

/*******************************************************
Function:
    21points game. AI first, player after. One's card's
    value should no more than 21, the one whoes value bigger
    wins the game.
Argument:None
Return  :None
*******************************************************/
void TwentyOnePointGame()
{
    Cards AI_Cards[54];                                                 //AI_Cards array
    Cards Player_Cards[54];
    int Available_List[54];                                             //available list
    int i=0;                                                            //index
    char input[10];

    memset(Available_List,AVAILABLE,sizeof(Available_List));            //init Available_List
    memset(AI_Cards,0,sizeof(AI_Cards));                                //init AI_Cards
    memset(Player_Cards,0,sizeof(Player_Cards));                        //init Player_Cards

    /* --------------------AI turn-------------------- */
    AI_Cards[0]=CardGenerator(Available_List, NOJOKER);                 //get the hand card

    printf("AI turn:\n");
    //printf("Card : %s %s\n", AI_Cards[0].suit_str, AI_Cards[0].point_str); //debug print AI's hole card
    printf("Hole card: Secret\n");
    printf("---------\n");

    i=1;    //AI request card
    while(TwentyOnePointAI(AI_Cards, Available_List))
    {
        AI_Cards[i]=CardGenerator(Available_List, NOJOKER);
        printf("Card %d: %-7s %s\n", i,AI_Cards[i].suit_str, AI_Cards[i].point_str);
        i++;
    }
    //printf("\nLast point: %.1f\n",TwentyOnePointCalculator(AI_Cards));    //debug print AI's value

    /* --------------------Player turn-------------------- */
    Player_Cards[0]=CardGenerator(Available_List, NOJOKER);                 //get the hole card

    printf("\n\nPlayer turn:\n");
    printf("Hole card: %s %s\n", Player_Cards[0].suit_str, Player_Cards[0].point_str);
    printf("---------");

    i=1;    //Player request card
    cin >> input;
    while(input[0]!='n' && TwentyOnePointCalculator(Player_Cards)<=21)      //while not 'n' && point is no more than 21
    {
        Player_Cards[i]=CardGenerator(Available_List, NOJOKER);
        printf("Card %d: %-7s %s", i,Player_Cards[i].suit_str, Player_Cards[i].point_str);
        i++;
        cin >> input;
    }
    //printf("\nLast point: %.1f\n",TwentyOnePointCalculator(Player_Cards));    //debug print Player's value

    /* --------------------judgement-------------------- */
    printf("\n");
    printf("---------\n");
    printf("AI point: %.1f\n",TwentyOnePointCalculator(AI_Cards));      //print AI's point
    printf("Player point: %.1f\n",TwentyOnePointCalculator(Player_Cards));  //print Player's point
    if(TwentyOnePointCalculator(AI_Cards)>21 && TwentyOnePointCalculator(Player_Cards)>21)
    {
        printf("Tied\n");
    }
    else if(TwentyOnePointCalculator(AI_Cards)>21)
    {
        printf("Player win\n");
    }
    else if(TwentyOnePointCalculator(Player_Cards)>21)
    {
        printf("AI win\n");
    }
    else if(TwentyOnePointCalculator(AI_Cards) == TwentyOnePointCalculator(Player_Cards))
    {
        printf("Tied\n");
    }
    else if(TwentyOnePointCalculator(AI_Cards) > TwentyOnePointCalculator(Player_Cards))
    {
        printf("AI win\n");
    }
    else if(TwentyOnePointCalculator(AI_Cards) < TwentyOnePointCalculator(Player_Cards))
    {
        printf("Player win\n");
    }
}

/*******************************************************
Function:
    Convert and card's Uni_Num to card's Int and set Int to card
Argument:Cards *
Return  :None
*******************************************************/
void CardUni2Int(Cards *card)
{
    if(card->uni_num==52)       //Black_joker
    {
        card->suit_int=52;      //set both suit and point int as 52
        card->point_int=52;
    }
    else if(card->uni_num==53)  //Red_Joker
    {
        card->suit_int=53;      //set both suit and point int as 53
        card->point_int=53;
    }
    else                        //0 to 51
    {
        card->suit_int=(card->uni_num)/13;                      //set suit.
        
                                                                //suit:
                                                                //0 for Spade
                                                                //1 for Heart
                                                                //2 for Club
                                                                //3 for Diamond
        
                                                                //here the uni_number couldn't be over 51
                                                                //if the number over 51, such as 52
                                                                //52 / 13 = 4, or even bigger, which means nothing

        card->point_int=card->uni_num%13+1;                     //set point_int, eg: 0%13=0, 0+1=1 means Ace, thus here should be added 1
    }
}


/*******************************************************
Function:
    Convert card's int to card's str.
    If this card is a Joker, then set both its suit and point
    string as Joker.
Argument:Cards *
Return  :None
*******************************************************/
void CardInt2StrConvertor(Cards *card)
{
    if      (card->suit_int==Spade)         strcpy(card->suit_str, "Spade");    //convert suit_int to suit_str
    else if (card->suit_int==Heart)         strcpy(card->suit_str, "Heart");
    else if (card->suit_int==Club)          strcpy(card->suit_str, "Club");
    else if (card->suit_int==Diamond)       strcpy(card->suit_str, "Diamond");
    else if (card->suit_int==Black_Joker)   strcpy(card->suit_str, "Blk");
    else if (card->suit_int==Red_Joker)     strcpy(card->suit_str, "Red");

    if      (card->point_int==Ace)          strcpy(card->point_str, "A");       //convert point_int to point_str
    else if (card->point_int==Jack)         strcpy(card->point_str, "J");
    else if (card->point_int==Queen)        strcpy(card->point_str, "Q");
    else if (card->point_int==King)         strcpy(card->point_str, "K");
    else if (card->point_int==1)            strcpy(card->point_str, "1");
    else if (card->point_int==2)            strcpy(card->point_str, "2");
    else if (card->point_int==3)            strcpy(card->point_str, "3");
    else if (card->point_int==4)            strcpy(card->point_str, "4");
    else if (card->point_int==5)            strcpy(card->point_str, "5");
    else if (card->point_int==6)            strcpy(card->point_str, "6");
    else if (card->point_int==7)            strcpy(card->point_str, "7");
    else if (card->point_int==8)            strcpy(card->point_str, "8");
    else if (card->point_int==9)            strcpy(card->point_str, "9");
    else if (card->point_int==10)           strcpy(card->point_str, "10");
    else if (card->point_int==Black_Joker)  strcpy(card->point_str, "Blk");
    else if (card->point_int==Red_Joker)    strcpy(card->point_str, "Red");
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
    Cards card;                                                 //new a card
    
    with_joker==true ? card.uni_num=randnum(0,53) : card.uni_num=randnum(0,51);
    //if with_joker is true, 1 to 54
    //if with_joker is false, 1 to 52
    
    while(Available_List[card.uni_num]!=AVAILABLE)              //if this card is not available, generate again
    {
        with_joker==true ? card.uni_num=randnum(0,53) : card.uni_num=randnum(0,51);
        //if with_joker is true, 1 to 54
        //if with_joker is false, 1 to 52
    }
    Available_List[card.uni_num]=NON_AVAILABLE;                 //after one successful generation, set this card number unavailable
    
    
    CardUni2Int(&card);                                         //Convert Uni_Num to Int, and set it to card
    CardInt2StrConvertor(&card);                                //set this card's string
    
    return card;                                                //return this new generated card
}

/*******************************************************
Function    :Call LastOne() function
Argument    :None
Return      :None
*******************************************************/
void CallLastOne()
{
    char para_1st[COMMAND_STR_LEN];
    char para_2nd[COMMAND_STR_LEN];
    char para_3rd[COMMAND_STR_LEN];//Infact, useless, just to fill up the GetCommand()'s three parameters

    memset(para_1st,'\0',sizeof(para_1st));                                         //initialize para_1st
    memset(para_2nd,'\0',sizeof(para_2nd));                                         //initialize para_2nd
    memset(para_3rd,'\0',sizeof(para_3rd));                                         //initialize para_3rd
    
    while(true)
    {
        printf("ControlDock\\LastOne>(peoples,number)");                            //welcome words
        GetCommand(para_1st,para_2nd,para_3rd);                                     //get input

        if( Equal(para_1st, (char *)"-exit") || Equal(para_1st, (char *)"exit") )                     //exit
        {
            break;
        }
        else if( Equal(para_1st, (char *)"") )                                               //invalid input
        {
            ;                                                                       //do nothing, out put another line
        }
        else if( Equal(para_1st, (char *)"cls") || Equal(para_1st, (char *)"-cls") )                  //clean screen
        {
            system("cls");
        }
        else if( Str2Int(para_1st)==ERROR_MARK || Str2Int(para_2nd)==ERROR_MARK )   //invalid input
        {
            printf("Sorry, invalid input, please check and try again.\n");
        }
        else if( Str2Int(para_1st)==0 || Str2Int(para_2nd)==0 )                     //invalid input(people and times cannot be 0)
        {
            printf("Sorry, invalid input, please check and try again.\n");
        }
        else
        {
            LastOne( Str2Int(para_1st),Str2Int(para_2nd) );                         //call lastone
        }
    }
}


/*******************************************************
Function    :is trips judgement
Argument    :None
Return:
    ture:   is trips
    false:  is not trips
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
Function    :is StraightFlush judgement
Argument    :None
Return:
    ture:   is StraightFlush
    false:  is not StraightFlush
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
Function    :is flush judgement
Argument    :None
Return:
    ture:   is flush
    false:  is not flush
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
Function    :is straight judgement
Argument    :None
Return:
    ture:   is straight
    false:  is not straight
*******************************************************/
bool isStraight(Cards *card_1st, Cards *card_2nd, Cards *card_3rd)
{
    bool is_straight=false;
    int seq[3];
    
    seq[0]=card_1st->point_int;
    seq[1]=card_2nd->point_int;
    seq[2]=card_3rd->point_int;
    
    Sort_Int(seq,3);                                //sort the three numbers, from small to large
    
    if(seq[2]-seq[1]==1 && seq[1]-seq[0]==1)        //n,n+1,n+2, can be a straight
    {
        if(seq[0]!=Ace)                             //n,n+1,n+2, and n!=Ace make it real straight, because A,2,3 is not straight
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
Function    :is pairs judgement
Argument    :None
Return:
    ture:   is pairs
    false:  is not pairs
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
Function    :Deal three cards(nothing special, just three cards)
Argument    :None
Return      :None
*******************************************************/
void DealThreeCards(Cards *card_1st, Cards *card_2nd, Cards *card_3rd)                      //Deal 3 card
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
    int times=0;        //for times to generate one type
    bool isDone=false;  //for finished judgment
    
    if(type==Trips)                             //generate Trips
    {
        while(isDone==false)
        {
            DealThreeCards(card_1st, card_2nd, card_3rd);
            isDone=isTrips(card_1st, card_2nd, card_3rd);
            times++;
        }
    }
    
    if(type==Straight_Flush)                    //generate Straight_Flush
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
    
    if(type==Flush)                             //generate Flush
    {
        while(isDone==false)
        {
            DealThreeCards(card_1st, card_2nd, card_3rd);
            isDone=isFlush(card_1st, card_2nd, card_3rd);
            times++;
        }
    }
    
    if(type==Straight)                          //generate Straight
    {
        while(isDone==false)
        {
            DealThreeCards(card_1st, card_2nd, card_3rd);
            isDone=isStraight(card_1st, card_2nd, card_3rd);
            times++;
        }
    }
    
    if(type==Pairs)                             //generate Pairs
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
Return  :None
*******************************************************/
void Initialize()
{
#ifdef WIN32
    _tsetlocale(LC_ALL, L"CHS");        //set locale codepage (Chinese)
#endif
    srand((unsigned)time(NULL));        //Random number seed initial, 2014.03.16 zhanglin
}

/*******************************************************
Function:
    A game. Generate a 4 length number, then player guess.
    If number and place match, A++. Only number match, B++.
    8 chances.
Argument:None
Return  :None
*******************************************************/
void AB_Game()
{
    char input[100];
    int Guess;
    int A=0,B=0;
    int R1,R2,R3,R4;                    //Rand  1,2,3,4
    int G1,G2,G3,G4;                    //Guess 1,2,3,4

    R1=R2=R3=R4=randnum(0,9);           //generate numbers

    while(R2==R1)                       //to make sure there is no repetition -S
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
    }                                   //to make sure there is no repetition -E

    //printf("%d,%d,%d,%d\n",R1,R2,R3,R4);
    
    //Game start:
    for(int i=1;i<=8;i++)               //1 to 8, 8 chances
    {
        if(i<8)                         //normal process
        {
            printf("Round %d:\n",i);
        }
        else                            //last try, remind player
        {
            printf("Round %d:(last chance)\n",i);
        }
        
        cin >> input;                            //get the input
        while(!AB_GameInputCheck(input))        //check the input is valid or not
        {
            printf("Invalid input\n");
            cin >> input;
        }
        
        Guess=Str2Int(input);                   //string to int
        //printf("%d\n",Guess);
        G1=Guess/1000%10;
        G2=Guess/100%10;
        G3=Guess/10%10;
        G4=Guess/1%10;

        //printf("%d,%d,%d,%d\n",G1,G2,G3,G4);

        if(G1==R1)A+=1;                                 //count A
        if(G2==R2)A+=1;
        if(G3==R3)A+=1;
        if(G4==R4)A+=1;
        if((G1==R2)||(G1==R3)||(G1==R4))B+=1;           //count B
        if((G2==R3)||(G2==R4)||(G2==R1))B+=1;
        if((G3==R4)||(G3==R1)||(G3==R2))B+=1;
        if((G4==R1)||(G4==R2)||(G4==R3))B+=1;
        
        printf("%dA,%dB\n",A,B);                        //display the result
        
        if(A==4)                                        //everything is right, win
        {
            printf("Bingo!!!\n");break;
        }
        
        if(i==8)                                        //sorry, game over
        {
            printf("Game Over!!!\n");
        }
        
        
        A=B=0;
    }
    
    printf("Number is:%d\n",R1*1000+R2*100+R3*10+R4);   //show the right number(no matter player guess it or not)
}


/*******************************************************
Function:check the ABgame input number is valid or not
Argument:char data[100]
Return: true for valid
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
        if(data[i]<48||data[i]>57)return false;                 //contain letters, return false
    }
    check=Str2Int(data);                                        //string to int
    
    N1=check/1000%10;
    N2=check/100%10;
    N3=check/10%10;
    N4=check/1%10;
    
    if(N1==0)                                                   //if kilobit is 0, only check N2,N3,N4
    {
        check/=100;
        if((check<=0)||(check>9))return false;
        if((N1==N2)||(N1==N3)||(N1==N4))return false;
        if((N2==N3)||(N2==N4))return false;
        if (N3==N4) return false;
    }
    else
    {
        check/=1000;                                            //else check whole number, N1,N2,N3,N4
        if((check<=0)||(check>9))return false;
        if((N1==N2)||(N1==N3)||(N1==N4))return false;
        if((N2==N3)||(N2==N4))return false;
        if (N3==N4) return false;
    }
    return true;                                                //everything is OK, return true
}

/*******************************************************
Function    :Call woords() function
Argument    :None
Return      :None
*******************************************************/
void Callwooords(void)
{
    char    word[30];                                                           //store the input word
    int     length=0;                                                           //store the required word length
    char    keyword=0;                                                          //store the required key letter

    char command[COMMAND_STR_LEN];
    char para_1st[COMMAND_STR_LEN];
    char para_2nd[COMMAND_STR_LEN];

    memset(command,'\0',sizeof(command));                                           //initialize command
    memset(para_1st,'\0',sizeof(para_1st));                                         //initialize parameter 1st
    memset(para_2nd,'\0',sizeof(para_2nd));                                         //initialize parameter 2nd
    memset(word,'\0',sizeof(word));

    while(true)
    {
        printf("\nControlDock\\Wooords>(word,length,key)");                         //welcome words
        GetCommand(command,para_1st,para_2nd);                                      //get main command and parameters

        if( Equal(command, (char *)"-exit") || Equal(command, (char *)"exit") )                       //exit
        {
            break;
        }
        else if( Equal(command, (char *)"") )                                                //invalid input
        {
            //printf("Invalid input\n\n");  //2014.03.14 zhanglin make it invalid
            ;                               //2014.03.14 zhanglin do nothing
        }
        else if( Equal(command, (char *)"-show") )                                           //show last input
        {
            if(word[0] )
            {
                puts("NULL\n");                                                     //no last input
            }
            else
            {
                printf("%s\n",word);                                                //show
            }
        }
        else if( Equal(command, (char *)"-last") )                                           //use the last input
        {
            printf("please input length:");                                         //get the length
            scanf("%d",&length);
            getchar();

            printf("please input keyword:");                                        //get the keyword
            scanf("%c",&keyword);
            getchar();

            wooords(word,length,keyword);                                           //call wooords
        }
        else if( Equal(command, (char *)"ok") )                                              //start wooords. annulment
        {
            printf("please input letters:");
            scanf("%s", word);
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
        else if( Equal(command, (char *)"cls") || Equal(command, (char *)"-cls") )                    //clean screen
        {
            system("cls");
        }
        else                                                                        //defalut mode. first command is the input
                                                                                    //para_1 is length
                                                                                    //para_2 is keyword
        {
            memcpy(word,command,sizeof(word));                                      //copy command to word
            length=Str2Int(para_1st);                                               //copy para1 to length
            keyword=para_2nd[0];                                                    //copy para2 to keyword

            if(Str2Int(para_1st)==ERROR_MARK)                                       //when error, result of Str2Int is -1
            {
                length = NO_RESTRICT_LENGTH;                                        //when error, convert to no restrict length
            }
            if(para_2nd[0]=='\0' || para_2nd[0]=='0')                               //convert to default no restrict keyword
            {
                keyword = NO_RESTRICT_KEYWORD;
            }

            wooords(word,length,keyword);                                           //call wooords
        }
    }   
}

/*******************************************************
Function    :The CMD like process entry point
Argument    :None
Return      :None
*******************************************************/
void ControlDock(void)
{
    char command[COMMAND_STR_LEN];
    char para_1st[COMMAND_STR_LEN];
    char para_2nd[COMMAND_STR_LEN];

    memset(command,'\0',COMMAND_STR_LEN);                   //initialize command
    memset(para_1st,'\0',COMMAND_STR_LEN);                  //initialize parameter 1st
    memset(para_2nd,'\0',COMMAND_STR_LEN);                  //initialize parameter 2nd

    printf("ControlDock [Version Alpha]\n");                //2014.04.14 added
    printf("Powered by zhanglintc. Nothing reserved.\n\n"); //2014.04.14 added
    
    while(true)                                                                 //Loops, waiting for the command
    {
        printf("ControlDock>");                                                 //Always prompt "ControlDock>"
        GetCommand(command,para_1st,para_2nd);                                  //Then get the user's command

        //No input, do nothing, just show a new prompt
        if( Equal(command, (char *)"") )
        {
            ;
        }

        //Exit
        else if( Equal(command, (char *)"-exit") || Equal(command, (char *)"exit") )
        {
            break;
        }
        
        //Clean the screen
        else if( Equal(command, (char *)"cls") || Equal(command, (char *)"-cls") )
        {
            system("cls");
            printf("\n");  //2014.04.14 added
        }

        //Show user's help
        else if( Equal(command, (char *)"-help") || Equal(command, (char *)"help") || Equal(command, (char *)"-?") || Equal(command, (char *)"/?") )
        {
            help();
        }
        
        //Call DotA's roll function
        else if( Equal(command, (char *)"-roll") || Equal(command, (char *)"roll") )
        {
            roll(para_1st, para_2nd);
        }
        
        //Call iOS game woords' assistant function
        else if( Equal(command, (char *)"-word") || Equal(command, (char *)"word") )
        {
            Callwooords();
        }
        
        //Play the AB game
        else if( Equal(command, (char *)"abgame") )
        {
            AB_Game();
        }
        
        //Call lastone
        else if( Equal(command, (char *)"lastone") )
        {
            CallLastOne();
        }

        //Play the 21 point game
        else if( Equal(command, (char *)"21game") )
        {
            TwentyOnePointGame();
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
Function:help function
Argument:None
Return  :None
*******************************************************/
void help(void)
{
    puts("-help -? /?");
    puts("-roll xxx");
    puts("21game");
    puts("abgame");
    puts("lastone");
    puts("-word word");
    puts("-exit exit\n");
}

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
Return  :None
*******************************************************/
void wooords(char *letters, int length, char keyword)
{
    //make it invalid 2014.03.12 zhanglin -S
    //because the lexicon.dat is missing 2014.03.12
    //int _8kLength=CountArrayLength((int *)lexicon8k);//-CountArrayLength((int *)lexicon8k);       //calculate 8k length
    //int _36kLength=CountArrayLength((int *)lexicon36k);                                           //calculate 36k length
    //make it invalid 2014.03.12 zhanglin -E

    /********************************************************
    when error, try to use 8k-36k to calculat length of 8k. 
    because sometimes length of 8k is wrongly caculated from 
    the very start to the very end. that means contain 8k and 36k=43k.
    the real length of 8k is about 8k.      --2013/5/13
    the real length of 36k is about 36k.    --2013/5/13
    ********************************************************/
    
    /********************************************************
    Any time if the comment of 2nd part or 3rd part is different from 1st part,
    please subject to 1st part's comment, because I may not update 2nd and 3rd
    in time.            zhanglin 2014.03.16
    ********************************************************/
    
    int _90kLength_1=CountArrayLength((intptr_t *)lexicon90k_1);                                     //calculate 90k part 1
    int _90kLength_2=CountArrayLength((intptr_t *)lexicon90k_2);                                     //calculate 90k part 2
    int _90kLength_3=CountArrayLength((intptr_t *)lexicon90k_3);                                     //calculate 90k part 3
    
    int i=0,j=0,k=0;                            //initialize i k j. 
                                                //i for lexicon length circle.      (about 30k)
                                                //j for word length.                (about 5~10)
                                                //k for alphabeta circle.           (about 26)

    int cnt_in[150];                            //the input alphabeta counter.      PS:150 is little more than ascll length
    int cnt_lex[150];                           //the lexicon alphabeta counter.    PS:150 is little more than ascll length
    int countWordExist=0;                       //founded words counter

    memset(cnt_in,0,sizeof(cnt_in));                                                //cnt_in initial
    memset(cnt_lex,0,sizeof(cnt_lex));                                              //cnt_lex initial   

    printf("The results are showing below\n\n");

    /*  count given word letters -S  */
    for(j=0;j<GetLength(letters);j++)                                               //from first letter to last letter. word
    {
        for(k='a';k<='z';k++)                                                       //from a to z, alphabeta
        {
            if(letters[j]==k)                                                       //if contain this letter
            {
                cnt_in[k]++;                                                        //corresponding alphabeta counter++
                break;
            }
        }
    }
    /*  count given word letters -E  */

/************************************************************************************************/
/************************************************************************************************/
    //count lexicon words letters, the 1st -S
    for(i=0;i<_90kLength_1;i++)                                                     //for all of the lexiconXXk
    {
        if( length==GetLength(lexicon90k_1[i]) || length==NO_RESTRICT_LENGTH )      //word length equals inquired length || 0 for no restrict
        {
            for(j=0;j<GetLength(lexicon90k_1[i]);j++)                               //from word's first letter to last letter
            {
                for(k=0;k<='z';k++)                                                 //from 0 to 'z'(ASCii), to avoid some show erratic characters
                {                   
                    if(lexicon90k_1[i][j]==k)                                       //if contain this letter, corresponding alphabeta counter++
                    {
                        cnt_lex[k]++;
                        break;
                    }//end of contain letter judgment
                }//end of ASCii count
            }//end of word's length loop
            
            //below to determine to show this word or not
            for(k=0;k<='z';k++)
            {
                if(cnt_in[k]<cnt_lex[k])break;                                      //corresponding input lettter number less than required number, berak(not show it)
                if(k=='z')                                                          //until the end
                {
                    if(lexicon90k_1[i][0]>='A' && lexicon90k_1[i][0]<='Z')break;    //if the first lettter of the word contains uppercase, break(not show it)
                    if(cnt_lex[keyword]==0 && keyword!=NO_RESTRICT_KEYWORD)break;   //do not contain keyword and not no restrict command(if keyword is '0',not break, will show), break(not show it)
                    if(GetLength(lexicon90k_1[i]) < MIN_WORD_LENGTH)break;          //word length not enough, break(not to show)

                    if(countWordExist>=100 && countWordExist%100==0)getchar();      //split to small pages
                    printf("%3d.%s\n",countWordExist+1,lexicon90k_1[i]);            //everything is fine, then print the word
                    countWordExist++;                                               //founded words counter++
                }
            }
            memset(cnt_lex,0,sizeof(cnt_lex));                                      //clear lexicon alphabeta counter
        }//end of word length judgment
    }//end of _90kLength_1 loop 
    //count lexicon words letters, the 1st -E

/************************************************************************************************/
/************************************************************************************************/

    //count lexicon words letters, the 2nd -S
    for(i=0;i<_90kLength_2;i++)                                                     //for all of the lexiconXXk
    {
        if( length==GetLength(lexicon90k_2[i]) || length==NO_RESTRICT_LENGTH )      //word length equals inquired length || 0 for no restrict
        {
            for(j=0;j<GetLength(lexicon90k_2[i]);j++)                               //from word's first letter to last letter
            {
                for(k=0;k<='z';k++)                                                 //from 0 to 'z'(ASCii), to avoid show some erratic characters
                {                   
                    if(lexicon90k_2[i][j]==k)                                       //if contain this letter, corresponding alphabeta counter++
                    {
                        cnt_lex[k]++;
                        break;
                    }//end of contain letter judgment
                }//end of ASCii count
            }//end of word's length loop
            
            //below to determine to show this word or not
            for(k=0;k<='z';k++)
            {
                if(cnt_in[k]<cnt_lex[k])break;                                      //corresponding input lettter number less than required number, berak(not show it)
                if(k=='z')                                                          //until the end
                {
                    if(lexicon90k_1[i][0]>='A' && lexicon90k_2[i][0]<='Z')break;    //if the first lettter of the word contains uppercase, break(not show it)
                    if(cnt_lex[keyword]==0 && keyword!=NO_RESTRICT_KEYWORD)break;   //do not contain keyword and not no restrict command(if keyword is '0',not break, will show), break(not show it)
                    if(GetLength(lexicon90k_2[i]) < MIN_WORD_LENGTH)break;          //word length not enough, break(not to show)

                    if(countWordExist>=100 && countWordExist%100==0)getchar();      //split to small pages
                    printf("%3d.%s\n",countWordExist+1,lexicon90k_2[i]);            //everything is fine, then print the word
                    countWordExist++;                                               //founded words counter++
                }
            }
            memset(cnt_lex,0,sizeof(cnt_lex));                                      //clear lexicon alphabeta counter
        }//end of word length judgment
    }//end of _90kLength_2 loop
    //count lexicon words letters, the 2st -E

/************************************************************************************************/
/************************************************************************************************/

    //count lexicon words letters, the 3rd -S
    for(i=0;i<_90kLength_3;i++)                                                     //for all of the lexiconXXk
    {
        if( length==GetLength(lexicon90k_3[i]) || length==NO_RESTRICT_LENGTH )      //word length equals inquired length || 0 for no restrict
        {
            for(j=0;j<GetLength(lexicon90k_3[i]);j++)                               //from word's first letter to last letter
            {
                for(k=0;k<='z';k++)                                                 //from 0 to 'z'(ASCii), to avoid show some erratic characters
                {                   
                    if(lexicon90k_3[i][j]==k)                                       //if contain this letter, corresponding alphabeta counter++
                    {
                        cnt_lex[k]++;
                        break;
                    }//end of contain letter judgment
                }//end of ASCii count
            }//end of word's length loop
            
            //below to determine to show this word or not
            for(k=0;k<='z';k++)
            {
                if(cnt_in[k]<cnt_lex[k])break;                                      //corresponding input lettter number less than required number, berak(not show it)
                if(k=='z')                                                          //until the end
                {
                    if(lexicon90k_1[i][0]>='A' && lexicon90k_3[i][0]<='Z')break;    //if the first lettter of the word contains uppercase, break(not show it)
                    if(cnt_lex[keyword]==0 && keyword!=NO_RESTRICT_KEYWORD)break;   //do not contain keyword and not no restrict command(if keyword is '0',not break, will show), break(not show it)
                    if(GetLength(lexicon90k_3[i]) < MIN_WORD_LENGTH)break;          //word length not enough, break(not to show)

                    if(countWordExist>=100 && countWordExist%100==0)getchar();      //split to small pages
                    printf("%3d.%s\n",countWordExist+1,lexicon90k_3[i]);            //everything is fine, then print the word
                    countWordExist++;                                               //founded words counter++
                }
            }
            memset(cnt_lex,0,sizeof(cnt_lex));                                      //clear lexicon alphabeta counter
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
Function:A roll game which is similar to then one in DotA
Argument:char *, char *
Return  :None
*******************************************************/
int roll(char *paraStr_1, char *paraStr_2)
{
    int ret=0;
    int paraInt_1=0;
    int paraInt_2=0;
    
    paraInt_1=Str2Int(paraStr_1);                                   //convert Str to Int, -1 when paraStr is in valid
    paraInt_2=Str2Int(paraStr_2);                                   //convert Str to Int, -1 when paraStr is in valid
    
    if( paraInt_1==ERROR_MARK || paraInt_2==ERROR_MARK )            //if para1 or prar2 is invalid, print invalid
    {
        printf("Sorry, unknown command,\n");
        printf("please check your input and try again.\n\n");
    }
    else if( paraInt_1 > paraInt_2 && GetLength(paraStr_2)!=0 )     //para1 is bigger than para2 and para2 is not NULL
    {
        printf("Sorry, unknown command,\n");
        printf("please check your input and try again.\n\n");
    }
    else if( GetLength(paraStr_1)==0 && GetLength(paraStr_2)==0 )   //if para1 and para2 is NULL, Rand default (0-100)
    {
        ret=randnum(0,100);
        printf("You have rolled: %d -- (0 to 100)\n\n",ret);
    }
    else                                                            //normal Rand
    {
        ret=randnum(paraInt_1,paraInt_2);
        if(paraInt_1 > paraInt_2)                                   //adjust para1 and para2's place when para2 is NULL
        {
            swap(&paraInt_1,&paraInt_2);
        }
        printf("You have rolled: %d -- (%d to %d)\n\n",ret,paraInt_1,paraInt_2);
    }   
    
    return 0;
}

/*******************************************************
Function:
    "numbers" people numbered off, the one who yells "number" 
    number will be excuted. Who can survive at last?
Argument:int int
Return  :None
*******************************************************/
void LastOne(int peoples,int number)//peoples is people's numbers, number is the "death" number
{
    int i=0;
    MAN *p_new=NULL;                        //point to the new one
    MAN *p_this=NULL;                       //point to the this
    MAN *p_cache=NULL;                      //point to the previous one
    MAN *head=NULL;                         //the a head

    //*****************************************************************
    //data1   to  data2   to   data3(new one)
    //p_cache     p_this       p_new
    //*****************************************************************

    //to make this circle(below)
    for(i=1;i<=peoples;i++)
    {
        p_new=(MAN *)malloc(sizeof(MAN));   //new an area
        p_new->num=i;                       //set number to this people
        
        if(head==NULL)                      //if this linked list is NULL
        {           
            head=p_new;                     //set new area to the head, so we could locate the very first area by using head
            p_this=head;                    //use p_this as a cursor to build the list, from head
        }           
        else
        {
            p_this->next=p_new;             //add the new one to the end of the list
            p_this=p_new;                   //then jump to the new one
        }
    }

    p_cache=p_this;                         //use p_cache back up the current place
    p_this->next=head;                      //to make it a circle
    p_this=head;                            //from the start
    i=1;                                    //reset the counter
    
    while(1)
    {
        printf("I'm No.%-3d %-2d times\n",p_this->num,( i%number )+( i%number==0 ? number : 0 ));   //report current person's number
        if(i%number==0)//kill this person
        {
            printf("No.%d has been killed\n\n",p_this->num);                                        //tell everyone this person has been killed
            p_cache->next=p_this->next;
            //delete this data(by jump over)
            //p_cache is the cache of p_this. "p_cache->next=p_this->next" means jump over p_this, means delete this person
            p_this=p_this->next;                                                                    //move on
        }
        else//not me, go ahead
        {
            p_cache=p_this;
            p_this=p_this->next;
        }
        i++;
        if(p_this->next==p_this)break;                                                              //only one person remains
    }

    //report the result
    printf("\n");
    printf("Last surviver is:\n");
    printf("No.%d\n",p_this->num);
    printf("Congradulations!!!\n");
}