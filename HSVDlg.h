#pragma once
#include "MedicalImg.h"

// CHSVDlg �Ի���

class CHSVDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHSVDlg)
	 
public:
	CHSVDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CHSVDlg(CString imagePath, CWnd* pParent = NULL);
	virtual ~CHSVDlg();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HSV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

public:
	CMedicalImg* m_pMedImage;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
