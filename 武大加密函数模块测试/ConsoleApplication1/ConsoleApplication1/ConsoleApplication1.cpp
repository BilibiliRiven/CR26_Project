// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
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

//�������ܣ�����Aֵ�����Bֵ�� ����Bֵ�����Aֵ
UINT Function1(UINT eax)
{
	//����
	//unsigned int eax = 0x5a221d5e;

	//����
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
		while (Var3 % 2 == 0) // ����Var3�϶����ܱ�����
		{
			Var3 >>= 1;

			if (Var5 % 2 == 0) //ֻ�����һ��
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
		Var1 = Var3; // ���˺�û��һ��

		while (Var0 % 2 == 0) // �м�����������ٴ�
		{
			Var0 >>= 1; 

			if (Var4 % 2 == 0) // �����Ķ����㣬�����1�Ͳ����������Ƕ������������ͬ
			{
				Var4 >>= 1;
			}
			else
			{
				//                 Var2 = Var4 <= 4 ? 0 : 1;
				//                 Var4 += 0x0FFFFFFFB;
				//                 Var4 = Uint64(Var2, Var4) >> 1;
				//                 Var2 >>= 1;
				Var4 = (Var4 + 0x0FFFFFFFB) >> 1; // ���ż������0
			}
		}

		if (Var1 > Var0) 
		{
			Var3 -= Var0; // ż��
			Var1 = Var3; // �ֿ������¿�ʼѭ��

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

	//return Uint64(Var3, Var5);  ����8�ֽڣ���ֻ�õ���4�ֽ�
	return Var5;
}
