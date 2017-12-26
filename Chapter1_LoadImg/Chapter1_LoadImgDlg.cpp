/*********************************************************************************************************
* 模块名称: Chapter1_LoadImgDlg.c
* 摘    要: MVC架构的中心控制器
* 当前版本: 1.0.0
* 作    者: 秦陈陈
* 完成日期: 2017年12月20日
* 内    容: 主对话框，作为MVC架构的控制器
* 注    意: 所有的
**********************************************************************************************************
* 取代版本:
* 作    者:
* 完成日期:
* 修改内容:
* 修改文件:
*********************************************************************************************************/


/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "stdafx.h"
#include "Chapter1_LoadImg.h"
#include "Chapter1_LoadImgDlg.h"
#include "afxdialogex.h"
#include "ImgProcAlgorithm.h"
#include "HistDlg.h"
#include "HSVDlg.h"

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/*********************************************************************************************************
*                                              内部变量
*********************************************************************************************************/
static UINT BASED_CODE indicators[] = {
	ID_INDICATOR_TIME,
	ID_INDICATOR_POS,
	ID_INDICATOR_PIXEL,
	ID_INDICATOR_HSV
};


/*********************************************************************************************************
*                                              内部类定义
*********************************************************************************************************/
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


/*********************************************************************************************************
*                                              类成员函数实现
*********************************************************************************************************/

/*********************************************************************************************************
* 类名称:	CChapter1_LoadImgDlg
* 函数名称:	CChapter1_LoadImgDlg
* 函数权限: Public
* 函数功能: 构造函数, 初始化ICON
* 输入参数: pParent: CWnd *, 父窗口句柄
* 输出参数: void
* 返 回 值: void
* 注    意: 
*********************************************************************************************************/
CChapter1_LoadImgDlg::CChapter1_LoadImgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChapter1_LoadImgDlg::IDD, pParent), m_pMedImage(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	/*初始化内部变量*/
}

/*********************************************************************************************************
* 类名称:	CChapter1_LoadImgDlg
* 函数名称:	DoDataExchange
* 函数权限: Private
* 函数功能: 空间与父窗口进行数据交换
* 输入参数: pDX: CDataExchange*, 交换的数据指针
* 输出参数: void
* 返 回 值: void
* 注    意:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PIC, m_picControl);
}

/*********************************************************************************************************
* 函数名称:	BEGIN_MESSAGE_MAP
* 函数功能: 映射控件和响应消息函数
* 输入参数: CChapter1_LoadImgDlg, CDialogEx
* 输出参数: void
* 返 回 值: void
* 注    意:
*********************************************************************************************************/
BEGIN_MESSAGE_MAP(CChapter1_LoadImgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CChapter1_LoadImgDlg::OnBnClickedButtonClose)
	ON_MESSAGE(WM_SHOW_POS, &CChapter1_LoadImgDlg::OnShowPos) 
	ON_COMMAND(ID_OPEN, &CChapter1_LoadImgDlg::OnOpenImage)
	ON_COMMAND(ID_SAVE, &CChapter1_LoadImgDlg::OnSave)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_COMMAND(ID_HSV_ADJUST, &CChapter1_LoadImgDlg::OnHsvAdjust)
END_MESSAGE_MAP()

/*********************************************************************************************************
* 类名称:	CChapter1_LoadImgDlg
* 函数名称:	OnInitDialog
* 函数权限: Protected
* 函数功能: 初始化消息响应，在这里初始化所有空间
* 输入参数: pDX: CDataExchange*, 交换的数据指针
* 输出参数: void
* 返 回 值: void
* 注    意:
*********************************************************************************************************/
BOOL CChapter1_LoadImgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.
	/*初始化菜单*/
	m_ctrMenu.LoadMenu(IDR_MENU1);
	SetMenu(&m_ctrMenu);
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	/*设置状态栏*/
	m_wndStatusBar.Create(this);
	m_wndStatusBar.SetIndicators(indicators, 4);
	CRect rect;
	GetClientRect(&rect);
	m_wndStatusBar.SetPaneInfo(0, ID_INDICATOR_TIME, SBPS_STRETCH, 0);
	m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_POS, SBPS_STRETCH, 0);
	m_wndStatusBar.SetPaneInfo(2, ID_INDICATOR_PIXEL, SBPS_STRETCH, 0);
	m_wndStatusBar.SetPaneInfo(3, ID_INDICATOR_HSV, SBPS_STRETCH, 0);
	m_wndStatusBar.GetStatusBarCtrl().SetBkColor(RGB(250, 180, 56));
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, AFX_IDW_CONTROLBAR_FIRST);
	/*设置定时器*/
	SetTimer(1, 1000, NULL);


	return TRUE;  // return TRUE  unless you set the focus to a control
}


/*********************************************************************************************************
* 类名称:	CChapter1_LoadImgDlg
* 函数名称:	OnSysCommand
* 函数权限: Private
* 函数功能: 响应系统消息
* 输入参数: nID: UINT, 资源分配符；lParam: LPARAM, 长指针
* 输出参数: void
* 返 回 值: void
* 注    意:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

/*********************************************************************************************************
* 类名称:	CChapter1_LoadImgDlg
* 函数名称:	OnPaint
* 函数权限: Private
* 函数功能: 响应绘图消息，所有的重绘在这里执行
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 注    意:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	if (m_pMedImage)
	{
		CRect rect;
		CWnd* pImgWnd = GetDlgItem(IDC_STATIC_PIC);
		pImgWnd->GetClientRect(&rect);
		CDC* pImgDC = pImgWnd->GetDC();
		m_pMedImage->SetToDC(*pImgDC, rect, (CPoint(0, 0)));
	}
	
}

/*********************************************************************************************************
* 类名称:	CChapter1_LoadImgDlg
* 函数名称:	OnQueryDragIcon-
* 函数权限: Private
* 函数功能: 响应鼠标拖动图标消息
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 注    意:
*********************************************************************************************************/
HCURSOR CChapter1_LoadImgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*********************************************************************************************************
* 类名称:	CChapter1_LoadImgDlg
* 函数名称:	OnBnClickedButtonClose
* 函数权限: Private
* 函数功能: 响应退出按钮消息，退出程序
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 注    意:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::OnBnClickedButtonClose()
{
	// TODO: Add your control notification handler code here
	if (m_pMedImage)
	{
		delete m_pMedImage;
	}
	SendMessage(WM_CLOSE);
}

/*********************************************************************************************************
* 类名称:	CChapter1_LoadImgDlg
* 函数名称:	OnShowPos
* 函数权限: Private
* 函数功能: 响应静态文本框，鼠标移动消息，获取鼠标相对空间左上角的位置，并更新状态栏
* 输入参数: ix： WPARAM，横坐标；iy： LPARAM，纵坐标
* 输出参数: LRESULT类型， 0标识成功执行，非零，标识异常
* 返 回 值: void
* 注    意:
*********************************************************************************************************/
LRESULT CChapter1_LoadImgDlg::OnShowPos( WPARAM ix, LPARAM iy)
{
	//处理鼠标悬停事件
	int x = ix;
	int y = iy;
	CString strPos;
	strPos.Format(_T("坐标: (%d, %d)"), x, y);
	m_wndStatusBar.SetPaneText(1, strPos);
	CPoint p(x, y);
	COLORREF color = m_picControl.GetDC()->GetPixel(p);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);
	CString strRGB;
	strRGB.Format(_T("RGB(%d, %d, %d)"), r, g, b);
	m_wndStatusBar.SetPaneText(2, strRGB);
	float h, s, v;
	CImgProcAlgorithm::RGB2HSV(r, g, b, h, s, v);
	CString strHSV;
	strHSV.Format(_T("HSV(%.3f, %.3f, %.3f)"), h, s, v);
	m_wndStatusBar.SetPaneText(3, strHSV);
	// validate
	// CImgProcAlgorithm::HSV2RGB(int(h), int(s), int(v), r, g, b);
	
	return 0;
}

/*********************************************************************************************************
* 类名称:	CChapter1_LoadImgDlg
* 函数名称:	OnOpenImage
* 函数权限: Private
* 函数功能: 响应菜单栏的打开文件消息，执行导入图片像素功能，并更新静态文本框显示图像
* 输入参数: void
* 输出参数: LRESULT类型， 0标识成功执行，非零，标识异常
* 返 回 值: void
* 注    意:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::OnOpenImage()
{
	/*打开文件对话框*/
	CString filter = L"所有文件(*.bmp,*.jpg,*.tiff)|*.bmp;*.jpg;*.gif;*.tiff| BMP(*.bmp)|*.bmp|JPG(*.jpg)|*.jpg|GIF(*.gif)|TIFF(*.tiff)|*.tiff";
	CFileDialog fileDLg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);

	if (IDOK == fileDLg.DoModal())
	{
		CString fPath = fileDLg.GetPathName();			// 获取文件路径  
		CString fEnt = fileDLg.GetFileExt();			// 获取文件扩展名  
		fEnt.MakeLower();								// 将文件扩展名转化为小写字母  

		if (fEnt.Compare(_T("bmp")) == 0)
		{	// 如果打开的是bmp文件
			if (!m_pMedImage)
			{
				m_pMedImage = new CMedicalImg(fPath);
			}
			else
			{
				delete m_pMedImage;
				m_pMedImage = new CMedicalImg(fPath);
			}
			/*显示图像*/
			// 更新窗口大小
			CWnd* pImgWnd = GetDlgItem(IDC_STATIC_PIC);
			long imgHeight = abs(m_pMedImage->GetHeight());
			long imgWidth = m_pMedImage->GetWidth();
			SetWindowPos(NULL, 0, 0, imgWidth + 38, imgHeight + 150, SWP_NOZORDER | SWP_NOMOVE);
			pImgWnd->SetWindowPos(NULL, 0, 0, imgWidth, imgHeight, SWP_NOZORDER | SWP_NOMOVE);
			CWnd* pBtnWnd = GetDlgItem(IDC_BUTTON_CLOSE);
			pBtnWnd->SetWindowPos(NULL, imgWidth - 200, imgHeight + 30, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			UpdateWindow();
			CDC* pImgDC = pImgWnd->GetDC();
			CRect rect;
			pImgWnd->GetClientRect(&rect);
			m_pMedImage->SetToDC(*pImgDC, rect, (CPoint(0, 0)));
		}
		else
		{
			AfxMessageBox(_T("文件格式不符合要求！"));
		}
	}
}

/*********************************************************************************************************
* 类名称:	CChapter1_LoadImgDlg
* 函数名称:	OnSave
* 函数权限: Private
* 函数功能: 响应菜单栏的保存文件消息，执行打开文件对话框和保存文件
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 注    意:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::OnSave()
{
	// TODO: 在此添加命令处理程序代码
	// 保存图像
}

/*********************************************************************************************************
* 类名称:	CChapter1_LoadImgDlg
* 函数名称:	OnTimer
* 函数权限: Private
* 函数功能: 响应定时器消息，更新状态栏时间
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 注    意:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString strTime;
	// 获取系统当前时间，并保存到curTime   
	CTime curTime = CTime::GetCurrentTime();
	// 格式化curTime，将字符串保存到strTime   
	strTime = curTime.Format(_T("%Y年%m月%d日 %H:%M:%S"));
	// 在状态栏的时间窗格中显示系统时间字符串   
	m_wndStatusBar.SetPaneText(0, strTime);

	CDialogEx::OnTimer(nIDEvent);
}

/*********************************************************************************************************
* 类名称:	CChapter1_LoadImgDlg
* 函数名称:	OnSize
* 函数权限: Private
* 函数功能: 响应窗口大小改变消息，更新状态栏位置
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 注    意:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_wndStatusBar.GetSafeHwnd())
	{
		CRect  m_rect;
		GetClientRect(&m_rect);
		m_rect.top = m_rect.bottom - 20;
		m_wndStatusBar.MoveWindow(&m_rect, TRUE);
	}
}


void CChapter1_LoadImgDlg::OnFinalRelease()
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_pMedImage)
	{
		delete m_pMedImage;
	}
	CDialogEx::OnFinalRelease();
}



void CChapter1_LoadImgDlg::OnHsvAdjust()
{
	// TODO: 在此添加命令处理程序代码
	//CHSVDlg hsvdlg(m_pMedImage->m_strPath, this);

	//hsvdlg.DoModal();
	if (m_pMedImage)
	{
		CHSVDlg dlg(m_pMedImage->m_strPath, this);
		dlg.DoModal();
	}
	else
	{
		CHSVDlg dlg(this);
		dlg.DoModal();
	}
	
}
