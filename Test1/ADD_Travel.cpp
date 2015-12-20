// ADD_Travel.cpp : 实现文件
//

#include "stdafx.h"
#include "Test1.h"
#include "ADD_Travel.h"
#include "afxdialogex.h"
#include "BROWSE_Travel.h"

// ADD_Travel 对话框

IMPLEMENT_DYNAMIC(ADD_Travel, CDialogEx)

ADD_Travel::ADD_Travel(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
	, m_Add_lng(0)
	, m_Add_lat(0)
	, m_Add_PicTime(_T(""))
	, m_Add_Location(_T(""))
{

}

ADD_Travel::~ADD_Travel()
{
}

void ADD_Travel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER2, m_web_add);
	DDX_Text(pDX, IDC_EDIT_Add_Lon, m_Add_lng);
	DDX_Text(pDX, IDC_EDIT_Add_Lat, m_Add_lat);
	DDX_Text(pDX, IDC_EDIT_Add_PicTime, m_Add_PicTime);
	DDX_Text(pDX, IDC_EDIT_Add_Location, m_Add_Location);
	DDX_Control(pDX, IDC_COMBO_Add_TravelName, m_Add_TravelName);
	DDX_Control(pDX, IDC_COMBO_Add_FileName, m_Add_Pics);
}

BEGIN_MESSAGE_MAP(ADD_Travel, CDialogEx)
	ON_CBN_EDITCHANGE(IDC_COMBO_Add_TravelName, &ADD_Travel::OnCbnEditchangeTravelName)
	ON_BN_CLICKED(IDC_BUTTON_AddPic, &ADD_Travel::OnBnClickedButtonAddpic)
	ON_CBN_SELCHANGE(IDC_COMBO_Add_TravelName, &ADD_Travel::OnCbnSelchangeComboAddTravelname)
	ON_BN_CLICKED(IDC_BUTTON_Add_Save, &ADD_Travel::OnBnClickedButtonAddSave)
	ON_EN_CHANGE(IDC_EDIT_Add_TravelName, &ADD_Travel::OnEnChangeEditAddTravelname)
	ON_EN_SETFOCUS(IDC_EDIT_Add_TravelName, &ADD_Travel::OnEnSetfocusEditAddTravelname)
	ON_EN_KILLFOCUS(IDC_EDIT_Add_TravelName, &ADD_Travel::OnEnKillfocusEditAddTravelname)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_Add_FileName, &ADD_Travel::OnCbnSelchangeComboAddFilename)
END_MESSAGE_MAP()

// ADD_Travel 消息处理程序

BOOL ADD_Travel::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	

	SetDlgItemText(IDC_EDIT_Add_TravelName, "新建旅程？");
	SetDlgItemText(IDC_EDIT_Add_PicTime, "");
	SetDlgItemText(IDC_EDIT_Add_Lon, "");
	SetDlgItemText(IDC_EDIT_Add_Lat, "");
	SetDlgItemText(IDC_EDIT_Add_Location, "");
	char buf[256];
	GetCurrentDirectory(256, buf);  //得到当前工作路径
	CString pic;
	pic = buf;
	pic += "\\res\\htm\\Add.htm";
	CDialogEx::OnInitDialog();
	VARIANT vt;
	COleVariant vaUrl = _T(pic);
	m_web_add.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
	return TRUE;
	//return FALSE;
}

void ADD_Travel::OnCbnEditchangeTravelName()
{
	// TODO: 在此添加控件通知处理程序代码

}

//添加图片
void ADD_Travel::OnBnClickedButtonAddpic()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szPathName[MAX_PATH] = { 0 };
	TCHAR szDrive[_MAX_DRIVE] = { 0 };
	TCHAR szDir[_MAX_DIR] = { 0 };
	TCHAR szFname[_MAX_FNAME] = { 0 };
	TCHAR szExt[_MAX_EXT] = { 0 };
	CString szFilePF;//全名
	FILE *fp;
	

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT | OFN_ENABLESIZING | OFN_HIDEREADONLY, _T("图片文件(*.jpg)|*.jpg|所有文件 (*.*)|*.*||"), NULL);
	const int MIN_FILE_NUMBER = 20;                                                           //至少允许选择10个文件
	fileDlg.m_ofn.lpstrFile = new TCHAR[_MAX_PATH * MIN_FILE_NUMBER]; //重新定义缓冲区大小           
	memset(fileDlg.m_ofn.lpstrFile, 0, _MAX_PATH * MIN_FILE_NUMBER);  //初始化定义的缓冲区 
	fileDlg.m_ofn.nMaxFile = _MAX_PATH * MIN_FILE_NUMBER;

	if (IDOK == fileDlg.DoModal())
	{
		POSITION pos = fileDlg.GetStartPosition();
		while(NULL != pos)
		{
			szFilePF = fileDlg.GetNextPathName(pos);
			int i;
			for (i = 0;i < newTravel.pics.size();i++)
			{
				if (newTravel.pics[i].fileName.Compare(szFilePF) == 0)
				{
					break;
				}
			}
			if (i < newTravel.pics.size())
			{
				SetDlgItemText(IDC_STATIC_Add_tip, "已经替您去除了重复项！");
				continue;
			}
		
			_splitpath(szFilePF, szDrive, szDir, szFname, szExt);
			fp = fopen(szFilePF, "rb");  /*打开当前目录名为CLIB的文件只读*/
			Cexif exif;
			EXIFINFO exifinfo;
			exif.DecodeExif(fp);
			exif.getExifinfo(&exifinfo);
			fclose(fp);
			CString fileName;
			fileName += szFname;
			fileName += ".";
			fileName + szExt;
			
			Node node(szFilePF, szFname, exifinfo.Longitude, exifinfo.Latitude, exifinfo.DateTime, Match_City(exifinfo.Longitude, exifinfo.Latitude));///////////////文件全名
			newTravel.pics.push_back(node);
			if (newTravel.starttime.Compare("") == 0)
			{
				newTravel.starttime = exifinfo.DateTime;
				newTravel.lasttime = exifinfo.DateTime;
			}
			else
			{
				newTravel.lasttime = exifinfo.DateTime;
			}
			m_Add_Pics.AddString(szFname);
		}
	}
	else
	{
		return;
	}
	delete[] fileDlg.m_ofn.lpstrFile;     //释放内存

	m_Add_Pics.SetCurSel(0);

	SetDlgItemText(IDC_EDIT_Add_PathName, szDir);

	sort(newTravel.pics.begin(), newTravel.pics.end(), sort_by_time);
	vector<Node>::iterator it;
	it = newTravel.pics.begin();
	MakeMap map;
	if (!map.File_Edit("C:\\Users\\kanglb\\Desktop\\map\\map.htm", newTravel.pics.begin(), newTravel.pics.end(), it))
		MessageBox("地图生成失败！");
	VARIANT vt;
	COleVariant vaUrl = _T("C:\\Users\\kanglb\\Desktop\\map\\map.htm");

	m_web_add.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
}

//////////////////////////
void ADD_Travel::OnCbnSelchangeComboAddTravelname()
{
	// TODO: 在此添加控件通知处理程序代码
	CString travelName;
	save_style = SAVE;
	int nIndex = m_Add_TravelName.GetCurSel();
	if (nIndex == 0)
	{
		save_style = CREATE;
		MessageBox("这是新建的旅程哦！");
		usr.select_travel = new Travel(travelName);
		usr.travel.push_back(*usr.select_travel);
		return;
	}
	m_Add_TravelName.GetLBText(nIndex, travelName);

	int i;
	for (i=0;i < usr.travel.size();i++)
	{
		if (usr.travel[i].travelName.CompareNoCase(travelName) == 0)
		{
			MessageBox("我找到了！" + travelName);
			usr.select_travel = &usr.travel[i];
			for (int j = 0;j < usr.select_travel->pics.size();j++)
				MessageBox(usr.select_travel->pics[j].filePF);
			return;
		}
	}

	
	//VARIANT vt;
	//COleVariant vaUrl = _T("C:\\Users\\李展旗\\Desktop\\Map\\map.htm");
	//m_web_add.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
}


void ADD_Travel::OnBnClickedButtonAddSave()
{
	// TODO: 在此添加控件通知处理程序代码

	GetDlgItemText(IDC_EDIT_Add_TravelName, newTravel.travelName);
	GetDlgItemText(IDC_EDIT_Add_Note, newTravel.notes);
	
	if (usr.create_travel(&newTravel))
	{
		for (int i = 0; i < newTravel.pics.size(); i++)
		{
			usr.uploadPic(&newTravel, &newTravel.pics[i]);
		}
	}



}

//内容修改
void ADD_Travel::OnEnChangeEditAddTravelname()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

}

//获得光标
void ADD_Travel::OnEnSetfocusEditAddTravelname()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT_Add_TravelName, "");
}

//失去光标
void ADD_Travel::OnEnKillfocusEditAddTravelname()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tName;
	GetDlgItemText(IDC_EDIT_Add_TravelName, tName);
	for (int i = 0;i < usr.travel.size();i++)
	{
		if (usr.travel[i].travelName.Compare(tName) == 0)
		{
			MessageBox("旅程名已经存在了，请重新起一个吧！");
			GetDlgItem(IDC_EDIT_Add_TravelName)->SetFocus();
			return;
		}
	}
}


HBRUSH ADD_Travel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);   //设置背景透明 
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}

	return hbr;
}

void ADD_Travel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect  rect;
	GetClientRect(&rect);
	CDC  dcMem;   //定义一个工具箱（设备上下文）
	dcMem.CreateCompatibleDC(&dc);///建立关联DC 
	CBitmap  bmpBackground;   //位图对象
	bmpBackground.LoadBitmap(IDB_BITMAP1);   //IDB_BITMAP是你自己的图对应的ID  
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


void ADD_Travel::OnCbnSelchangeComboAddFilename()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_Add_Pics.GetCurSel();
	CString PicName;
	m_Add_Pics.GetLBText(nIndex, PicName);
	for (int i = 0; i < newTravel.pics.size();i++)
	{
		SetDlgItemText(IDC_EDIT_Add_PicTime, newTravel.pics[i].time);
		SetDlgItemText(IDC_EDIT_Add_Lon, newTravel.pics[i].longitude);
		SetDlgItemText(IDC_EDIT_Add_Lat, newTravel.pics[i].latitude);
		SetDlgItemText(IDC_EDIT_Add_Location, newTravel.pics[i].Location);
		return;
	}
}
