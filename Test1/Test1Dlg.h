
// Test1Dlg.h : ͷ�ļ�
//
#include "Connect.h"
#pragma once


// CTest1Dlg �Ի���
class CTest1Dlg : public CDialogEx
{
// ����
public:
	CTest1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CBrush m_brush;		//��ɫ��ˢ
	CEdit m_Login_passwd;
	int Login(CString name,CString passwd);
	BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//HBITMAP LoadPicture(CString mFile);
	afx_msg void OnPaint();//ˢ�´���ʱ����
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedLogin();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);//�����¼�����϶�
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);//���ñ���ɫ��������ɫ������ɫ
	afx_msg void OnEnSetfocusEditName();
	afx_msg void OnEnSetfocusEditPasswd();
	afx_msg void OnBnClickedButtonRegister();
};
