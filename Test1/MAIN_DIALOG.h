#pragma once

#include "ADD_Travel.h"
#include "EDIT_Travel.h"
#include "FIND_Travel.h"
#include "BROWSE_Travel.h"

// MAIN_DIALOG 对话框

class MAIN_DIALOG : public CDialogEx
{
	DECLARE_DYNAMIC(MAIN_DIALOG)

public:
	MAIN_DIALOG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MAIN_DIALOG();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
#endif

protected:
	HICON m_hIcon;

	CBrush m_brush;		//画刷
	CTabCtrl m_tab;
	int m_CurSelTab;
	ADD_Travel m_page_ADD;
	EDIT_Travel m_page_EDIT;
	FIND_Travel m_page_FIND;
	BROWSE_Travel m_page_BROWSE;
	CDialog* pDialog[4];  //用来保存对话框对象指针
						  // 生成的消息映射函数
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
};
