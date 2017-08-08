
// CADV5View.cpp : CCADV5View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCADV5View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CCADV5View ����/����

CCADV5View::CCADV5View()
{
	// TODO:  �ڴ˴���ӹ������

}

CCADV5View::~CCADV5View()
{
}

BOOL CCADV5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCADV5View ����

void CCADV5View::OnDraw(CDC* /*pDC*/)
{
	CCADV5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CCADV5View ��ӡ


void CCADV5View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCADV5View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCADV5View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCADV5View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
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


// CCADV5View ���

#ifdef _DEBUG
void CCADV5View::AssertValid() const
{
	CView::AssertValid();
}

void CCADV5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCADV5Doc* CCADV5View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCADV5Doc)));
	return (CCADV5Doc*)m_pDocument;
}
#endif //_DEBUG


// CCADV5View ��Ϣ�������


void CCADV5View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetCapture();
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ReleaseCapture();
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (PAINT == m_CadState){
		if (m_pCurrentShape == NULL){
			return;
		}
		ASSERT(m_pCurrentShape != NULL);
		m_pCurrentShape->OnLButtonUpForDraw(nFlags, point);
		// ������list��
		m_ShapList.AddHead(m_pCurrentShape);
		// ��p_CurrentShape����ΪNULL;
		m_pCurrentShape = NULL;
		OutputDebugString(TEXT("��굯��ͼ���Ա���\t\n"));
		Invalidate(FALSE);
	}
	else if (MOVE == m_CadState){
		// ���浱ǰֵ
		//m_ShapList.AddHead(m_pCurrentShape);������222��֮ǰ�Ѿ�������ϲ���Ҫ�ٱ���
		m_pCurrentShape = NULL;
		Invalidate(FALSE);
	}
	else if (ROTATION == m_CadState  && m_pCurrentShape != NULL){
		m_pCurrentShape = NULL;
		Invalidate(FALSE);
	}

	CView::OnLButtonUp(nFlags, point);
}
