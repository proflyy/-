// MAIN_DIALOG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test1.h"
#include "MAIN_DIALOG.h"
#include "afxdialogex.h"

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx

{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

														// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	TRACE(traceAppMsg, 0, "����: ��ִ����û�а���\n");
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// MAIN_DIALOG �Ի���

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
	m_brush.CreateSolidBrush(RGB(0, 200, 255));
	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

		////////////////////////
		//ΪTab Control��������ҳ��
	m_tab.InsertItem(0, _T("�����г�"));
	m_tab.InsertItem(1, _T("�༭�г�"));
	m_tab.InsertItem(2, _T("��ѯ�г�"));
	m_tab.InsertItem(3, _T("����г�"));

	//���������Ի���
	m_page_ADD.Create(IDD_DIALOG_ADD, &m_tab);
	m_page_EDIT.Create(IDD_DIALOG_EDIT, &m_tab);
	m_page_FIND.Create(IDD_DIALOG_FIND, &m_tab);
	m_page_BROWSE.Create(IDD_DIALOG_BROWSE, &m_tab);
	//�趨��Tab����ʾ�ķ�Χ
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

	//�ѶԻ������ָ�뱣������
	pDialog[0] = &m_page_ADD;
	pDialog[1] = &m_page_EDIT;
	pDialog[2] = &m_page_FIND;
	pDialog[3] = &m_page_BROWSE;
	//��ʾ��ʼҳ��
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	pDialog[2]->ShowWindow(SW_HIDE);
	pDialog[3]->ShowWindow(SW_HIDE);
	//���浱ǰѡ��
	m_CurSelTab = 0;



	//GetDlgItem(IDC_COMBO_Add_TravelName)->SetFocus();
	///////////////////////
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void MAIN_DIALOG::OnPaint()
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

	TRACE(traceAppMsg, 0, "����: �һ��ǻ��ƺ�����\n");
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR MAIN_DIALOG::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon); 
}

HBRUSH MAIN_DIALOG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	pDC->SetBkMode(TRANSPARENT); //͸��������
	if (nCtlColor == CTLCOLOR_DLG)
	{
		//return   m_brush;   //����ˢ��
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);   //���ñ���͸�� 
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	return hbr;
}
// MAIN_DIALOG ��Ϣ�������


void MAIN_DIALOG::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ѵ�ǰ��ҳ����������
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//�õ��µ�ҳ������
	m_CurSelTab = m_tab.GetCurSel();
	//���µ�ҳ����ʾ����
	pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);

	*pResult = 0;
}