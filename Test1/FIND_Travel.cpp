// FIND_Travel.cpp : 实现文件
//

#include "stdafx.h"
#include "Test1.h"
#include "FIND_Travel.h"
#include "afxdialogex.h"


// FIND_Travel 对话框

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
	m_findstyle.AddString("按时间查找");
	m_findstyle.AddString("按地名查找");
	m_findstyle.AddString("按旅程查找");

	char buf[256];
	GetCurrentDirectory(256, buf);  //得到当前工作路径
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


// FIND_Travel 消息处理程序


void FIND_Travel::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
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
	if (str.Compare("按地名查找") == 0)
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
	else if (str.Compare("按旅程查找") == 0)
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
	else if (str.Compare("按时间查找") == 0)
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
	//SetDlgItemText(IDC_COMBO_TravelName, "北京之旅");

	if (travel == -1)
	{
		MessageBox("没有找到！");
	}
	else
	{
		result.TrimRight(",");
		MessageBox("我找到了以下旅程：\n" + result + "。请在下面选择查看！");
	}

}


HBRUSH FIND_Travel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);   //设置背景透明 
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	return hbr;
}


void FIND_Travel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect  rect;
	GetClientRect(&rect);
	CDC  dcMem;   //定义一个工具箱（设备上下文）
	dcMem.CreateCompatibleDC(&dc);///建立关联DC 
	CBitmap  bmpBackground;   //位图对象
	bmpBackground.LoadBitmap(IDB_BITMAP3);   //IDB_BITMAP是你自己的图对应的ID  
	BITMAP  bitmap;
	bmpBackground.GetBitmap(&bitmap);  //建立绑定关系
	CBitmap  *pbmpOld = dcMem.SelectObject(&bmpBackground);   //保存原有CDC对象，并选入新CDC对象入DC
	dc.SetStretchBltMode(COLORONCOLOR);//防止bmp图片失真
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	// （个人建议把,rect.Width(),rect.Height()这两个数据 换成你的图片的大小，前提是图片足够大，这样图片不容易失真。关于图片失真，参考：http://blog.csdn.net/abidepan/article/details/7963929 ）
	dcMem.SelectObject(pbmpOld);
	bmpBackground.DeleteObject();
	dcMem.DeleteDC();
}


void FIND_Travel::OnCbnSelchangeComboTravelname()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
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
		//MessageBox("该旅程貌似还没有图片呢！");
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
		MessageBox("地图生成失败！");
	VARIANT vt;
	COleVariant vaUrl = _T("C:\\Users\\kanglb\\Desktop\\map\\map.htm");

	m_web.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
}


void FIND_Travel::OnCbnSelchangeComboFindPics()
{
	// TODO: 在此添加控件通知处理程序代码
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
		MessageBox("地图生成失败！");
	VARIANT vt;
	COleVariant vaUrl = _T("C:\\Users\\kanglb\\Desktop\\map\\map.htm");

	m_web.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
}


void FIND_Travel::OnCbnSelchangeComboFindstyle()
{
	//// TODO: 在此添加控件通知处理程序代码
	//CString style;
	//int nIndex = m_findstyle.GetCurSel();
	//m_findstyle.GetLBText(nIndex, style);

	//GetDlgItem(IDC_TOTAL_CASES)->SetWindowText(ss);
}
