// BROWSE_Travel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test1.h"
#include "BROWSE_Travel.h"
#include "afxdialogex.h"


// BROWSE_Travel �Ի���

IMPLEMENT_DYNAMIC(BROWSE_Travel, CDialogEx)

BROWSE_Travel::BROWSE_Travel(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_BROWSE, pParent)
{

}

BROWSE_Travel::~BROWSE_Travel()
{
}

void BROWSE_Travel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_BROWSE_TravelName, m_Browse_TravelName);
	DDX_Control(pDX, IDC_EXPLORER1, m_Browse_Map);
}


BEGIN_MESSAGE_MAP(BROWSE_Travel, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_BROWSE_TravelName, &BROWSE_Travel::OnCbnSelchangeComboBrowseTravelname)
	ON_CBN_SETFOCUS(IDC_COMBO_BROWSE_TravelName, &BROWSE_Travel::OnCbnSetfocusComboBrowseTravelname)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// BROWSE_Travel ��Ϣ�������

BOOL BROWSE_Travel::OnInitDialog()
{
	char buf[256];
	int i = 1000;
	GetCurrentDirectory(1000, buf);  //�õ���ǰ����·��
	CString nopic;
	nopic = buf;
	nopic += "\\res\\htm\\Browse.htm";
	CDialogEx::OnInitDialog();
	VARIANT vt;
	COleVariant vaUrl = _T(nopic);

	m_Browse_Map.Navigate2(vaUrl, &vt, &vt, &vt, &vt);

	return TRUE;
	//return FALSE;
}

void BROWSE_Travel::OnCbnSelchangeComboBrowseTravelname()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i;
	CString travelName;
	int nIndex = m_Browse_TravelName.GetCurSel();
	m_Browse_TravelName.GetLBText(nIndex, travelName);

	for (i = 0;i < usr.travel.size();i++)
	{
		if (usr.travel[i].travelName.CompareNoCase(travelName) == 0)
		{
			//MessageBox("���ҵ��ˣ�" + travelName);
			usr.select_travel = &usr.travel[i];

			//for (int j = 0;j < usr.select_travel->pics.size();j++)
			//	MessageBox(usr.select_travel->pics[j].filePF);
			break;
		}
	}
	CString time;
	time = usr.select_travel->starttime + usr.select_travel->lasttime;
	SetDlgItemText(IDC_EDIT_BROWSE_TravelName, travelName);
	SetDlgItemText(IDC_EDIT_BROWSE_Time, time);
	SetDlgItemText(IDC_EDIT_Browse_nodes, usr.select_travel->notes);

	if (usr.select_travel->pics.size() < 1)
	{
		MessageBox("���г̻�û��ͼƬ��Ϣ��");
		VARIANT vt;
		COleVariant vaUrl = _T(".\\res\\htm\\NoPic_Browse.htm");

		m_Browse_Map.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
		return;
	}
	sort(usr.select_travel->pics.begin(), usr.select_travel->pics.end(), sort_by_time);
	vector<Node>::iterator it;
	it = usr.select_travel->pics.begin();
	MakeMap map;
	if (!map.File_Edit("C:\\Users\\kanglb\\Desktop\\map\\map.htm", usr.select_travel->pics.begin(), usr.select_travel->pics.end(), it))
		MessageBox("��ͼ����ʧ�ܣ�");
	VARIANT vt;
	COleVariant vaUrl = _T("C:\\Users\\kanglb\\Desktop\\map\\map.htm");

	m_Browse_Map.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
}


void BROWSE_Travel::OnCbnSetfocusComboBrowseTravelname()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Browse_TravelName.ResetContent();
	int i;
	for (i = 0;i < usr.travel.size();i++)
	{
		m_Browse_TravelName.AddString(usr.travel[i].travelName);
	}

	//m_Browse_TravelName.SetCurSel(0);
}


HBRUSH BROWSE_Travel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);   //���ñ���͸�� 
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	return hbr;
}


void BROWSE_Travel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect  rect;
	GetClientRect(&rect);
	CDC  dcMem;   //����һ�������䣨�豸�����ģ�
	dcMem.CreateCompatibleDC(&dc);///��������DC 
	CBitmap  bmpBackground;   //λͼ����
	bmpBackground.LoadBitmap(IDB_BITMAP4);   //IDB_BITMAP�����Լ���ͼ��Ӧ��ID  
	BITMAP  bitmap;
	bmpBackground.GetBitmap(&bitmap);  //�����󶨹�ϵ
	CBitmap  *pbmpOld = dcMem.SelectObject(&bmpBackground);   //����ԭ��CDC���󣬲�ѡ����CDC������DC
	dc.SetStretchBltMode(COLORONCOLOR);//��ֹbmpͼƬʧ��
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	// �����˽����,rect.Width(),rect.Height()���������� �������ͼƬ�Ĵ�С��ǰ����ͼƬ�㹻������ͼƬ������ʧ�档����ͼƬʧ�棬�ο���http://blog.csdn.net/abidepan/article/details/7963929 ��
	dcMem.SelectObject(pbmpOld);
	bmpBackground.DeleteObject();
	dcMem.DeleteDC();
}

