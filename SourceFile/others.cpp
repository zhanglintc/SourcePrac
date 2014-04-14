#include "stdafx.h"
#include "headers.h"

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