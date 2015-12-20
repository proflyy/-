#pragma once
#include "afxwin.h"
#include "explorer2.h"


// BROWSE_Travel 对话框

class BROWSE_Travel : public CDialogEx
{
	DECLARE_DYNAMIC(BROWSE_Travel)

public:
	BROWSE_Travel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BROWSE_Travel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BROWSE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Browse_TravelName;
	afx_msg void OnCbnSelchangeComboBrowseTravelname();///////////////////////////////
	CExplorer2 m_Browse_Map;//没用
	afx_msg void OnCbnSetfocusComboBrowseTravelname();//
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
