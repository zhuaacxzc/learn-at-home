#include<stdio.h>
#include <stdlib.h>
const char S1 = 0xFE;        //��ͷ ������ͷ�ı�������޸�
const char S2 = 0xFD;
const char S3 = 0xFC;
const char S4 = 0xFB;

int a, b, c, d = 0;             //a, b, c Ϊ�ṹ���Ա  �ݶ� dΪ�����ü���������
typedef struct
{
	int a;
	int b;
	int c;
} REVdatapack;

REVdatapack getrev(int x, int y, int z)//�Խṹ�嶨�庯��������
{
	REVdatapack result;
	result.a = a;
	result.b = b;
	result.c = c;          //c������־���ʹ���     �����ʹ��󷵻�1  ����Ϊ0
	return result;
}


int sendata(unsigned char *p, int a)      //������һ�����ͺ������䷵��ֵΪ�Ƿ��ͳɹ�
{
	int n = 0;
	return n;
}


int Datapackage(char *p, int l)   //������� �β�Ϊ�������ڵ��ڴ��׵�ַ�����ݳ���
{
	int packagenum, packageord, detect;                    //packagenumΪ��Ҫ����İ�����packageordΪ�ڼ������ݰ�,detect��������Ƿ������
	if (l % 1432 == 0)                                     //��1432ȡ���жϴ������,����������������ĸ�������������������������int���͵��������ֻ����С�����֣���Ҫ�Խ����һ
	{
		packagenum = l / 1432;
	}
	else
	{
		packagenum = l / 1432 + 1;
	}
	printf("Ҫ����ĸ���Ϊ��%d \n", packagenum);
	unsigned char *package;                                    //����
	package = (unsigned char*)malloc(1440 * sizeof(char));     //��̬�����ڴ�
	package[0] = S1;                                           //�����ͷ
	package[1] = S2;
	package[2] = S3;
	package[3] = S4;


	for (packageord = 1; packageord < (packagenum + 1); packageord++)
	{
		int i, len, ord = 0;	                                          //lenΪ���ݳ��ȣ�ord����Ϊ�˷��������ʱ��ÿ��������ʼ���ݵĵ�ַƫ�ƣ����ڳ���1�����������
		printf("��%d��������\n", packageord);
		unsigned char cha[4] = { packageord };                        //����ţ�int �������ĸ��ֽڣ���ֳ��ĸ��ֽڴ�ŵ������У���λ��ǰ
		cha[0] = (packageord & 0xFF000000) % 0x00FFFFFF;
		cha[1] = (packageord & 0x00FF0000) % 0x0000FFFF;
		cha[2] = (packageord & 0x0000FF00) % 0x000000FF;
		cha[3] = packageord & 0x000000FF;

		;		package[4] = cha[0];
		package[5] = cha[1];
		package[6] = cha[2];
		package[7] = cha[3];
		printf("%X  %X  %X  %X\n", package[4], package[5], package[6], package[7]);

		if (packageord == packagenum)                                  //���ݳ���  ���������һ��ʱ�����ȿ϶�Ϊ1440�����һ����Ϊ��������ݳ��ȼ�ȥ�Դ�������ݳ�����+8
		{
			len = l + 8 - (packagenum - 1) * 1432;
		}
		else
		{
			len = 1440;
		}
		printf("���ݰ��ĳ���Ϊ��%d \n", len);
		for (i = 8; i < len; i++)                     //��һ�����ӵھŸ��ֽڿ�ʼд�����ݣ����µ�����Ҫ�����ַƫ��
		{
			ord = 1432 * (packageord - 1);   //��Ϊpackageord��1��ʼ�����Լ�һ
			package[i] = *(p + ord);
		}
		printf("%X  %X  %X  %X\n", package[29], package[35], package[67], package[16]);

		detect = sendata(package, len); //���跢�ͺ������ͳɹ�ʱ����0,����ʧ�ܷ���1
		d++;
		printf("%d\n", d);
		if (detect != 0)
		{
			a = 0, b = 0;
			c = 1;
		}
		else
		{
			a = 0, b = 0, c = 0;
		}

	}
	free(package);                  //�ͷŶ�̬������ڴ�
	getrev(0, 0, 0);
	return 0;
}