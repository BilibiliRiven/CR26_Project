// Line.h : Line DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CLineApp
// �йش���ʵ�ֵ���Ϣ������� Line.cpp
//

class CLineApp : public CWinApp
{
public:
	CLineApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};


class CLine :
	public ICR26Shape
{
	DECLARE_SERIAL(CLine)
	CPoint m_StartPt;
	CPoint m_EndPt;
	CPoint m_MovePt;
	int m_iDegree;
	int m_iRadius;
	CPoint m_ptCent;
	int m_iPenWidth;
	int m_PenStyle;
	int m_BrushStyle;
	COLORREF m_PenColor;
	COLORREF m_BrushColor;
public:
	CLine();
	virtual ~CLine();
	virtual TCHAR * const GetShapeName(){ return TEXT("ֱ��"); }
	virtual void OnLButtonDownForDraw(UINT nFlags, CPoint point);
	virtual void OnLButtonUpForDraw(UINT nFlags, CPoint point);
	virtual void OnMouseMoveForDraw(UINT nFlags, CPoint point);
	virtual void OnDraw(CDC* pDC);
	virtual void OnDrawSeleted(CDC* pDC);
	virtual BOOL OnLButtonDownForSelection(UINT nFlags, CPoint point);
	virtual void OnLButtonUpForSelection(UINT nFlags, CPoint point);
	virtual void OnLButtonDownForMove(UINT nFlags, CPoint point);
	virtual void OnLButtonUpForMove(UINT nFlags, CPoint point);
	virtual void MoveWithMouse(UINT nFlags, CPoint point);
	virtual void RotationWithMouse(UINT nFlags, CPoint point);
	virtual void Serialize(CArchive&);
	virtual void SetDrawAttrbuilt(int iWidth, int iPenStyle, COLORREF PenColor, int iBrushStyle, COLORREF BrushColor){
		m_iPenWidth = iWidth;
		m_PenStyle = iPenStyle;
		m_BrushStyle = iBrushStyle;
		m_PenColor = PenColor;
		m_BrushColor = BrushColor;
	}
};



ICR26Shape * CR26_CreateShape()
{
	return new CLine();
	//return NULL;
}
