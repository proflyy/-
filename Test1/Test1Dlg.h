
// Test1Dlg.h : 头文件
//
#include "Connect.h"
#pragma once


// CTest1Dlg 对话框
class CTest1Dlg : public CDialogEx
{
// 构造
public:
	CTest1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CBrush m_brush;		//蓝色画刷
	CEdit m_Login_passwd;
	int Login(CString name,CString passwd);
	BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//HBITMAP LoadPicture(CString mFile);
	afx_msg void OnPaint();//刷新窗口时调用
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedLogin();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);//处理登录界面拖动
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);//设置背景色，字体颜色，按键色
	afx_msg void OnEnSetfocusEditName();
	afx_msg void OnEnSetfocusEditPasswd();
	afx_msg void OnBnClickedButtonRegister();
};
