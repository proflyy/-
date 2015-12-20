// MAIN_DIALOG.cpp : 实现文件
//

#include "stdafx.h"
#include "Test1.h"
#include "MAIN_DIALOG.h"
#include "afxdialogex.h"

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx

{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

														// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	TRACE(traceAppMsg, 0, "警告: 我执行了没有啊？\n");
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// MAIN_DIALOG 对话框

IMPLEMENT_DYNAMIC(MAIN_DIALOG, CDialogEx)

MAIN_DIALOG::MAIN_DIALOG(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MAIN, pParent)
{

}

MAIN_DIALOG::~MAIN_DIALOG()
{
}

void MAIN_DIALOG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_tab);
}


BEGIN_MESSAGE_MAP(MAIN_DIALOG, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &MAIN_DIALOG::OnTcnSelchangeTab)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()



BOOL MAIN_DIALOG::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);
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
	m_brush.CreateSolidBrush(RGB(0, 200, 255));
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码

		////////////////////////
		//为Tab Control增加两个页面
	m_tab.InsertItem(0, _T("新增行程"));
	m_tab.InsertItem(1, _T("编辑行程"));
	m_tab.InsertItem(2, _T("查询行程"));
	m_tab.InsertItem(3, _T("浏览行程"));

	//创建两个对话框
	m_page_ADD.Create(IDD_DIALOG_ADD, &m_tab);
	m_page_EDIT.Create(IDD_DIALOG_EDIT, &m_tab);
	m_page_FIND.Create(IDD_DIALOG_FIND, &m_tab);
	m_page_BROWSE.Create(IDD_DIALOG_BROWSE, &m_tab);
	//设定在Tab内显示的范围
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_page_ADD.MoveWindow(&rc);
	m_page_EDIT.MoveWindow(&rc);
	m_page_FIND.MoveWindow(&rc);
	m_page_BROWSE.MoveWindow(&rc);

	//把对话框对象指针保存起来
	pDialog[0] = &m_page_ADD;
	pDialog[1] = &m_page_EDIT;
	pDialog[2] = &m_page_FIND;
	pDialog[3] = &m_page_BROWSE;
	//显示初始页面
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	pDialog[2]->ShowWindow(SW_HIDE);
	pDialog[3]->ShowWindow(SW_HIDE);
	//保存当前选择
	m_CurSelTab = 0;



	//GetDlgItem(IDC_COMBO_Add_TravelName)->SetFocus();
	///////////////////////
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void MAIN_DIALOG::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void MAIN_DIALOG::OnPaint()
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

	TRACE(traceAppMsg, 0, "警告: 我还是绘制函数。\n");
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR MAIN_DIALOG::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon); 
}

HBRUSH MAIN_DIALOG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	pDC->SetBkMode(TRANSPARENT); //透明背景！
	if (nCtlColor == CTLCOLOR_DLG)
	{
		//return   m_brush;   //返加刷子
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);   //设置背景透明 
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	return hbr;
}
// MAIN_DIALOG 消息处理程序


void MAIN_DIALOG::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//把当前的页面隐藏起来
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//得到新的页面索引
	m_CurSelTab = m_tab.GetCurSel();
	//把新的页面显示出来
	pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);

	*pResult = 0;
}