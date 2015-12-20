// EDIT_Travel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test1.h"
#include "EDIT_Travel.h"
#include "afxdialogex.h"


// EDIT_Travel �Ի���

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


// EDIT_Travel ��Ϣ�������
BOOL EDIT_Travel::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Edit_TravelName.InsertString(0, "-----��ѡ���ó�-----");
	m_Edit_TravelName.SetCurSel(0);

	char buf[256];
	GetCurrentDirectory(256, buf);  //�õ���ǰ����·��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i;
	CString travelName;
	int nIndex = m_Edit_TravelName.GetCurSel();
	m_Edit_TravelName.GetLBText(nIndex, travelName);
	for (i = 0;i < usr.travel.size();i++)
	{
		if (usr.travel[i].travelName.Compare(travelName) == 0)
		{
			//MessageBox("���ҵ��ˣ�" + travelName);
			select_travel = i;
			travelBuf.travelName = usr.travel[i].travelName;
			travelBuf.notes = usr.travel[i].notes;
			SetDlgItemText(IDC_EDIT_EDIT_Node, usr.travel[i].notes);//ѡ����������  ��ʾ

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
	m_Edit_PicName.ResetContent();
	vector<Node>::iterator itt;
	for (itt = usr.travel[i].pics.begin();itt != usr.travel[i].pics.end();itt++)
	{
		m_Edit_PicName.AddString(itt->fileName);
	}
	MakeMap map;
	vector<Node>::iterator it = usr.travel[i].pics.begin();
	if (!map.File_Edit("C:\\Users\\kanglb\\Desktop\\map\\map.htm", usr.travel[i].pics.begin(), usr.travel[i].pics.end(), it))
		MessageBox("��ͼ����ʧ�ܣ�");
	VARIANT vt;
	COleVariant vaUrl = _T("C:\\Users\\kanglb\\Desktop\\map\\map.htm");

	m_Edit_web.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
}

//�༭�г�
void EDIT_Travel::OnBnClickedButtonEditEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret;
	ret = AfxMessageBox(_T("�����޸ģ�"), MB_ICONQUESTION | MB_OKCANCEL);
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
	MessageBox("û���޸�~");
	SetDlgItemText(IDC_COMBO_EDIT_TravelName, travelBuf.travelName);
	SetDlgItemText(IDC_EDIT_EDIT_Node, travelBuf.notes);
	//m_Edit_TravelName.OnShowWindow(FALSE, 0);
}

//ɾ���ó�
void EDIT_Travel::OnBnClickedButtonEditOndel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret;
	ret = AfxMessageBox(_T("ȷ��ɾ����"), MB_ICONEXCLAMATION | MB_OKCANCEL);
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
	MessageBox("û���޸�~");
	SetDlgItemText(IDC_COMBO_EDIT_TravelName, usr.select_travel->travelName);
	SetDlgItemText(IDC_EDIT_EDIT_Node, usr.select_travel->notes);

}


HBRUSH EDIT_Travel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);   //���ñ���͸�� 
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	return hbr;
}


void EDIT_Travel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect  rect;
	GetClientRect(&rect);
	CDC  dcMem;   //����һ�������䣨�豸�����ģ�
	dcMem.CreateCompatibleDC(&dc);///��������DC 
	CBitmap  bmpBackground;   //λͼ����
	bmpBackground.LoadBitmap(IDB_BITMAP2);   //IDB_BITMAP�����Լ���ͼ��Ӧ��ID  
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


void EDIT_Travel::OnBnClickedButtonEditDelpic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox("��ͼ����ʧ�ܣ�");
	VARIANT vt;
	COleVariant vaUrl = _T("C:\\Users\\kanglb\\Desktop\\map\\map.htm");

	m_Edit_web.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
}


void EDIT_Travel::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szPathName[MAX_PATH] = { 0 };
	TCHAR szDrive[_MAX_DRIVE] = { 0 };
	TCHAR szDir[_MAX_DIR] = { 0 };
	TCHAR szFname[_MAX_FNAME] = { 0 };
	TCHAR szExt[_MAX_EXT] = { 0 };
	CString szFilePF;//ȫ��
	FILE *fp;

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT | OFN_ENABLESIZING | OFN_HIDEREADONLY, _T("ͼƬ�ļ�(*.jpg)|*.jpg|�����ļ� (*.*)|*.*||"), NULL);
	const int MIN_FILE_NUMBER = 20;                                                           //��������ѡ��10���ļ�
	fileDlg.m_ofn.lpstrFile = new TCHAR[_MAX_PATH * MIN_FILE_NUMBER]; //���¶��建������С           
	memset(fileDlg.m_ofn.lpstrFile, 0, _MAX_PATH * MIN_FILE_NUMBER);  //��ʼ������Ļ����� 
	fileDlg.m_ofn.nMaxFile = _MAX_PATH * MIN_FILE_NUMBER;
	if (IDOK == fileDlg.DoModal())
	{
		POSITION pos = fileDlg.GetStartPosition();
		while (NULL != pos)
		{
			szFilePF = fileDlg.GetNextPathName(pos);
			_splitpath(szFilePF, szDrive, szDir, szFname, szExt);
			fp = fopen(szFilePF, "rb");  /*�򿪵�ǰĿ¼��ΪCLIB���ļ�ֻ��*/
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
	delete[] fileDlg.m_ofn.lpstrFile;     //���������ͷ��ڴ�


	SetDlgItemText(IDC_EDIT_Add_PathName, szDir);

	sort(pictures.begin(), pictures.end(), sort_by_time);
	vector<Node>::iterator it = pictures.begin();
	MakeMap map;
	if (!map.File_Edit("C:\\Users\\kanglb\\Desktop\\map\\map.htm", pictures.begin(), pictures.end(),it))
		MessageBox("��ͼ����ʧ�ܣ�");
	VARIANT vt;
	COleVariant vaUrl = _T("C:\\Users\\kanglb\\Desktop\\map\\map.htm");

	m_Edit_web.Navigate2(vaUrl, &vt, &vt, &vt, &vt);
}


void EDIT_Travel::OnCbnSetfocusComboEditPicname()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
