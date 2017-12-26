// HSVDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Chapter1_LoadImg.h"
#include "HSVDlg.h"
#include "afxdialogex.h"
#include "ImgProcAlgorithm.h"

// CHSVDlg 对话框

IMPLEMENT_DYNAMIC(CHSVDlg, CDialogEx)

CHSVDlg::CHSVDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_HSV, pParent), m_pMedImage(NULL)
	, m_bIsLoad(false)
	, m_strPath(_T(""))
	, m_iH(0)
	, m_iS(0)
	, m_iV(0)
{

}

CHSVDlg::CHSVDlg(CString imagePath, CWnd* pParent /*= NULL*/)
	: CDialogEx(IDD_DIALOG_HSV, pParent), m_bIsLoad(FALSE), m_pMedImage(NULL)
{
	m_strPath = imagePath;
}

CHSVDlg::~CHSVDlg()
{
	if (m_pMedImage)
	{
		delete m_pMedImage;
	}
}

void CHSVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_SLIDER_H, m_iH);
	DDV_MinMaxInt(pDX, m_iH, 0, 360);
	DDX_Slider(pDX, IDC_SLIDER_S, m_iS);
	DDV_MinMaxInt(pDX, m_iS, 0, 100);
	DDX_Slider(pDX, IDC_SLIDER_V, m_iV);
	DDV_MinMaxInt(pDX, m_iV, 0, 100);
}


BEGIN_MESSAGE_MAP(CHSVDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_HSV_CANCEL, &CHSVDlg::OnBnClickedHsvCancel)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CHSVDlg::OnBnClickedButtonLoad)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_H, &CHSVDlg::OnNMCustomdrawSliderH)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_S, &CHSVDlg::OnNMCustomdrawSliderS)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_V, &CHSVDlg::OnNMCustomdrawSliderV)
END_MESSAGE_MAP()


// CHSVDlg 消息处理程序


void CHSVDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用
	CDialogEx::OnPaint();
	if (m_bIsLoad)
	{
		CWnd* pImgWnd = GetDlgItem(IDC_STATIC_HSV_PIC);
		CDC* pImgDC = pImgWnd->GetDC();
		CRect rect;
		pImgWnd->GetClientRect(&rect);
		m_pMedImage->SetToDC(*pImgDC, rect, (CPoint(0, 0)));
	}	
}


BOOL CHSVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CHSVDlg::OnBnClickedHsvCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(IDOK);
}


void CHSVDlg::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_strPath)
	{
		if (m_pMedImage)
		{
			delete m_pMedImage;
		}
		m_pMedImage = new CMedicalImg(m_strPath);
		CWnd* pImgWnd = GetDlgItem(IDC_STATIC_HSV_PIC);
		long imgHeight = abs(m_pMedImage->GetHeight());
		long imgWidth = m_pMedImage->GetWidth();
		SetWindowPos(NULL, 0, 0, imgWidth + 300, imgHeight + 20, SWP_NOZORDER | SWP_NOMOVE);
		pImgWnd->SetWindowPos(NULL, 0, 0, imgWidth, imgHeight, SWP_NOZORDER | SWP_NOMOVE);
		// 获取中心元素RGB的值
		int r = 0;
		int g = 0;
		int b = 0;
		m_pMedImage->GetPixelRGB(imgHeight / 2, imgWidth / 2, r, g, b);
		float h, s, v;
		CImgProcAlgorithm::RGB2HSV(r, g, b, h, s, v);
		m_iH = int(h) % 360;
		m_iS = int(s) % 100;
		m_iV = int(v) % 100;

		CWnd* pBtnWnd = GetDlgItem(IDC_HSV_CANCEL);
		pBtnWnd->SetWindowPos(NULL, imgWidth + 60, imgHeight - 60, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

		CWnd* pStatic1 = GetDlgItem(IDC_HSV_STATIC1);
		pStatic1->SetWindowPos(NULL, imgWidth + 30, 60, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		CSliderCtrl* pSliderH = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_H);
		pSliderH->SetWindowPos(NULL, imgWidth + 60, 60, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pSliderH->SetPos(int(h));

		CWnd* pStatic2 = GetDlgItem(IDC_HSV_STATIC2);
		pStatic2->SetWindowPos(NULL, imgWidth + 30, 100, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		CSliderCtrl* pSliderS = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_S);
		pSliderS->SetWindowPos(NULL, imgWidth + 60, 100, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pSliderS->SetPos(int(s));

		CWnd* pStatic3 = GetDlgItem(IDC_HSV_STATIC3);
		pStatic3->SetWindowPos(NULL, imgWidth + 30, 140, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		CSliderCtrl* pSliderV = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_V);
		pSliderV->SetWindowPos(NULL, imgWidth + 60, 140, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pSliderV->SetPos(int(v));

		CWnd* pBtnLoad = GetDlgItem(IDC_HSV_BUTTON_LOAD);
		pBtnLoad->SetWindowPos(NULL, imgWidth + 60, imgHeight - 100, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pBtnLoad->SetWindowTextW(_T("重新导入"));

		UpdateWindow();
		CDC* pImgDC = pImgWnd->GetDC();
		CRect rect;
		pImgWnd->GetClientRect(&rect);
		m_pMedImage->SetToDC(*pImgDC, rect, (CPoint(0, 0)));

		m_bIsLoad = TRUE;
	}
	else
	{
		AfxMessageBox(_T("数据不存在，请先打开图像"));
	}
}


void CHSVDlg::OnNMCustomdrawSliderH(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (m_bIsLoad)
	{
		int r = 0;
		int g = 0;
		int b = 0;
		int imgHeight = m_pMedImage->GetHeight();
		int imgWidth = m_pMedImage->GetWidth();
		m_pMedImage->GetPixelRGB(imgHeight / 2, imgWidth / 2, r, g, b);
		UpdateData();
		int r1, g1, b1;
		CImgProcAlgorithm::HSV2RGB(m_iH, m_iS, m_iV, r1, g1, b1);
		//char * p_imgBuffer = new char[m_pMedImage->GetBodySize()];
		//memset(p_imgBuffer, 0, m_pMedImage->GetBodySize());
		int deltaR = r1 - r;
		int deltaG = g1 - g;
		int deltaB = b1 - b;
		m_pMedImage->UpdateRGB((char *)m_pMedImage->GetBits(), deltaR, deltaG, deltaB);
		UpdateWindow();
		CWnd* pImgWnd = GetDlgItem(IDC_STATIC_HSV_PIC);
		CDC* pImgDC = pImgWnd->GetDC();
		CRect rect;
		pImgWnd->GetClientRect(&rect);
		m_pMedImage->SetToDC(*pImgDC, rect, (CPoint(0, 0)));
	}
	*pResult = 0;
}


void CHSVDlg::OnNMCustomdrawSliderS(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (m_bIsLoad)
	{
		int r = 0;
		int g = 0;
		int b = 0;
		int imgHeight = m_pMedImage->GetHeight();
		int imgWidth = m_pMedImage->GetWidth();
		m_pMedImage->GetPixelRGB(imgHeight / 2, imgWidth / 2, r, g, b);
		UpdateData();
		int r1, g1, b1;
		CImgProcAlgorithm::HSV2RGB(m_iH, m_iS, m_iV, r1, g1, b1);
		//char * p_imgBuffer = new char[m_pMedImage->GetBodySize()];
		//memset(p_imgBuffer, 0, m_pMedImage->GetBodySize());
		int deltaR = r1 - r;
		int deltaG = g1 - g;
		int deltaB = b1 - b;
		m_pMedImage->UpdateRGB((char *)m_pMedImage->GetBits(), deltaR, deltaG, deltaB);
		//UpdateWindow();
		CWnd* pImgWnd = GetDlgItem(IDC_STATIC_HSV_PIC);
		CDC* pImgDC = pImgWnd->GetDC();
		CRect rect;
		pImgWnd->GetClientRect(&rect);
		m_pMedImage->SetToDC(*pImgDC, rect, (CPoint(0, 0)));
	}
	*pResult = 0;
}


void CHSVDlg::OnNMCustomdrawSliderV(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (m_bIsLoad)
	{
		int r = 0;
		int g = 0;
		int b = 0;
		int imgHeight = m_pMedImage->GetHeight();
		int imgWidth = m_pMedImage->GetWidth();
		m_pMedImage->GetPixelRGB(imgHeight / 2, imgWidth / 2, r, g, b);
		UpdateData();
		int r1, g1, b1;
		CImgProcAlgorithm::HSV2RGB(m_iH, m_iS, m_iV, r1, g1, b1);
		//char * p_imgBuffer = new char[m_pMedImage->GetBodySize()];
		//memset(p_imgBuffer, 0, m_pMedImage->GetBodySize());
		int deltaR = r1 - r;
		int deltaG = g1 - g;
		int deltaB = b1 - b;
		m_pMedImage->UpdateRGB((char *)m_pMedImage->GetBits(), deltaR, deltaG, deltaB);
		CWnd* pImgWnd = GetDlgItem(IDC_STATIC_HSV_PIC);
		CDC* pImgDC = pImgWnd->GetDC();
		CRect rect;
		pImgWnd->GetClientRect(&rect);
		m_pMedImage->SetToDC(*pImgDC, rect, (CPoint(0, 0)));

	}
	*pResult = 0;
}
