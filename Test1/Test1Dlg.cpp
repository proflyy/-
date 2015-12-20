
// Test1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test1.h"
#include "Test1Dlg.h"
#include "afxdialogex.h"
#include "MAIN_DIALOG.h"
#include "User.h"
#include "CreateUser.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTest1Dlg �Ի���



CTest1Dlg::CTest1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEST1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTest1Dlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_EDIT_PASSWD, m_Login_passwd);
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTest1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CTest1Dlg::OnBnClickedLogin)
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
	ON_EN_SETFOCUS(IDC_EDIT_NAME, &CTest1Dlg::OnEnSetfocusEditName)
	ON_EN_SETFOCUS(IDC_EDIT_PASSWD, &CTest1Dlg::OnEnSetfocusEditPasswd)
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &CTest1Dlg::OnBnClickedButtonRegister)
END_MESSAGE_MAP()


// CTest1Dlg ��Ϣ�������

BOOL CTest1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	ifstream in("usr.info");
	string readfile;
	in >> readfile;
	if (readfile.substr(0, 9).compare("UserName:") == 0)
	{
		SetDlgItemText(IDC_EDIT_NAME, readfile.substr(9).c_str());
		in >> readfile;
		if (readfile.substr(0, 11).compare("UserPasswd:") == 0)
		{
			SetDlgItemText(IDC_EDIT_passwd_save, readfile.substr(11).c_str());
			SetDlgItemText(IDC_EDIT_PASSWD, "��ֱ�ӵ�¼��");
			((CButton*)GetDlgItem(IDC_CHECK_SavePWD))->SetCheck(TRUE);
			in >> readfile;
			if (readfile.compare("AutoLogin:TRUE") == 0)
			{
				((CButton*)GetDlgItem(IDC_CHECK_AutoLogin))->SetCheck(TRUE);
				OnBnClickedLogin();
			}
		}
		else
			SetDlgItemText(IDC_EDIT_PASSWD, "����������");
	}
	else
		SetDlgItemText(IDC_EDIT_NAME,"�������½��");
	//CEdit::SetPasswordChar();
	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	((CEdit*)GetDlgItem(IDC_EDIT_PASSWD))->SetPasswordChar(0);
	//SetDlgItemText(IDC_EDIT_NAME,"�������½��");
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_brush.CreateSolidBrush(RGB(0, 200, 255));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTest1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
//		CAboutDlg dlgAbout;
//		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTest1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		
		CDialogEx::OnPaint();
	}
	CImage image;
	image.Load("bj.jpg");//����ͼƬ
	CRect rcclient_1;
	GetDlgItem(IDC_PIC)->GetClientRect(&rcclient_1);
	image.Draw(GetDC()->m_hDC, rcclient_1);

	CImage avatar;
	CString avatarfile;
	avatarfile = "avatar.png";
	avatar.Load(avatarfile);
	CRect rcclient_2;
	GetDlgItem(IDC_AVATAR)->GetWindowRect(&rcclient_2);
	ScreenToClient(&rcclient_2);
	avatar.Draw(GetDC()->m_hDC, rcclient_2);

	//CRect rcclient_3;
	//GetDlgItem(IDC_EDIT_NAME)->GetWindowRect(&rcclient_3);
	//DrawText(0, "***********************8", 50, rcclient_3, DT_SINGLELINE);
}


//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTest1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//��¼��ť
void CTest1Dlg::OnBnClickedLogin()			
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	
//	CString name,
	CString passwd;
	GetDlgItemText(IDC_EDIT_NAME, usr.loginName);
	GetDlgItemText(IDC_EDIT_passwd_save, passwd);
	if(passwd.Compare("")==0)
		GetDlgItemText(IDC_EDIT_PASSWD, passwd);
	UpdateData(true);//���ڽ���Ļ�Ͽؼ��е����ݽ����������С�
	if (usr.loginName.IsEmpty())
	{
		MessageBox(_T("�������û�����"));
		//SetFocus();
		return;
	}
	if (passwd.IsEmpty())
	{
		MessageBox(_T("���������룡"));
		return;
	}
	if(usr.login(passwd) == FALSE)
	{
		//MessageBox(_T("�û������������"));
		usr.con.Close();
		return;
	}
	ofstream out("usr.info");
	out << "UserName:" << usr.loginName << endl;
//#include <direct.h>
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_SavePWD))->GetCheck())
	{
		out << "UserPasswd:" << passwd << endl;
		if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_AutoLogin))->GetCheck())
			out << "AutoLogin:TRUE" << endl;
		out.close();
	}

	SetDlgItemText(IDC_BUTTON_LOGIN, "��½�С�����");
	if (usr.loading(passwd) == FALSE)
	{
		MessageBox("����ʧ��,�����µ�¼��");
		SetDlgItemText(IDC_BUTTON_LOGIN, "��½");
		return;
	}
		
	//MessageBox(usr.loginName + ",��ӭ��½!");


	CTest1Dlg::OnOK();
	MAIN_DIALOG dlg;
	dlg.DoModal();
}

//��ϢԤ����
BOOL CTest1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	//CEdit* m_edit = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
	if ((GetFocus() == (CEdit*)GetDlgItem(IDC_EDIT_NAME) || GetFocus() == (CEdit*)GetDlgItem(IDC_EDIT_PASSWD)) && (pMsg->message == WM_CHAR))
	{
		if (pMsg->wParam == ' ')
		{
			return 1;

		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

//�����¼�����϶�
void CTest1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}


HBRUSH CTest1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	//�����һ���Ƿ�Ϊ�Ի�����ж����  
	pDC->SetBkMode(TRANSPARENT); //͸��������
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return   m_brush;
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);   
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));//���ñ���ɫΪ��ɫ
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CTest1Dlg::OnEnSetfocusEditName()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_EDIT_NAME, "");
	SetDlgItemText(IDC_EDIT_passwd_save, "");
}


void CTest1Dlg::OnEnSetfocusEditPasswd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	////CString s = "��";
	//TCHAR a;
	//PBYTE p = (PBYTE)&a;
	//*p = 0xa1f1;
	//*(++p) = 0xf1;
	//CString s = _T("��");
	//MessageBox(s);
	((CEdit*)GetDlgItem(IDC_EDIT_PASSWD)) -> SetPasswordChar('*');
	SetDlgItemText(IDC_EDIT_PASSWD, "");
	SetDlgItemText(IDC_EDIT_passwd_save, "");
}

//ע���û�
void CTest1Dlg::OnBnClickedButtonRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CreateUser dlg;
	dlg.DoModal();//��ʾע�ᴰ��
	//����������������״̬��Ϣ
}
