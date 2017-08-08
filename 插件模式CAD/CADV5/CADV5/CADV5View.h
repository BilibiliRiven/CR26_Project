
// CADV5View.h : CCADV5View 类的接口
//

#pragma once


class CCADV5View : public CView
{
protected: // 仅从序列化创建
	CCADV5View();
	DECLARE_DYNCREATE(CCADV5View)

// 特性
public:
	CCADV5Doc* GetDocument() const;

// 操作
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
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CCADV5View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // CADV5View.cpp 中的调试版本
inline CCADV5Doc* CCADV5View::GetDocument() const
   { return reinterpret_cast<CCADV5Doc*>(m_pDocument); }
#endif

