#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define  GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}   //求指令长度 （字符数组中的元素个数），作为遍历数组的形参
int com = 0, dat = 0,err=0;

typedef struct
{
	int a;
	int b;
	int c;
} REVjudgement;

REVjudgement getrevjudge(int x, int y,int z)//以结构体定义函数的类型
{
	REVjudgement result;
	result.a = com;          //a用来标志指令 当指令找到时为指令数，否则为0
	result.b = dat;          //b用来标志参数   当指令为无参时，返回-1
	result.c = err;          //c用来标志指令错误   当指令正确时为0，错误时为20, 即RE:ERR;  此时返回值为 0  0  20
	return result;
}



int find_string(char *strs[], char *str, int len)                             //遍历字符串数组寻找指定的字符串
{
	int i = 1;
	while (i < len + 1) {
		if (strcmp(*strs, str) == 0) {
			break;
		}
		i++;
		strs++;
	}
	if (i == len + 1)
	{
		return -1;
	}
	return i;
}

int judgement(char *p,int l)    //判断是哪一条指令
{
	int i, max = 18, j = 0;
	char command[19];
	for (i = 0; i<l; i++)
	{
		command[i] = *(p + i);
	}
	command[i] = '\0';
	printf("%s\n", command);
	for (i = 0; i < max; i++)                                                   //通过是否含有空格判断是否含有参数
	{
		if (command[i] == ' ')
		{
			j = i;
			break;
		}
	}
	if (j != 0)                                                                //有参数的情况
	{
		int i, len, k, m=0, num = 0;
		char command1[16];
		char data[6];
		char *commandsheet1[] = { "SYS:R","SYS:MA","SYS:DAQSP","SYS:DAQEP","SYS:MGROUP","SYS:MPOINT","SYS:SENDDATA",
			"STA:TESTPOINT","TST:MOTORGP","TST:MOTORGN","TST:READIO","TST:WRITEIO", "TST:CLEARIO" };
		for (i = 0; i < j; i++)
		{
			command1[i] = command[i];
		}
		command1[j] = '\0';
		GET_ARRAY_LEN(commandsheet1, len);
		i = find_string(commandsheet1, command1, len);
		if (i < 0)                                                            //没有对应指令
		{
			printf("指令错误\r\n");
			err = 20;
			getrevjudge(0, 0, 0);
			return 0;
		}
		else                                                                  //找到对应指令，i值即为指令在列表中的顺序，从1开始
		{
			com = i;
		}


		for (i = 0; i < max; i++)                                             //找到空格位置
		{
			if (command[i] == ' ')
			{
				k = i + 1;
				break;
			}
		}
		for (i = 0; i < max; i++)                                             //找到结束位置
		{
			if (command[i] == ';')
			{
				m = i;
				break;
			}
		}

		for (i = 0; i < (m - k); i++)                                            //将参数提取
		{
			data[i] = command[k + i];
		}
		data[m - k] = '\0';


		for (i = 0; data[i] != '\0'; i++)                                     //检测参数部分是否全为数字
		{
			if ((data[i] < '0') | (data[i] > '9'))
			{
				printf("指令错误\r\n");
				com = 0;
				err = 20;
				getrev(0, 0, 0);
				return 0;
			}
			num = atoi(data);                                                  //将字符转换为int类型的数值
		}
		dat = num;
		printf("指令为%d\r\n", com);
		getrevjudge(0,0,0);
	}
	else                                                                       //无参数的情况
	{
		int i, len;
		char *commandsheet2[] = {" "," "," "," "," "," "," "," "," "," "," "," "," ", "SYS:SENDDATA;","SYS:DATAOK;","SYS:DATAERR;","SYS:STOP;","SYS:TEST;","RE:OK;","RE:ERR;","DAQ:START;",
			"DAQ:STARTMANUAL;","DAQ:STOPMANUAL;","DAQ:STARTMGP;","STA:SELFTESTERR;","STA:MOTORERR;","STA:CYLERR;","STA:DAQERR;",
			"STA:CYLERR2;","STA:DAQEND;","STA:CYLIN;","STA:CYLOUT;","TST:CYLIN;","TST:CYLOUT;","TST:MOTORRST;","TST:CYLCHECK;" };          //指令列表
		GET_ARRAY_LEN(commandsheet2, len);
		i = find_string(commandsheet2, command, len);
		if (i < 0)                                                            //没有对应指令
		{
			printf("指令错误\r\n");
			err = 20;
			getrevjudge(0, 0, 0);
		}
		else                                                                  //找到对应指令，i值即为指令在列表中的顺序，从1开始
		{
			printf("指令为%d\r\n",i);
			com = i;
			dat = -1;
			getrevjudge(0, 0, 0);
		}
	}
	return 0;
}




