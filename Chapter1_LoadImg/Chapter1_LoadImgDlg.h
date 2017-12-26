/*********************************************************************************************************
* 模块名称: Chapter1_LoadImgDlg.h
* 摘    要: MVC架构的中心控制器
* 当前版本: 1.0.0
* 作    者: 秦陈陈
* 完成日期: 2017年12月20日
* 内    容: 主对话框，作为MVC架构的控制器
* 注    意: 
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
#pragma once
#include "piccontrol.h"
#include "MedicalImg.h"


/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/
#define WM_SHOW_POS WM_USER+10


/*********************************************************************************************************
*                                              类定义
*********************************************************************************************************/
class CChapter1_LoadImgDlg : public CDialogEx
{
// Construction
public:
	CChapter1_LoadImgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CHAPTER1_LOADIMG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnShowPos(WPARAM,LPARAM);		//处理鼠标悬停消息
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnOpenImage();
	afx_msg void OnSave();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);



// Variable
public:
	/*View*/
	CPicControl m_picControl;
	CStatusBar m_wndStatusBar;
	CMenu m_ctrMenu;
	/*Data*/
	CMedicalImg* m_pMedImage;
	virtual void OnFinalRelease();
	afx_msg void OnHsvAdjust();
};
