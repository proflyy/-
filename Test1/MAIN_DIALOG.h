#pragma once

#include "ADD_Travel.h"
#include "EDIT_Travel.h"
#include "FIND_Travel.h"
#include "BROWSE_Travel.h"

// MAIN_DIALOG �Ի���

class MAIN_DIALOG : public CDialogEx
{
	DECLARE_DYNAMIC(MAIN_DIALOG)

public:
	MAIN_DIALOG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MAIN_DIALOG();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
#endif

protected:
	HICON m_hIcon;

	CBrush m_brush;		//��ˢ
	CTabCtrl m_tab;
	int m_CurSelTab;
	ADD_Travel m_page_ADD;
	EDIT_Travel m_page_EDIT;
	FIND_Travel m_page_FIND;
	BROWSE_Travel m_page_BROWSE;
	CDialog* pDialog[4];  //��������Ի������ָ��
						  // ���ɵ���Ϣӳ�亯��
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
};
