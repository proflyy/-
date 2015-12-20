#pragma once
#include "explorer2.h"
#include "afxwin.h"


// FIND_Travel 对话框

class FIND_Travel : public CDialogEx
{
	DECLARE_DYNAMIC(FIND_Travel)

public:
	FIND_Travel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FIND_Travel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FIND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	CExplorer2 m_web;//没用
	CComboBox m_findstyle;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CComboBox m_Find_TravelName;
	afx_msg void OnCbnSelchangeComboTravelname();/////////////////////////////////
	CComboBox m_Find_Pics;//路线名称
	afx_msg void OnCbnSelchangeComboFindPics();
	afx_msg void OnCbnSelchangeComboFindstyle();//没用
};
