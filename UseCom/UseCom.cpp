// UseCom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../FirstCom/Interface.h"



int main(int argc, char* argv[])
{
  HRESULT hr;
  IBase* pObject = NULL;
  HMODULE hDll;
  
  hDll = LoadLibrary("../FirstCom/debug/FirstCom.dll");
  if (hDll == NULL)
    return 0;

  CREATE_OBJECT pfnCreateObj = (CREATE_OBJECT)GetProcAddress(hDll, "CreateObject");
  if (pfnCreateObj == NULL)
  {
    FreeLibrary(hDll);
    return 0;
  }

  hr = pfnCreateObj((void**)&pObject);
  if (hr != S_OK)
    return 0;

  //有没有xxx接口
  ISuperMath2 *pSuperMath = NULL;
  hr = pObject->QueryInterface(IID_ISuperMath2, (void**)&pSuperMath);
  if (hr != S_OK)
    return 0;

  long result;
  hr =pSuperMath->Multi(1, 2, &result);
  if (hr != S_OK)
    return 0;

  printf("1+2=%d\n", result);


  getchar();
	return 0;
}

