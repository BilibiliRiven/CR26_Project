
// CADV5View.cpp : CCADV5View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CADV5.h"
#endif

#include "CADV5Doc.h"
#include "CADV5View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCADV5View

IMPLEMENT_DYNCREATE(CCADV5View, CView)

BEGIN_MESSAGE_MAP(CCADV5View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCADV5View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CCADV5View 构造/析构

CCADV5View::CCADV5View()
{
	// TODO:  在此处添加构造代码

}

CCADV5View::~CCADV5View()
{
}

BOOL CCADV5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCADV5View 绘制

void CCADV5View::OnDraw(CDC* /*pDC*/)
{
	CCADV5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CCADV5View 打印


void CCADV5View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCADV5View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCADV5View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CCADV5View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

void CCADV5View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCADV5View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCADV5View 诊断

#ifdef _DEBUG
void CCADV5View::AssertValid() const
{
	CView::AssertValid();
}

void CCADV5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCADV5Doc* CCADV5View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCADV5Doc)));
	return (CCADV5Doc*)m_pDocument;
}
#endif //_DEBUG


// CCADV5View 消息处理程序


void CCADV5View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	SetCapture();
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (PAINT == m_CadState && m_pFactory != NULL){
		ASSERT(m_pCurrentShape == NULL);
		m_pCurrentShape = m_pFactory->CreateShape();
		m_pCurrentShape->SetDrawAttrbuilt(m_iWidth, m_PenStyle, m_PenColor, m_BrushStyle, m_BrushColor);
		m_pCurrentShape->OnLButtonDownForDraw(nFlags, point);
	}
	else if (MOVE == m_CadState || ROTATION == m_CadState){
		POSITION pos = m_ShapList.GetHeadPosition();
		POSITION posTemp;

		IShape * pShapeTemp = NULL;
		while (pos){
			posTemp = pos;
			pShapeTemp = m_ShapList.GetNext(pos);
			if (pShapeTemp->OnLButtonDownForSelection(nFlags, point)){
				m_ShapList.RemoveAt(posTemp);
				m_pCurrentShape = pShapeTemp;
				m_ShapList.AddHead(m_pCurrentShape);
				break;
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CCADV5View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	ReleaseCapture();
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (PAINT == m_CadState){
		if (m_pCurrentShape == NULL){
			return;
		}
		ASSERT(m_pCurrentShape != NULL);
		m_pCurrentShape->OnLButtonUpForDraw(nFlags, point);
		// 保存在list中
		m_ShapList.AddHead(m_pCurrentShape);
		// 将p_CurrentShape设置为NULL;
		m_pCurrentShape = NULL;
		OutputDebugString(TEXT("鼠标弹起，图形以保存\t\n"));
		Invalidate(FALSE);
	}
	else if (MOVE == m_CadState){
		// 保存当前值
		//m_ShapList.AddHead(m_pCurrentShape);由于在222行之前已经保存完毕不需要再保存
		m_pCurrentShape = NULL;
		Invalidate(FALSE);
	}
	else if (ROTATION == m_CadState  && m_pCurrentShape != NULL){
		m_pCurrentShape = NULL;
		Invalidate(FALSE);
	}

	CView::OnLButtonUp(nFlags, point);
}
