// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h" 

#include <iostream>    
#include <boost/format.hpp>    
#include <boost/tokenizer.hpp>    
#include <boost/algorithm/string.hpp>    

int _tmain(int argc, _TCHAR* argv[])
{
	std::wcout.imbue(std::locale("chs"));
	//���ָ���ַ���    
	std::wstring strTag = _T("I Come from China");

	std::vector<std::wstring> vecSegTag;
	// boost::is_any_of�����൱�ڷָ������    
	boost::split(vecSegTag, strTag, boost::is_any_of(_T(" ,��")));

	for (size_t i = 0; i < vecSegTag.size(); i++)
	{
		std::wcout << vecSegTag[i] << std::endl;
	}

	vecSegTag.clear();
	std::wstring strTag2 = _T("�ҽ�С������,�������������Һܸ���");
	boost::split(vecSegTag, strTag2, boost::is_any_of(_T(" ,��")));

	for (size_t i = 0; i < vecSegTag.size(); i++)
	{
		std::wcout << vecSegTag[i] << std::endl;
	}
	CFileFind
	getchar();
	return 0;
}
