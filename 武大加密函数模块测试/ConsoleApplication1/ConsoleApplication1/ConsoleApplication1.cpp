// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Windows.h"
UINT Function1(UINT eax);
int _tmain(int argc, _TCHAR* argv[])
{
	for (UINT i = 0; i < 0xffffffff; ++i){
		printf("f(%x)=%x\r\n", i, Function1(i));
	}
	return 0;
}

//函数功能：输入A值，输出B值； 输入B值则输出A值
UINT Function1(UINT eax)
{
	//参数
	//unsigned int eax = 0x5a221d5e;

	//变量
	UINT Var0 = eax;
	UINT Var1 = 0x0FFFFFFFB;
	UINT Var2 = eax;
	UINT Var3 = 0x0FFFFFFFB;    //edx
	__int64 Var4 = 1;
	__int64 Var5 = 0;              //eax

	if (Var2 == 0)
	{
		return 0;
	}

	while (Var0 != 0)
	{
		while (Var3 % 2 == 0) // 由于Var3肯定不能被整除
		{
			Var3 >>= 1;

			if (Var5 % 2 == 0) //只会进来一次
			{
				Var5 >>= 1;
			}
			else
			{
				//                 Var2 = Var5 <= 4 ? 0 : 1;
				//                 Var5 += 0x0FFFFFFFB;
				//                 Var5 = Uint64(Var2, Var5) >> 1;
				//                 Var2 >>= 1;
				Var5 = (Var5 + 0x0FFFFFFFB) >> 1;

			}
		}
		Var1 = Var3; // 做了和没做一样

		while (Var0 % 2 == 0) // 有几个零进来多少次
		{
			Var0 >>= 1; 

			if (Var4 % 2 == 0) // 丢掉的都是零，如果是1就不丢掉，凡是丢掉的情况都相同
			{
				Var4 >>= 1;
			}
			else
			{
				//                 Var2 = Var4 <= 4 ? 0 : 1;
				//                 Var4 += 0x0FFFFFFFB;
				//                 Var4 = Uint64(Var2, Var4) >> 1;
				//                 Var2 >>= 1;
				Var4 = (Var4 + 0x0FFFFFFFB) >> 1; // 变成偶数丢掉0
			}
		}

		if (Var1 > Var0) 
		{
			Var3 -= Var0; // 偶数
			Var1 = Var3; // 又可以重新开始循环

			if (Var5 >= Var4)
			{
				Var5 -= Var4;
			}
			else
			{
				Var2 = 0x0FFFFFFFB - Var4;
				Var5 += Var2;
			}
		}
		else
		{
			Var0 -= Var3;

			if (Var4 >= Var5)
			{
				Var4 -= Var5;
			}
			else
			{
				Var3 = 0x0FFFFFFFB - Var5;
				Var4 += Var3;
			}

			Var3 = Var1;
		}

		if (Var3 == 0)
		{
			break;
		}
	}

	if (Var3 != 1)
	{
		if (Var0 == 1)
		{
			Var5 &= Var4;
		}
		else
		{
			Var5 = 0;
		}
	}

	//return Uint64(Var3, Var5);  返回8字节，但只用到低4字节
	return Var5;
}
