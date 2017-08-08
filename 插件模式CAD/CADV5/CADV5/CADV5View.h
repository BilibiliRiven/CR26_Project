
// CADV5View.h : CCADV5View ��Ľӿ�
//

#pragma once


class CCADV5View : public CView
{
protected: // �������л�����
	CCADV5View();
	DECLARE_DYNCREATE(CCADV5View)

// ����
public:
	CCADV5Doc* GetDocument() const;

// ����
public:
	enum CDA_STATE{
		NONE,
		PAINT,
		MOVE,
		ROTATION,
	}m_CadState;
	afx_msg void OnSetPattern();
	COLORREF  m_PenColor;
	COLORREF  m_BrushColor;
	int  m_PenStyle;
	int  m_BrushStyle;
	CList<ICR26Shape *, ICR26Shape *> m_ShapList;
	ICR26Shape *m_pCurrentShape;
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CCADV5View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // CADV5View.cpp �еĵ��԰汾
inline CCADV5Doc* CCADV5View::GetDocument() const
   { return reinterpret_cast<CCADV5Doc*>(m_pDocument); }
#endif

