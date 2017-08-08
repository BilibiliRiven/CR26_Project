#pragma once
/*
* 如果差错找不到原因是由于我，将接口文件定义到CLine的dll项目中了，笑。
*/
class ICR26Shape:
	public CObject
{
	int m_nID;
public:
	//ICR26Shape();
	int SetID(int nID){ return m_nID = nID; }
	int GetID(){ return m_nID; }
	//virtual ~ICR26Shape();
	virtual TCHAR * const GetShapeName() = 0;
	virtual void OnLButtonDownForDraw(UINT nFlags, CPoint point) = 0;
	virtual void OnLButtonUpForDraw(UINT nFlags, CPoint point) = 0;
	virtual void OnMouseMoveForDraw(UINT nFlags, CPoint point) = 0;
	virtual void OnDraw(CDC* pDC) = 0;
	virtual void OnDrawSeleted(CDC* pDC) = 0;
	virtual BOOL OnLButtonDownForSelection(UINT nFlags, CPoint point) = 0;
	virtual void OnLButtonUpForSelection(UINT nFlags, CPoint point) = 0;
	virtual void OnLButtonDownForMove(UINT nFlags, CPoint point) = 0;
	virtual void OnLButtonUpForMove(UINT nFlags, CPoint point) = 0;
	virtual void MoveWithMouse(UINT nFlags, CPoint point) = 0;
	virtual void RotationWithMouse(UINT nFlags, CPoint point) = 0;
	virtual void Serialize(CArchive&) = 0;
	virtual void SetDrawAttrbuilt(int iWidth, int iPenStyle, COLORREF PenColor,
		int iBrushStyle, COLORREF BrushColor) = 0;

};

extern "C" __declspec(dllexport) ICR26Shape * CR26_CreateShape();

typedef ICR26Shape * (*CR26PFN_CREATE_SHAPE)();