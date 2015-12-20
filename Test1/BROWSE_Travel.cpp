// BROWSE_Travel.cpp : 实现文件
//

#include "stdafx.h"
#include "Test1.h"
#include "BROWSE_Travel.h"
#include "afxdialogex.h"


// BROWSE_Travel 对话框

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


// BROWSE_Travel 消息处理程序

BOOL BROWSE_Travel::OnInitDialog()
{
	char buf[256];
	int i = 1000;
	GetCurrentDirectory(1000, buf);  //得到当前工作路径
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
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CString travelName;
	int nIndex = m_Browse_TravelName.GetCurSel();
	m_Browse_TravelName.GetLBText(nIndex, travelName);

	for (i = 0;i < usr.travel.size();i++)
	{
		if (usr.travel[i].travelName.CompareNoCase(travelName) == 0)
		{
			//MessageBox("我找到了！" + travelName);
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
		MessageBox("该行程还没有图片信息。");
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
		MessageBox("地图生成失败！");
	VARIANT vt;
	COleVariant vaUrl = _T("C:\\Users\\kanglb\\Desktop\\map\\map.htm");

	m_Browse_Map.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
}


void BROWSE_Travel::OnCbnSetfocusComboBrowseTravelname()
{
	// TODO: 在此添加控件通知处理程序代码
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
		pDC->SetBkMode(TRANSPARENT);   //设置背景透明 
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	return hbr;
}


void BROWSE_Travel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect  rect;
	GetClientRect(&rect);
	CDC  dcMem;   //定义一个工具箱（设备上下文）
	dcMem.CreateCompatibleDC(&dc);///建立关联DC 
	CBitmap  bmpBackground;   //位图对象
	bmpBackground.LoadBitmap(IDB_BITMAP4);   //IDB_BITMAP是你自己的图对应的ID  
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

