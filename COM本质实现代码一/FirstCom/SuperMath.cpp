// SuperMath.cpp: implementation of the CSuperMath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SuperMath.h"
#include <boost/lexical_cast.hpp>
#include <iostream>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSuperMath::CSuperMath()
{

}

CSuperMath::~CSuperMath()
{

}

HRESULT CSuperMath::QueryInterface(const GUID& riid, void **ppObject)
{
  if (memcmp(&riid, &IID_IBase, sizeof(GUID)) == 0)
  {
    *ppObject = (IBase*)this;
  }
  else if (memcmp(&riid, &IID_ISuperMath, sizeof(GUID)) == 0)
  {
    *ppObject = (ISuperMath*)this;
  }
  else if (memcmp(&riid, &IID_ISuperMath2, sizeof(GUID)) == 0)
  {
    *ppObject = (ISuperMath2*)this;
  }
  else
    return E_NOINTERFACE;

  return S_OK;
}

long CSuperMath::AddRef()
{
  return S_OK;
}

long CSuperMath::Release()
{
  delete this;

  return S_OK;
}

HRESULT CSuperMath::Add(long n1, long n2, long* result)
{
  *result = n1 + n2;
  return S_OK;
}

HRESULT CSuperMath::Sub(long n1, long n2, long* result)
{
  *result = n1 - n2;
  return S_OK;
}

HRESULT CSuperMath::Multi(long n1, long n2, long * result){
	*result = n1 * n2;
	return S_OK;
}


CSuperString::CSuperString(){

}


CSuperString::~CSuperString(){

}


HRESULT CSuperString::QueryInterface(const GUID& riid, void **ppObject){
	if (memcmp(&riid, &IID_IBase, sizeof(GUID)) == 0){
		*ppObject = (IBase *)this;
		return S_OK;
	}
	else if (memcmp(&riid, &IID_ISuperString, sizeof(GUID)) == 0){
		*ppObject = (ISuperString *)this;
		return S_OK;
	}
	return S_OK;
}

long CSuperString::AddRef(){
	return S_OK;
}

long CSuperString::Release(){
	delete this;
	return S_OK;
}

HRESULT CSuperString::Str2n(TCHAR * pDest, int * pnNum){
	int nProcId = -1;
	try
	{
		nProcId = boost::lexical_cast<int>(pDest);
	}
	catch (boost::bad_lexical_cast& e)
	{
		return -1;
	}
	*pnNum = nProcId;
	return S_OK;
}