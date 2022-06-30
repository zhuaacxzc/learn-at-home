#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define  GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}   //��ָ��� ���ַ������е�Ԫ�ظ���������Ϊ����������β�
int com = 0, dat = 0,err=0;

typedef struct
{
	int a;
	int b;
	int c;
} REVjudgement;

REVjudgement getrevjudge(int x, int y,int z)//�Խṹ�嶨�庯��������
{
	REVjudgement result;
	result.a = com;          //a������־ָ�� ��ָ���ҵ�ʱΪָ����������Ϊ0
	result.b = dat;          //b������־����   ��ָ��Ϊ�޲�ʱ������-1
	result.c = err;          //c������־ָ�����   ��ָ����ȷʱΪ0������ʱΪ20, ��RE:ERR;  ��ʱ����ֵΪ 0  0  20
	return result;
}



int find_string(char *strs[], char *str, int len)                             //�����ַ�������Ѱ��ָ�����ַ���
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

int judgement(char *p,int l)    //�ж�����һ��ָ��
{
	int i, max = 18, j = 0;
	char command[19];
	for (i = 0; i<l; i++)
	{
		command[i] = *(p + i);
	}
	command[i] = '\0';
	printf("%s\n", command);
	for (i = 0; i < max; i++)                                                   //ͨ���Ƿ��пո��ж��Ƿ��в���
	{
		if (command[i] == ' ')
		{
			j = i;
			break;
		}
	}
	if (j != 0)                                                                //�в��������
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
		if (i < 0)                                                            //û�ж�Ӧָ��
		{
			printf("ָ�����\r\n");
			err = 20;
			getrevjudge(0, 0, 0);
			return 0;
		}
		else                                                                  //�ҵ���Ӧָ�iֵ��Ϊָ�����б��е�˳�򣬴�1��ʼ
		{
			com = i;
		}


		for (i = 0; i < max; i++)                                             //�ҵ��ո�λ��
		{
			if (command[i] == ' ')
			{
				k = i + 1;
				break;
			}
		}
		for (i = 0; i < max; i++)                                             //�ҵ�����λ��
		{
			if (command[i] == ';')
			{
				m = i;
				break;
			}
		}

		for (i = 0; i < (m - k); i++)                                            //��������ȡ
		{
			data[i] = command[k + i];
		}
		data[m - k] = '\0';


		for (i = 0; data[i] != '\0'; i++)                                     //�����������Ƿ�ȫΪ����
		{
			if ((data[i] < '0') | (data[i] > '9'))
			{
				printf("ָ�����\r\n");
				com = 0;
				err = 20;
				getrev(0, 0, 0);
				return 0;
			}
			num = atoi(data);                                                  //���ַ�ת��Ϊint���͵���ֵ
		}
		dat = num;
		printf("ָ��Ϊ%d\r\n", com);
		getrevjudge(0,0,0);
	}
	else                                                                       //�޲��������
	{
		int i, len;
		char *commandsheet2[] = {" "," "," "," "," "," "," "," "," "," "," "," "," ", "SYS:SENDDATA;","SYS:DATAOK;","SYS:DATAERR;","SYS:STOP;","SYS:TEST;","RE:OK;","RE:ERR;","DAQ:START;",
			"DAQ:STARTMANUAL;","DAQ:STOPMANUAL;","DAQ:STARTMGP;","STA:SELFTESTERR;","STA:MOTORERR;","STA:CYLERR;","STA:DAQERR;",
			"STA:CYLERR2;","STA:DAQEND;","STA:CYLIN;","STA:CYLOUT;","TST:CYLIN;","TST:CYLOUT;","TST:MOTORRST;","TST:CYLCHECK;" };          //ָ���б�
		GET_ARRAY_LEN(commandsheet2, len);
		i = find_string(commandsheet2, command, len);
		if (i < 0)                                                            //û�ж�Ӧָ��
		{
			printf("ָ�����\r\n");
			err = 20;
			getrevjudge(0, 0, 0);
		}
		else                                                                  //�ҵ���Ӧָ�iֵ��Ϊָ�����б��е�˳�򣬴�1��ʼ
		{
			printf("ָ��Ϊ%d\r\n",i);
			com = i;
			dat = -1;
			getrevjudge(0, 0, 0);
		}
	}
	return 0;
}




