#pragma once


// CreateUser �Ի���

class CreateUser : public CDialogEx
{
	DECLARE_DYNAMIC(CreateUser)

public:
	CreateUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CreateUser();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CreateUsr };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCdCreateusr();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnKillfocusEditCuPasswdcheck();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
