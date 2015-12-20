#pragma once
#include "afxwin.h"
#include "explorer2.h"


// EDIT_Travel 对话框

class EDIT_Travel : public CDialogEx
{
	DECLARE_DYNAMIC(EDIT_Travel)

public:
	EDIT_Travel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~EDIT_Travel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Travel travelBuf;

	int select_travel;

	vector <Node> pictures;
	BOOL OnInitDialog();
	afx_msg void OnCbnSetfocusComboEditTravelname();
	CComboBox m_Edit_TravelName;
	afx_msg void OnCbnSelchangeComboEditTravelname();///////////////////////////
	afx_msg void OnBnClickedButtonEditEdit();
	CEdit m_Edit_Nodes;
	CExplorer2 m_Edit_web;
	afx_msg void OnBnClickedButtonEditOndel();
	CComboBox m_Edit_PicName;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonEditDelpic();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnCbnSetfocusComboEditPicname();
};
