// EDIT_Travel.cpp : 实现文件
//

#include "stdafx.h"
#include "Test1.h"
#include "EDIT_Travel.h"
#include "afxdialogex.h"


// EDIT_Travel 对话框

IMPLEMENT_DYNAMIC(EDIT_Travel, CDialogEx)

EDIT_Travel::EDIT_Travel(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_EDIT, pParent)
{

}

EDIT_Travel::~EDIT_Travel()
{
}

void EDIT_Travel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_EDIT_TravelName, m_Edit_TravelName);
	DDX_Control(pDX, IDC_EDIT_EDIT_Node, m_Edit_Nodes);
	DDX_Control(pDX, IDC_EXPLORER1, m_Edit_web);
	DDX_Control(pDX, IDC_COMBO_Edit_PicName, m_Edit_PicName);
}


BEGIN_MESSAGE_MAP(EDIT_Travel, CDialogEx)
	ON_CBN_SETFOCUS(IDC_COMBO_EDIT_TravelName, &EDIT_Travel::OnCbnSetfocusComboEditTravelname)
	ON_CBN_SELCHANGE(IDC_COMBO_EDIT_TravelName, &EDIT_Travel::OnCbnSelchangeComboEditTravelname)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_EDIT, &EDIT_Travel::OnBnClickedButtonEditEdit)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_OnDel, &EDIT_Travel::OnBnClickedButtonEditOndel)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_EDIT_DelPic, &EDIT_Travel::OnBnClickedButtonEditDelpic)
	ON_BN_CLICKED(IDC_BUTTON3, &EDIT_Travel::OnBnClickedButton3)
	ON_CBN_SETFOCUS(IDC_COMBO_Edit_PicName, &EDIT_Travel::OnCbnSetfocusComboEditPicname)
END_MESSAGE_MAP()


// EDIT_Travel 消息处理程序
BOOL EDIT_Travel::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Edit_TravelName.InsertString(0, "-----请选择旅程-----");
	m_Edit_TravelName.SetCurSel(0);

	char buf[256];
	GetCurrentDirectory(256, buf);  //得到当前工作路径
	CString pic;
	pic = buf;
	pic += "\\res\\htm\\Edit.htm";
	CDialogEx::OnInitDialog();
	VARIANT vt;
	COleVariant vaUrl = _T(pic);
	m_Edit_web.Navigate2(vaUrl, &vt, &vt, &vt, &vt);

	return TRUE;
	//return FALSE;
}

void EDIT_Travel::OnCbnSetfocusComboEditTravelname()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Edit_TravelName.ResetContent();
	int i;
	for (i = 0;i < usr.travel.size();i++)
	{
		m_Edit_TravelName.AddString(usr.travel[i].travelName);
	}
	//m_Edit_TravelName.SetCurSel(0);
}


void EDIT_Travel::OnCbnSelchangeComboEditTravelname()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	CString travelName;
	int nIndex = m_Edit_TravelName.GetCurSel();
	m_Edit_TravelName.GetLBText(nIndex, travelName);
	for (i = 0;i < usr.travel.size();i++)
	{
		if (usr.travel[i].travelName.Compare(travelName) == 0)
		{
			//MessageBox("我找到了！" + travelName);
			select_travel = i;
			travelBuf.travelName = usr.travel[i].travelName;
			travelBuf.notes = usr.travel[i].notes;
			SetDlgItemText(IDC_EDIT_EDIT_Node, usr.travel[i].notes);//选中旅行名称  显示

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
	m_Edit_PicName.ResetContent();
	vector<Node>::iterator itt;
	for (itt = usr.travel[i].pics.begin();itt != usr.travel[i].pics.end();itt++)
	{
		m_Edit_PicName.AddString(itt->fileName);
	}
	MakeMap map;
	vector<Node>::iterator it = usr.travel[i].pics.begin();
	if (!map.File_Edit("C:\\Users\\kanglb\\Desktop\\map\\map.htm", usr.travel[i].pics.begin(), usr.travel[i].pics.end(), it))
		MessageBox("地图生成失败！");
	VARIANT vt;
	COleVariant vaUrl = _T("C:\\Users\\kanglb\\Desktop\\map\\map.htm");

	m_Edit_web.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
}

//编辑行程
void EDIT_Travel::OnBnClickedButtonEditEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret;
	ret = AfxMessageBox(_T("保存修改？"), MB_ICONQUESTION | MB_OKCANCEL);
	if (ret == IDOK)
	{
		CString travelName, notes;
		GetDlgItemText(IDC_COMBO_EDIT_TravelName, travelName);
		GetDlgItemText(IDC_EDIT_EDIT_Node, notes);
		if (usr.updataTravel(&travelBuf, travelName, notes, 1))
		{
			m_Edit_TravelName.ResetContent();
			int i;
			for (i = 0;i < usr.travel.size();i++)
			{
				m_Edit_TravelName.AddString(usr.travel[i].travelName);
			}
		}
		return;
	}
	MessageBox("没有修改~");
	SetDlgItemText(IDC_COMBO_EDIT_TravelName, travelBuf.travelName);
	SetDlgItemText(IDC_EDIT_EDIT_Node, travelBuf.notes);
	//m_Edit_TravelName.OnShowWindow(FALSE, 0);
}

//删除旅程
void EDIT_Travel::OnBnClickedButtonEditOndel()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret;
	ret = AfxMessageBox(_T("确定删除？"), MB_ICONEXCLAMATION | MB_OKCANCEL);
	if (ret == IDOK)
	{
		if (usr.updataTravel(&travelBuf, "", "", 0))
		{
			m_Edit_TravelName.ResetContent();
			int i;
			for (i = 0;i < usr.travel.size();i++)
			{
				m_Edit_TravelName.AddString(usr.travel[i].travelName);
			}
		}
		return;
	}
	MessageBox("没有修改~");
	SetDlgItemText(IDC_COMBO_EDIT_TravelName, usr.select_travel->travelName);
	SetDlgItemText(IDC_EDIT_EDIT_Node, usr.select_travel->notes);

}


HBRUSH EDIT_Travel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);   //设置背景透明 
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	return hbr;
}


void EDIT_Travel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect  rect;
	GetClientRect(&rect);
	CDC  dcMem;   //定义一个工具箱（设备上下文）
	dcMem.CreateCompatibleDC(&dc);///建立关联DC 
	CBitmap  bmpBackground;   //位图对象
	bmpBackground.LoadBitmap(IDB_BITMAP2);   //IDB_BITMAP是你自己的图对应的ID  
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


void EDIT_Travel::OnBnClickedButtonEditDelpic()
{
	// TODO: 在此添加控件通知处理程序代码
	CString picName;					
	//CString travelName;
	GetDlgItemText(IDC_COMBO_EDIT_TravelName, travelBuf.travelName);
	GetDlgItemText(IDC_COMBO_Edit_PicName, picName);
	if(usr.deletePic(&usr.travel[select_travel], picName))
	{
		m_Edit_PicName.ResetContent();
		int i;
		for (i = 0;i < usr.travel[select_travel].pics.size();i++)
		{
			m_Edit_PicName.AddString(usr.travel[select_travel].pics[i].fileName);
		}
	}
	if (usr.travel[select_travel].pics.size() <= 0)
	{
		return;
	}
	sort(usr.travel[select_travel].pics.begin(), usr.travel[select_travel].pics.end(), sort_by_time);
	vector<Node>::iterator it;
	it = usr.travel[select_travel].pics.begin();
	MakeMap map;
	if (!map.File_Edit("C:\\Users\\kanglb\\Desktop\\map\\map.htm", usr.travel[select_travel].pics.begin(), usr.travel[select_travel].pics.end(), it))
		MessageBox("地图生成失败！");
	VARIANT vt;
	COleVariant vaUrl = _T("C:\\Users\\kanglb\\Desktop\\map\\map.htm");

	m_Edit_web.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
}


void EDIT_Travel::OnBnClickedButton3()
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
		while (NULL != pos)
		{
			szFilePF = fileDlg.GetNextPathName(pos);
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

			//MessageBox(szFilePF+ Match_City(exifinfo.Longitude, exifinfo.Latitude));
			Node node(fileName, szFilePF, exifinfo.Longitude, exifinfo.Latitude, exifinfo.DateTime, Match_City(exifinfo.Longitude, exifinfo.Latitude));
			pictures.push_back(node);
			m_Edit_PicName.AddString(szFname);
		}
	}
	delete[] fileDlg.m_ofn.lpstrFile;     //最后别忘了释放内存


	SetDlgItemText(IDC_EDIT_Add_PathName, szDir);

	sort(pictures.begin(), pictures.end(), sort_by_time);
	vector<Node>::iterator it = pictures.begin();
	MakeMap map;
	if (!map.File_Edit("C:\\Users\\kanglb\\Desktop\\map\\map.htm", pictures.begin(), pictures.end(),it))
		MessageBox("地图生成失败！");
	VARIANT vt;
	COleVariant vaUrl = _T("C:\\Users\\kanglb\\Desktop\\map\\map.htm");

	m_Edit_web.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
}


void EDIT_Travel::OnCbnSetfocusComboEditPicname()
{
	// TODO: 在此添加控件通知处理程序代码
}
