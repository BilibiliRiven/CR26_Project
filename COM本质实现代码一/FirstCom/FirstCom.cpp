// FirstCom.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "SuperMath.h"


HRESULT CreateObject(void **ppObject)
{
  *ppObject = new CSuperMath();
  return S_OK;
}

HRESULT CreateObject2(void **ppObject)
{
	*ppObject = new CSuperString();
	return S_OK;
}


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

