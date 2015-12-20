#pragma once


// CreateUser 对话框

class CreateUser : public CDialogEx
{
	DECLARE_DYNAMIC(CreateUser)

public:
	CreateUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CreateUser();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CreateUsr };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCdCreateusr();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnKillfocusEditCuPasswdcheck();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
