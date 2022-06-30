#include<stdio.h>
#include <stdlib.h>
const char S1 = 0xFE;        //组头 若是组头改变从这里修改
const char S2 = 0xFD;
const char S3 = 0xFC;
const char S4 = 0xFB;

int a, b, c, d = 0;             //a, b, c 为结构体成员  暂定 d为测试用计数器参数
typedef struct
{
	int a;
	int b;
	int c;
} REVdatapack;

REVdatapack getrev(int x, int y, int z)//以结构体定义函数的类型
{
	REVdatapack result;
	result.a = a;
	result.b = b;
	result.c = c;          //c用来标志发送错误     若发送错误返回1  否则为0
	return result;
}


int sendata(unsigned char *p, int a)      //假设有一个发送函数，其返回值为是否发送成功
{
	int n = 0;
	return n;
}


int Datapackage(char *p, int l)   //打包函数 形参为数据所在的内存首地址及数据长度
{
	int packagenum, packageord, detect;                    //packagenum为需要打包的包数，packageord为第几个数据包,detect用来检测是否发送完毕
	if (l % 1432 == 0)                                     //对1432取余判断打包次数,若整除则就是需打包的个数，若不是整除，对于两个int类型的数，结果只保留小数部分，需要对结果加一
	{
		packagenum = l / 1432;
	}
	else
	{
		packagenum = l / 1432 + 1;
	}
	printf("要打包的个数为：%d \n", packagenum);
	unsigned char *package;                                    //缓存
	package = (unsigned char*)malloc(1440 * sizeof(char));     //动态分配内存
	package[0] = S1;                                           //添加组头
	package[1] = S2;
	package[2] = S3;
	package[3] = S4;


	for (packageord = 1; packageord < (packagenum + 1); packageord++)
	{
		int i, len, ord = 0;	                                          //len为数据长度，ord则是为了方便计算打包时，每个包裹开始数据的地址偏移（对于超过1个包的情况）
		printf("第%d个包裹：\n", packageord);
		unsigned char cha[4] = { packageord };                        //将组号（int 所以是四个字节）拆分成四个字节存放到数组中，高位在前
		cha[0] = (packageord & 0xFF000000) % 0x00FFFFFF;
		cha[1] = (packageord & 0x00FF0000) % 0x0000FFFF;
		cha[2] = (packageord & 0x0000FF00) % 0x000000FF;
		cha[3] = packageord & 0x000000FF;

		;		package[4] = cha[0];
		package[5] = cha[1];
		package[6] = cha[2];
		package[7] = cha[3];
		printf("%X  %X  %X  %X\n", package[4], package[5], package[6], package[7]);

		if (packageord == packagenum)                                  //数据长度  当不是最后一组时，长度肯定为1440，最后一组则为传入的数据长度减去以打包的数据长度再+8
		{
			len = l + 8 - (packagenum - 1) * 1432;
		}
		else
		{
			len = 1440;
		}
		printf("数据包的长度为：%d \n", len);
		for (i = 8; i < len; i++)                     //第一个包从第九个字节开始写入数据，余下的则需要计算地址偏移
		{
			ord = 1432 * (packageord - 1);   //因为packageord从1开始，所以减一
			package[i] = *(p + ord);
		}
		printf("%X  %X  %X  %X\n", package[29], package[35], package[67], package[16]);

		detect = sendata(package, len); //假设发送函数发送成功时返回0,发送失败返回1
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
	free(package);                  //释放动态分配的内存
	getrev(0, 0, 0);
	return 0;
}