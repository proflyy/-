#pragma once
#include "explorer2.h"
#include "afxwin.h"


// FIND_Travel �Ի���

class FIND_Travel : public CDialogEx
{
	DECLARE_DYNAMIC(FIND_Travel)

public:
	FIND_Travel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FIND_Travel();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FIND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	CExplorer2 m_web;//û��
	CComboBox m_findstyle;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CComboBox m_Find_TravelName;
	afx_msg void OnCbnSelchangeComboTravelname();/////////////////////////////////
	CComboBox m_Find_Pics;//·������
	afx_msg void OnCbnSelchangeComboFindPics();
	afx_msg void OnCbnSelchangeComboFindstyle();//û��
};
