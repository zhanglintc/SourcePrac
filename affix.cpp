#include "stdafx.h"
#include "stdio.h"
#include "functions.h"

/*******************************************************
�@�\:return command and two parameters
����:char, char, char
�߂�l:�Ȃ� 
*******************************************************/
void GetCommand(char command[COMMAND_STR_LEN], char para_1st[COMMAND_STR_LEN], char para_2nd[COMMAND_STR_LEN])
{
	int		input_loc=0;									//cursor of input word
	int		current_loc=0;									//cursor of command and parameter
	char	input[INPUT_STRING_LEN];						//input word string

	memset(input,' ',sizeof(input));												//initialize input
	memset(command,'\0',COMMAND_STR_LEN);											//initialize command
	memset(para_1st,'\0',COMMAND_STR_LEN);											//initialize parameter 1st
	memset(para_2nd,'\0',COMMAND_STR_LEN);											//initialize parameter 2nd

	gets(input);																	//get the input
	input[INPUT_STRING_LEN-1]='\0';													//set the last one as \0
//-------------------------------------------------------------------------------------------------------------
	/*
	when no parameter, the end of input command is '\0',
	otherwise the end of input command is ' ',
	no matter in what case, load the whole things before ' ',

	1.no para:load the whole word with '\0'.
	2.with para:load the whole word with no '\0', 
	but we add the '\0' outside of this function.

	so, on matter in what case, we can count the 
	number of letters correctly.
	*/
	current_loc=0;																	//current loc clean. clean before load
	while(input[input_loc]!=' ')													//load the info to command
	{
		command[current_loc]=input[input_loc];
		current_loc++;
		input_loc++;
	}
	while(input[input_loc]==' '&&input[input_loc]!='\0')							//jump over the space
	{
		input_loc++;
	}
//-------------------------------------------------------------------------------------------------------------
	
	//add the '\0' judge in case of the end of the whole input string
	//from here, it can be the last para
	current_loc=0;																	//current loc clean. clean before load
	while(input[input_loc]!='\0'&&input[input_loc]!=' ')							//load the inft to para_1st
	{
		para_1st[current_loc]=input[input_loc];
		current_loc++;
		input_loc++;
	}
	while(input[input_loc]==' '&&input[input_loc]!='\0')							//jump over the space
	{
		input_loc++;
	}
//-------------------------------------------------------------------------------------------------------------

	//add the '\0' judge in case of the end of the whole input string
	//from here, it can be the last para

	current_loc=0;																	//current loc clean. clean before load
	while(input[input_loc]!='\0'&&input[input_loc]!=' ')							//load the inft to para_2nd
	{
		para_2nd[current_loc]=input[input_loc];
		current_loc++;
		input_loc++;
	}
}

/*******************************************************
�@�\:�����o��
����:int ,char ,char
�߂�l:�Ȃ�
*******************************************************/
void getbits(int value,char n1,char n2)
{
	//                ��o�ʐ�   �E�ڈʐ�
	value&=(~(65535<<(n2-n1+1))<<(15-n2));
	value>>=(15-n2);
	printf("%d",value);
}

/*******************************************************
�@�\:�����񒷂𓾂�
����:char []
�߂�l:int
*******************************************************/
//get length of in put string
int GetLength(char data[])
{
	int i=0;
	while(*(data+i)!='\0')
	{
		i++;
	}
	return i;
}

/*******************************************************
�@�\:�������Int�ύX
����:char *,int
�߂�l:int
*******************************************************/
int String2Int(char *data,int length)
{
	int ret=0;
	//for(int i=0;i<length;i++)
	//{
	//	if(*(data+i)<48||*(data+i)>57)return -1;
	//}
	for(int i=length-1;i>=0;i--)
	{
		ret+=((*(data+length-1-i)-48)*((int)pow(10.0,(int)i)));
	}
	return ret;
}

/*******************************************************
�@�\:�������Int�ύX
����:char []
�߂�l:int
*******************************************************/
//return value of string,-1 when not valid
int String2Int(char data[100])
{
	int ret=0;
	int i=0;
	for(i=0;i<GetLength(data);i++)
	{
		if(data[i]<48||data[i]>57)return -1;
	}
	for(i=GetLength(data)-1;i>=0;i--)
	{
		ret+=((data[GetLength(data)-1-i]-48)*((int)pow(10.0,(int)i)));
	}
	return ret;
}

/*******************************************************
�@�\:swap the two data
����:char *, char *
�߂�l:�Ȃ�
*******************************************************/
void swap(char *a, char *b) 
{     
    int m;     
    m = *a;     
    *a = *b;     
    *b = m; 
} 

/*******************************************************
�@�\:�����_���Ȑ����o��
����:data�F�͈�min�A�͈�max	 
�߂�l:�Ȃ�
*******************************************************/
int randnum(int min,int max)
{
	if(max<min)Exchange(&min,&max);
	int i=0;
	int randnum=0;
	//srand((unsigned)time(NULL));			//seed of the randdom number
											//always ues it out of loop
											//not here	
	randnum=rand()%(max-min+1)+min;
	return randnum;
}

/*******************************************************
�@�\:�O�����
����:�O��
	 �㐔
�߂�l:�Ȃ�
*******************************************************/
void Exchange(char *a,char *b)
{
	char tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
}

/*******************************************************
�@�\:�O�����
����:�O��
	 �㐔
�߂�l:�Ȃ�
*******************************************************/
void Exchange(int *a,int *b)
{
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
}

/*******************************************************
�@�\:�K��v�Z
����:int
	 data:N!��N
�߂�l:ret
*******************************************************/
int Factorial(int data)
{
    int i,ret=data;
    for(i=data-1;i>0;i--)
    {
        ret*=i;
    }
    return ret;
}

/*******************************************************
�@�\:count length of array. elements of array must 
be pointer or int or char or something length less 
than 4. arr is a pointer, point to int, length 4.
length of pointer is 4, too. thus this function 
can count an array which elements are pointers.
����:int *
�߂�l:length
*******************************************************/
int CountArrayLength(int *arr)				//point to 4 length datas
{
	int i=0;
	for(i=0;*(arr+i);i++);					//if arr[i] contains things, i++
	return i;
}
