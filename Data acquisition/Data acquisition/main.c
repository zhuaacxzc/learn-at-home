#include <stdio.h>
#include <judgement.h>
#include <Datapack.h>
int main()
{
	char s[] = "SYS:DAQEP 58;";
	int la = 13;
	char* p;
	REVjudgement testa;
	p = s;
	judgement(p, la);
	int a = 1, b = 1, c = 1;
	testa = getrevjudge(a, b, c);//���ú�������ֵ
	printf("%d  %d  %d\n", testa.a, testa.b, testa.c);


	char data[10000];                                  //�Լ���������
	int i;
	for (i = 0; i < 10000; i++)
	{
		data[i] = 0xAE;
	}
	int lb= 10000;                                      //���ݳ���
	Datapackage(data, lb);
	int d = 1, e = 1, f= 1;
	REVdatapack testb = getrev(d, e, f);                       //���ú�������ֵ
	printf("%d  %d  %d\n", testb.a, testb.b, testb.c);
	
	return 0;
}