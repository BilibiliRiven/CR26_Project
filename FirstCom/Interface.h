#if !defined(INTERFACE_H__29617E9C_0D37_4D93_BFAA_93BB7E31200F__INCLUDED_)
#define INTERFACE_H__29617E9C_0D37_4D93_BFAA_93BB7E31200F__INCLUDED_

#include <windows.h>


//com本质论

class IBase
{
public:
  virtual HRESULT QueryInterface(const GUID& riid, void **ppObject) = 0; //全球唯一标识符(GUID)
  virtual long AddRef() = 0; //引用计数
  virtual long Release() = 0;
};

// {D2150EF7-68F6-453c-A4C6-52E2A211880C}
static const GUID IID_IBase = 
{0xd2150ef7, 0x68f6, 0x453c, { 0xa4, 0xc6, 0x52, 0xe2, 0xa2, 0x11, 0x88, 0xc } };

//1.多重继承影响虚表
//2.虚析构影响虚表
//3.重载影响虚表顺序


//接口不变原则
class ISuperMath :public IBase
{
public:
  virtual HRESULT Add(long n1, long n2, long* result) = 0;
  virtual HRESULT Sub(long n1, long n2, long* result) = 0;
};

// {6634CF3C-62E4-4a53-B64E-F53F7F80F06D}
static const GUID IID_ISuperMath = 
{ 0x6634cf3c, 0x62e4, 0x4a53, { 0xb6, 0x4e, 0xf5, 0x3f, 0x7f, 0x80, 0xf0, 0x6d } };


HRESULT CreateObject(void **ppObject);
typedef HRESULT (*CREATE_OBJECT)(void **ppObject);

#endif
