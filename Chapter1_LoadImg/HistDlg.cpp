// HistDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Chapter1_LoadImg.h"
#include "HistDlg.h"
#include "afxdialogex.h"


// CHistDlg 对话框

IMPLEMENT_DYNAMIC(CHistDlg, CDialogEx)

CHistDlg::CHistDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CHistDlg::~CHistDlg()
{
}

void CHistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistDlg, CDialogEx)
END_MESSAGE_MAP()


// CHistDlg 消息处理程序·
