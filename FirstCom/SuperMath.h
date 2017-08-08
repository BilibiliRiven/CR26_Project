// SuperMath.h: interface for the CSuperMath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUPERMATH_H__A2E51150_9CCA_4B4B_80A3_04FF5B0D5EB0__INCLUDED_)
#define AFX_SUPERMATH_H__A2E51150_9CCA_4B4B_80A3_04FF5B0D5EB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Interface.h"

class CSuperMath : public ISuperMath  
{
public:
	CSuperMath();
	~CSuperMath();
  virtual HRESULT QueryInterface(const GUID& riid, void **ppObject);
  virtual long AddRef(); //引用计数
  virtual long Release();
  virtual HRESULT Add(long n1, long n2, long* result);
  virtual HRESULT Sub(long n1, long n2, long* result);
};

#endif // !defined(AFX_SUPERMATH_H__A2E51150_9CCA_4B4B_80A3_04FF5B0D5EB0__INCLUDED_)
