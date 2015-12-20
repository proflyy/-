
// Test1Dlg.cpp : 实现文件
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


// CTest1Dlg 对话框



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


// CTest1Dlg 消息处理程序

BOOL CTest1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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
			SetDlgItemText(IDC_EDIT_PASSWD, "请直接登录！");
			((CButton*)GetDlgItem(IDC_CHECK_SavePWD))->SetCheck(TRUE);
			in >> readfile;
			if (readfile.compare("AutoLogin:TRUE") == 0)
			{
				((CButton*)GetDlgItem(IDC_CHECK_AutoLogin))->SetCheck(TRUE);
				OnBnClickedLogin();
			}
		}
		else
			SetDlgItemText(IDC_EDIT_PASSWD, "请输入密码");
	}
	else
		SetDlgItemText(IDC_EDIT_NAME,"请输入登陆名");
	//CEdit::SetPasswordChar();
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	((CEdit*)GetDlgItem(IDC_EDIT_PASSWD))->SetPasswordChar(0);
	//SetDlgItemText(IDC_EDIT_NAME,"请输入登陆名");
	// TODO: 在此添加额外的初始化代码

	m_brush.CreateSolidBrush(RGB(0, 200, 255));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTest1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		
		CDialogEx::OnPaint();
	}
	CImage image;
	image.Load("bj.jpg");//设置图片
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


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTest1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//登录按钮
void CTest1Dlg::OnBnClickedLogin()			
{
	// TODO: 在此添加控件通知处理程序代码

	
//	CString name,
	CString passwd;
	GetDlgItemText(IDC_EDIT_NAME, usr.loginName);
	GetDlgItemText(IDC_EDIT_passwd_save, passwd);
	if(passwd.Compare("")==0)
		GetDlgItemText(IDC_EDIT_PASSWD, passwd);
	UpdateData(true);//用于将屏幕上控件中的数据交换到变量中。
	if (usr.loginName.IsEmpty())
	{
		MessageBox(_T("请输入用户名！"));
		//SetFocus();
		return;
	}
	if (passwd.IsEmpty())
	{
		MessageBox(_T("请输入密码！"));
		return;
	}
	if(usr.login(passwd) == FALSE)
	{
		//MessageBox(_T("用户名或密码错误！"));
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

	SetDlgItemText(IDC_BUTTON_LOGIN, "登陆中。。。");
	if (usr.loading(passwd) == FALSE)
	{
		MessageBox("加载失败,请重新登录！");
		SetDlgItemText(IDC_BUTTON_LOGIN, "登陆");
		return;
	}
		
	//MessageBox(usr.loginName + ",欢迎登陆!");


	CTest1Dlg::OnOK();
	MAIN_DIALOG dlg;
	dlg.DoModal();
}

//消息预处理
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

//处理登录界面拖动
void CTest1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}


HBRUSH CTest1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	//在这加一条是否为对话框的判断语句  
	pDC->SetBkMode(TRANSPARENT); //透明背景！
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return   m_brush;
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);   
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));//设置背景色为蓝色
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CTest1Dlg::OnEnSetfocusEditName()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT_NAME, "");
	SetDlgItemText(IDC_EDIT_passwd_save, "");
}


void CTest1Dlg::OnEnSetfocusEditPasswd()
{
	// TODO: 在此添加控件通知处理程序代码
	////CString s = "●";
	//TCHAR a;
	//PBYTE p = (PBYTE)&a;
	//*p = 0xa1f1;
	//*(++p) = 0xf1;
	//CString s = _T("●");
	//MessageBox(s);
	((CEdit*)GetDlgItem(IDC_EDIT_PASSWD)) -> SetPasswordChar('*');
	SetDlgItemText(IDC_EDIT_PASSWD, "");
	SetDlgItemText(IDC_EDIT_passwd_save, "");
}

//注册用户
void CTest1Dlg::OnBnClickedButtonRegister()
{
	// TODO: 在此添加控件通知处理程序代码
	CreateUser dlg;
	dlg.DoModal();//显示注册窗口
	//发给服务器并返回状态信息
}
