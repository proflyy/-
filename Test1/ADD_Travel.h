#pragma once
#include "explorer2.h"
#include "afxwin.h"
#define CREATE	1
#define SAVE	0
using namespace std;
// ADD_Travel �Ի���

class ADD_Travel : public CDialogEx
{
	DECLARE_DYNAMIC(ADD_Travel)

public:
	ADD_Travel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ADD_Travel();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	int save_style;//
	CExplorer2 m_web_add;//û��
	//vector<Node> openFiles;
	Travel newTravel;
	CString ADD_Travel::BootOpenDialog();///////֪ͨ����������
	afx_msg void OnBnClickedButtonAddpic();//��ʾ��ͼ
	// ����
	double m_Add_lng;
	double m_Add_lat;
	CString m_Add_PicTime;
	CString m_Add_Location;
	CComboBox m_Add_TravelName;
	afx_msg void OnCbnEditchangeTravelName();//�༭�г�����
	afx_msg void OnCbnSelchangeComboAddTravelname();//�����ó�����//��ѯ
	afx_msg void OnBnClickedButtonAddSave();//��Ƭ���浽����
	afx_msg void OnEnChangeEditAddTravelname();///////û�ã��Ժ��޸�
	afx_msg void OnEnSetfocusEditAddTravelname();///////��ù�꣬����
	afx_msg void OnEnKillfocusEditAddTravelname();////////ʧȥ���
	CComboBox m_Add_Pics;//�ļ�����
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeComboAddFilename();//��ʾͼƬ��Ϣ
};
