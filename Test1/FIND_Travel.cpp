// FIND_Travel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test1.h"
#include "FIND_Travel.h"
#include "afxdialogex.h"


// FIND_Travel �Ի���

IMPLEMENT_DYNAMIC(FIND_Travel, CDialogEx)

FIND_Travel::FIND_Travel(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FIND, pParent)
{
}

FIND_Travel::~FIND_Travel()
{
}

BOOL FIND_Travel::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_findstyle.AddString("��ʱ�����");
	m_findstyle.AddString("����������");
	m_findstyle.AddString("���ó̲���");

	char buf[256];
	GetCurrentDirectory(256, buf);  //�õ���ǰ����·��
	CString pic;
	pic = buf;
	pic += "\\res\\htm\\Find.htm";
	CDialogEx::OnInitDialog();
	VARIANT vt;
	COleVariant vaUrl = _T(pic);
	m_web.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
	return TRUE;
}

void FIND_Travel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER2, m_web);
	DDX_Control(pDX, IDC_COMBO_FindStyle, m_findstyle);
	DDX_Control(pDX, IDC_COMBO_TravelName, m_Find_TravelName);
	DDX_Control(pDX, IDC_COMBO2, m_Find_Pics);
}


BEGIN_MESSAGE_MAP(FIND_Travel, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &FIND_Travel::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_TravelName, &FIND_Travel::OnCbnSelchangeComboTravelname)
	ON_CBN_SELCHANGE(IDC_COMBO_Find_Pics, &FIND_Travel::OnCbnSelchangeComboFindPics)
	ON_CBN_SELCHANGE(IDC_COMBO_FindStyle, &FIND_Travel::OnCbnSelchangeComboFindstyle)
END_MESSAGE_MAP()


// FIND_Travel ��Ϣ�������


void FIND_Travel::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//int nIndex = m_findstyle.GetCurSel();			=_wtof(a.GetBuffer(0))
	m_Find_TravelName.ResetContent();
	CString str;
	CString city;
	GetDlgItemText(IDC_EDIT_Search,str);
	//Travel t;
	int nIndex = m_findstyle.GetCurSel();
	m_findstyle.GetLBText(nIndex, str);
	CString info;
	CString result;
	GetDlgItemText(IDC_EDIT_Search, info);
	int travel =-1;
	if (str.Compare("����������") == 0)
	{
		for (int i = 0; i < usr.travel.size();i++)
		{
			for (int j = 0;j < usr.travel[i].pics.size();j++)
			{
				city = Match_City(atof(usr.travel[i].pics[j].longitude.GetBuffer()), atof(usr.travel[i].pics[j].latitude.GetBuffer()));

				//MessageBox(city);
				if (city.FindOneOf(info) != -1)
				{
					travel = i;
					result += usr.travel[i].travelName + ",";
					m_Find_TravelName.AddString(usr.travel[i].travelName);
					//t.travelName = usr.travel[i].travelName;
					//t.notes = usr.travel[i].notes;
					SetDlgItemText(IDC_EDIT_EDIT_Node, usr.travel[i].notes);

					//for (int j = 0;j < usr.select_travel->pics.size();j++)
					//	MessageBox(usr.select_travel->pics[j].filePF);
					break;
				}
			}
		}
	}
	else if (str.Compare("���ó̲���") == 0)
	{
		for (int i = 0; i < usr.travel.size();i++)
		{
			if (usr.travel[i].travelName.FindOneOf(info) != -1)
			{
				travel = i;
				result += usr.travel[i].travelName + ",";
				m_Find_TravelName.AddString(usr.travel[i].travelName);

				SetDlgItemText(IDC_EDIT_EDIT_Node, usr.travel[i].notes);
			}
		}
	}
	else if (str.Compare("��ʱ�����") == 0)
	{
		for (int i = 0; i < usr.travel.size();i++)
		{
			if ((usr.travel[i].starttime.Left(info.GetLength()).Compare(info) <= 0) && (usr.travel[i].lasttime.Left(info.GetLength()).Compare(info) >= 0))
			{
				travel = i;
				result += usr.travel[i].travelName + ",";
				m_Find_TravelName.AddString(usr.travel[i].travelName);
				SetDlgItemText(IDC_EDIT_EDIT_Node, usr.travel[i].notes);
			}
		}
	}
	//SetDlgItemText(IDC_COMBO_TravelName, "����֮��");

	if (travel == -1)
	{
		MessageBox("û���ҵ���");
	}
	else
	{
		result.TrimRight(",");
		MessageBox("���ҵ��������ọ́�\n" + result + "����������ѡ��鿴��");
	}

}


HBRUSH FIND_Travel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);   //���ñ���͸�� 
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	return hbr;
}


void FIND_Travel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect  rect;
	GetClientRect(&rect);
	CDC  dcMem;   //����һ�������䣨�豸�����ģ�
	dcMem.CreateCompatibleDC(&dc);///��������DC 
	CBitmap  bmpBackground;   //λͼ����
	bmpBackground.LoadBitmap(IDB_BITMAP3);   //IDB_BITMAP�����Լ���ͼ��Ӧ��ID  
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


void FIND_Travel::OnCbnSelchangeComboTravelname()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Find_Pics.ResetContent();
	int i;
	CString travelName;
	int nIndex = m_Find_TravelName.GetCurSel();
	m_Find_TravelName.GetLBText(nIndex, travelName);
	for (i = 0;i < usr.travel.size();i++)
	{
		if (usr.travel[i].travelName.Compare(travelName) == 0)
		{
			//travelBuf.travelName = usr.travel[i].travelName;
			//travelBuf.notes = usr.travel[i].notes;
			SetDlgItemText(IDC_EDIT_Find_stime, usr.travel[i].starttime);
			SetDlgItemText(IDC_EDIT_Find_ltime, usr.travel[i].lasttime);
			//for (int j = 0;j < usr.select_travel->pics.size();j++)
			//	MessageBox(usr.select_travel->pics[j].filePF);
			break;
		}
	}
	if (usr.travel[i].pics.size() == 0)
	{
		//MessageBox("���ó�ò�ƻ�û��ͼƬ�أ�");
		return;
	}
	sort(usr.travel[i].pics.begin(), usr.travel[i].pics.end(), sort_by_time);
	vector<Node>::iterator itt;
	for (itt = usr.travel[i].pics.begin();itt != usr.travel[i].pics.end();itt++)
	{
		m_Find_Pics.AddString(itt->fileName);
	}
	MakeMap map;
	vector<Node>::iterator it = usr.travel[i].pics.begin();
	if (!map.File_Edit("C:\\Users\\kanglb\\Desktop\\map\\map.htm", usr.travel[i].pics.begin(), usr.travel[i].pics.end(), it))
		MessageBox("��ͼ����ʧ�ܣ�");
	VARIANT vt;
	COleVariant vaUrl = _T("C:\\Users\\kanglb\\Desktop\\map\\map.htm");

	m_web.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
}


void FIND_Travel::OnCbnSelchangeComboFindPics()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int travel,picture;
	CString travelName, picName;
	GetDlgItemText(IDC_COMBO_TravelName,travelName);
	int nIndex = m_Find_Pics.GetCurSel();
	m_Find_Pics.GetLBText(nIndex, picName);
	//GetDlgItemText(IDC_COMBO_Find_Pics, picName);
	for (int i = 0;i < usr.travel.size();i++)
	{
		if (usr.travel[i].travelName.Compare(travelName) == 0)
		{
			travel = i;
			break;
		}
	}

	sort(usr.travel[travel].pics.begin(), usr.travel[travel].pics.end(), sort_by_time);
	vector<Node>::iterator itt;
	for (itt = usr.travel[travel].pics.begin();itt != usr.travel[travel].pics.end();itt++)
	{
		if (itt->fileName.Compare(picName) == 0)
		{
			break;
		}
	}
	MakeMap map;
	//vector<Node>::iterator it = usr.travel[travel].pics.begin();
	if (!map.File_Edit("C:\\Users\\kanglb\\Desktop\\map\\map.htm", usr.travel[travel].pics.begin(), usr.travel[travel].pics.end(), itt))
		MessageBox("��ͼ����ʧ�ܣ�");
	VARIANT vt;
	COleVariant vaUrl = _T("C:\\Users\\kanglb\\Desktop\\map\\map.htm");

	m_web.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
}


void FIND_Travel::OnCbnSelchangeComboFindstyle()
{
	//// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CString style;
	//int nIndex = m_findstyle.GetCurSel();
	//m_findstyle.GetLBText(nIndex, style);

	//GetDlgItem(IDC_TOTAL_CASES)->SetWindowText(ss);
}
