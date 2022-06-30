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
	testa = getrevjudge(a, b, c);//调用函数返回值
	printf("%d  %d  %d\n", testa.a, testa.b, testa.c);


	char data[10000];                                  //自己定义数据
	int i;
	for (i = 0; i < 10000; i++)
	{
		data[i] = 0xAE;
	}
	int lb= 10000;                                      //数据长度
	Datapackage(data, lb);
	int d = 1, e = 1, f= 1;
	REVdatapack testb = getrev(d, e, f);                       //调用函数返回值
	printf("%d  %d  %d\n", testb.a, testb.b, testb.c);
	
	return 0;
}