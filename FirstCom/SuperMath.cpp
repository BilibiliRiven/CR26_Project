// SuperMath.cpp: implementation of the CSuperMath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SuperMath.h"

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
