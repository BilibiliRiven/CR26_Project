// Line.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "Line.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CLineApp

BEGIN_MESSAGE_MAP(CLineApp, CWinApp)
END_MESSAGE_MAP()


// CLineApp ����

CLineApp::CLineApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CLineApp ����

CLineApp theApp;


// CLineApp ��ʼ��

BOOL CLineApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}



// �����￪ʼCLine��ʵ��
CLine::CLine()
{
}


CLine::~CLine()
{
}



void CLine::OnLButtonDownForDraw(UINT nFlags, CPoint point){
	m_StartPt = m_EndPt = point;
};
void CLine::OnLButtonUpForDraw(UINT nFlags, CPoint point){
	m_EndPt = point;
	m_MovePt = point;
	m_ptCent.x = (m_StartPt.x + m_EndPt.x) / 2;
	m_ptCent.y = (m_StartPt.y + m_EndPt.y) / 2;

	int x, y;
	x = m_StartPt.x - m_EndPt.x;
	y = m_StartPt.y - m_EndPt.y;
	m_iRadius = sqrt(x*1.0*x + y*y) / 2.0;
};
void CLine::OnMouseMoveForDraw(UINT nFlags, CPoint point){
	m_EndPt = point;
	m_MovePt = point;
	m_ptCent.x = (m_StartPt.x + m_EndPt.x) / 2;
	m_ptCent.y = (m_StartPt.y + m_EndPt.y) / 2;

	int x, y;
	x = m_StartPt.x - m_EndPt.x;
	y = m_StartPt.y - m_EndPt.y;
	m_iRadius = sqrt(x*1.0*x + y*y) / 2.0;
}

void CLine::OnDraw(CDC* pDC){
	CPen pen(m_PenStyle, m_iPenWidth, m_PenColor);
	pDC->SelectObject(pen);

	LOGBRUSH logbrush;
	logbrush.lbStyle = m_BrushStyle;
	logbrush.lbColor = m_BrushColor;
	CBrush brush;
	brush.CreateBrushIndirect(&logbrush);
	pDC->SelectObject(brush);




	pDC->MoveTo(m_StartPt);
	pDC->LineTo(m_EndPt);

};


void CLine::OnDrawSeleted(CDC* pDC){
	static int i = 0;
	if (0 == i){
		CPen pen(PS_DOT, 1, RGB(0, 0, 0));
		pDC->SelectObject(pen);

		LOGBRUSH logbrush;
		logbrush.lbStyle = m_BrushStyle;
		logbrush.lbColor = m_BrushColor;
		CBrush brush;
		brush.CreateBrushIndirect(&logbrush);
		pDC->SelectObject(brush);

		pDC->MoveTo(m_StartPt);
		pDC->LineTo(m_EndPt);
		++i;
	}
	else{
		CPen pen(PS_DASHDOT, 1, RGB(0, 0, 0));
		pDC->SelectObject(pen);

		LOGBRUSH logbrush;
		logbrush.lbStyle = m_BrushStyle;
		logbrush.lbColor = m_BrushColor;
		CBrush brush;
		brush.CreateBrushIndirect(&logbrush);
		pDC->SelectObject(brush);

		pDC->MoveTo(m_StartPt);
		pDC->LineTo(m_EndPt);
		i = 0;
	}


};

/*!
*  @brief �жϵ�ǰ��굥�����Ƿ�ѡ���߶�
*
*  @param [in]p  ��ǰ��굥��������
*  @param [in]p1 ֱ�ߵ�һ���˵������
*  @param [in]p2 ֱ�ߵ���һ���˵������
*  @param [in]dbLimit ѡȡ����ֵ
*  @return �Ƿ�ѡ�С�TRUEΪѡ�У�FALSE��ʾû��ѡ�С�
*/
BOOL CLine::OnLButtonDownForSelection(UINT nFlags, CPoint point){
	m_MovePt = point;

	double x = point.x - m_StartPt.x;
	double y = point.y - m_StartPt.y;

	double a = m_EndPt.x - m_StartPt.x;
	double b = m_EndPt.y - m_StartPt.y;
	double c = sqrt(a*a + b*b);

	double sin_a = b / c;
	double cos_a = a / c;

	double chx = x*cos_a + y*sin_a;
	double chy = -x*sin_a + y*cos_a;

	if (fabs(chy) < 2 && (chx >= 0 && chx <= c))
		return TRUE;
	return FALSE;
};
void CLine::OnLButtonUpForSelection(UINT nFlags, CPoint point){
}
void CLine::OnLButtonDownForMove(UINT nFlags, CPoint point){
	m_MovePt = point;
};

void CLine::OnLButtonUpForMove(UINT nFlags, CPoint point){
};

void CLine::MoveWithMouse(UINT nFlags, CPoint point){
	int x = point.x - m_MovePt.x;
	int y = point.y - m_MovePt.y;
	m_StartPt.x += x;
	m_StartPt.y += y;

	m_EndPt.x += x;
	m_EndPt.y += y;

	m_ptCent.x = (m_StartPt.x + m_EndPt.x) / 2;
	m_ptCent.y = (m_StartPt.y + m_EndPt.y) / 2;
	m_MovePt = point;
};

void CLine::RotationWithMouse(UINT nFlags, CPoint point){


	int x = point.x - m_ptCent.x;
	int y = point.y - m_ptCent.y;
	double pi = 3.1415926535;
	m_iDegree = atan2(y*1., x*1.) * 180 / pi;

	m_StartPt.x = m_ptCent.x + m_iRadius*cos(m_iDegree*1.0*pi / 180);
	m_StartPt.y = m_ptCent.y + m_iRadius*sin(m_iDegree*1.0*pi / 180);

	m_EndPt.x = m_ptCent.x - m_iRadius*cos(m_iDegree*1.0 *pi / 180);
	m_EndPt.y = m_ptCent.y - m_iRadius*sin(m_iDegree*1.0*pi / 180);
}



void CLine::Serialize(CArchive& ar){

	if (ar.IsStoring()){
		ar << m_StartPt << m_EndPt << m_ptCent << m_iRadius << m_iDegree;
		ar << m_iPenWidth << m_PenStyle << m_BrushStyle << m_PenColor << m_BrushColor;
	}
	else{
		ar >> m_StartPt >> m_EndPt >> m_ptCent >> m_iRadius >> m_iDegree;
		ar >> m_iPenWidth >> m_PenStyle >> m_BrushStyle >> m_PenColor >> m_BrushColor;
	}

}
IMPLEMENT_SERIAL(CLine, CObject, 1)

