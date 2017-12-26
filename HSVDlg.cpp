#include "stdafx.h"
#include "Chapter1_LoadImg.h"
#include "HSVDlg.h"
#include "afxdialogex.h"


IMPLEMENT_DYNAMIC(CHSVDlg, CDialogEx)

CHSVDlg::CHSVDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_HSV, pParent), m_pMedImage(NULL)
{

	EnableAutomation();

}

CHSVDlg::CHSVDlg(CString imagePath, CWnd* pParent /*= NULL*/)
{
	m_pMedImage = new CMedicalImg(imagePath);
}

CHSVDlg::~CHSVDlg()
{
	if (m_pMedImage)
	{
		delete m_pMedImage;
	}
}

void CHSVDlg::OnFinalRelease()
{

	CDialogEx::OnFinalRelease();
}

void CHSVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHSVDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()




BOOL CHSVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	

	return TRUE;  
}


void CHSVDlg::OnPaint()
{
	CPaintDC dc(this); 
	/*
	CWnd* pImgWnd = GetDlgItem(IDC_STATIC_HSV_PIC);
	CDC* pImgDC = pImgWnd->GetDC();
	CRect rect;
	pImgWnd->GetClientRect(&rect);
	CRect imgRect = CRect(0, 0, m_pMedImage->GetHeight(), m_pMedImage->GetWidth());
	m_pMedImage->StretchToDC(*pImgDC, rect, imgRect);
	*/
}
