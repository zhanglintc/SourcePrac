#include "stdafx.h"
#include "headers.h"

void GetLocalIP()
{
	WSADATA data;
	WSAStartup(2,&data);
	hostent* host = gethostbyname("");
 
	char *IP = inet_ntoa(*(struct in_addr*)*(host->h_addr_list));

	printf("Local IP: %s\n",IP);
 
	WSACleanup();
}

/*Soket Client Demo*/
void SocketClient()
{
    Sleep(2000);                        //沉睡2秒再连接server

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET s=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in sockaddr;
    sockaddr.sin_family=PF_INET;
    sockaddr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(9000);

    connect(s, (SOCKADDR*)&sockaddr, sizeof(SOCKADDR));

    char buffer[MAXBYTE]={0};
    recv(s, buffer, MAXBYTE, NULL);
    printf("***SERVER***%s", buffer);

    while(TRUE)
    {
        char* mymsg=new char[100000];
        printf("You can chat with server now:\n");
        gets(mymsg);
        send(s, mymsg, strlen(mymsg)+sizeof(char), NULL);
        /*
           recv函数中的bufferlength参数是可以固定值的
           send函数中的bufferlength参数不能固定值，需要看实际长度，并且考虑到'\0'字符串
        */
    }

    closesocket(s);
    WSACleanup();
}

/*Soket Server Demo*/
void SocketServer()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET s=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in sockaddr;
    sockaddr.sin_family=PF_INET;
    sockaddr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");   //需要绑定到本地的哪个IP地址
    sockaddr.sin_port=htons(9000);                          //需要监听的端口
    bind(s, (SOCKADDR*)&sockaddr, sizeof(SOCKADDR));        //进行绑定动作

    listen(s, 1);                                           //启动监听

    printf("listening on port [%d].\n", 9000);

    while(TRUE)
    {
        SOCKADDR clientAddr;
        int size=sizeof(SOCKADDR);

        SOCKET clientsocket;
        clientsocket=accept(s, &clientAddr, &size);                 //阻塞，直到有新tcp客户端连接
        printf("***SYS***    New client touched.\n");

        char* msg="Hello, my client.\r\n";
        send(clientsocket, msg, strlen(msg)+sizeof(char), NULL);    //这里的第三个参数要注意，是加了一个char长度的
        printf("***SYS***    HELLO.\n");

        while(TRUE)
        {
            char buffer[MAXBYTE]={0};
            recv(clientsocket, buffer, MAXBYTE, NULL);              //一直接收客户端socket的send操作
            printf("***Client***    %s\n", buffer);
        }

        closesocket(clientsocket);                                  //关闭socket
    }

    closesocket(s);                                                 //关闭监听socket    
    WSACleanup();                                                   //卸载
    getchar();
}

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
Return  :None
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
Function:
    sort an array whose elements no more than 10. 
    elements of this array are strings.
    order of sorted array is:
    value less in ascll, rank former.
    front value the same, the longer, the latter.
Argument:char * [10]     
Return  :None
*******************************************************/
//function failed
void Sort_Str(char *data[10])
{
    char **p=NULL,*tmp=NULL;                            //p point data. tmp point to data[X]. **tmp can do the same thing
    int i=0,j=0,k=0;                                    //i for 1st num. j for 2nd num. k for letters
    int length=0;                                       //length of letter

    p=data;                                             //initialize p

    for(i=0;i<10;i++)                                   //find the longest length of array
    {
        if(length<GetLength(*p))
            length=/*length<*/GetLength(*p);
    }
    for(i=0;i<CountArrayLength((int *)data);i++)        //from start to end circle
    {
        for(j=i+1;j<CountArrayLength((int *)data);j++)  //from i+1 to end
        {
            for(k=0;k<length;k++)                       //go through string
            {
                if(*(*(p+i)+k)>*(*(p+j)+k))             //data[i]>data[j], swap the two strings
                {
                    tmp=*(p+i);
                    *(p+i)=*(p+j);
                    *(p+j)=tmp;
                    break;
                }
                else if(*(*(p+i)+k)<*(*(p+j)+k))        //break this string
                    break;
                else if(*(*(p+i)+k)==*(*(p+j)+k))       //jump over this letter
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
    for(i=Factorial(length);i>0;i--)                    //number of all the possibilities
    {
        Exchange(&data[j],&data[j+1]);                  //swap 1st 2nd numbers
        j++;    if(j==length-1)j=0;                     //reach the end, go back to start        
        for(k=0;k<length;k++)                           //print the answers
        {
            if(k==0)                                    //if it's the first num of each roll
            {
                z++;
                printf("\nNo.%-3d: ",z);                //then print the No.
            }
            switch(type)                                //print the data by different parameters
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
    for(i=Factorial(length);i>0;i--)                    //number of all the possibilities
    {
        Exchange(&data[j],&data[j+1]);                  //swap 1st 2nd numbers
        j++;    if(j==length-1)j=0;                     //reach the end, go back to start
        for(k=0;k<length;k++)                           //print the answers
        {
            if(k==0)                                    //if it's the first num of each roll
            {
                z++;
                printf("\nNo.%-3d: ",z);                //then print the No.
            }
            switch(type)                                //print the data by different parameters
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
Function:None
Argument:None
Return  :None
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
Return  :None
*******************************************************/
void sayhello()
{
    printf("hello\n");
    getchar();
}

/*******************************************************
Function:None
Argument:None
Return  :None
*******************************************************/
void ptrsth()
{
    int (*p)[4];
    int score[][4]={{60,70,80,90},{56,89,67,88},{37,78,90,66}};
    p=score;
    printf("%d\n",sizeof(p[4]));
//  printf("%d\n",p);
//  printf("%d\n",p+1);
    getchar();
}

/*******************************************************
Function:None
Argument:None
Return  :None
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
Function:ThreeCardBrag() and cards relevant test.
Argument:None
Return  :None
*******************************************************/
void LANE20140414()
{
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
    
    
    Cards card_1st;
    Cards card_2nd;
    Cards card_3rd;
    
    times=ThreeCardBrag(&card_1st, &card_2nd, &card_3rd, Straight_Flush);
    printf("card 1: %-8s%2s\n",card_1st.suit_str,card_1st.point_str);
    printf("card 2: %-8s%2s\n",card_2nd.suit_str,card_2nd.point_str);
    printf("card 3: %-8s%2s\n",card_3rd.suit_str,card_3rd.point_str);
    printf("times:%d",times);
}

/*******************************************************
Function:None
Argument:None
Return  :None
*******************************************************/
void LANE0124()
{
    signed char t=0;
//  int i;
    t=t-4;
    t>>=1;

    printf("%d",t);
}

/*******************************************************
Function:None
Argument:None
Return  :None
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
Return  :None
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
Return  :None
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
Return  :None
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
    for the uncertain parameters functions study.
Argument:... *
Return  :None
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
    va_start(Valist_P,Para);            //va_start(), make Valist_P point to the Para
    while(Para!=0)
    {
        printf("%d\n",Para);
        Para=va_arg(Valist_P,int);      //va_arg(), make Valist_P point to the one after Para, and then return the value of Para
    }
    va_end(Valist_P); /* clean up when done */
}


/*******************************************************
Function:
    Another function for the uncertain parameters functions study.
Argument:... *
Return  :None
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
    char *p;
    wchar_t *sval;
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
                    sval = va_arg(ap, wchar_t *);
                    wprintf(L"%s", sval);
                    //for (sval = va_arg(ap, wchar_t *); *sval; sval++)
                    //{
                    //  putchar(*sval);
                    //}
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
    Another function for the uncertain parameters functions study.
Argument:... *
Return  :None
*******************************************************/
#if 0
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
#endif

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

/******************************************************/
bool findchar(char* string,char temp)
{
    int index=0;
    while(*string!='\0' &&*string++ !=temp  )index++;
    return index>GetLength(string)? false :true;
}
/******************************************************/

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

//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************

/*******************************************************
Function:Frame of count day in a year
Argument:None
Return  :None
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
Return  :bool
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
Return  :None
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