// CreateUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test1.h"
#include "CreateUser.h"
#include "afxdialogex.h"


// CreateUser �Ի���

IMPLEMENT_DYNAMIC(CreateUser, CDialogEx)

CreateUser::CreateUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CreateUsr, pParent)
{

}

CreateUser::~CreateUser()
{
}

void CreateUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CreateUser, CDialogEx)
	ON_BN_CLICKED(IDC_CD_CreateUsr, &CreateUser::OnBnClickedCdCreateusr)
	ON_BN_CLICKED(IDC_Cancel, &CreateUser::OnBnClickedCancel)
	ON_EN_KILLFOCUS(IDC_EDIT_CU_PasswdCheck, &CreateUser::OnEnKillfocusEditCuPasswdcheck)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CreateUser ��Ϣ�������


void CreateUser::OnBnClickedCdCreateusr()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString loginName;
	CString photo;
	CString userName;
	CString passwd;
	CString passwd_check;
	GetDlgItemText(IDC_EDIT_CU_LoginName, loginName);
	GetDlgItemText(IDC_EDIT_CU_UserName, userName);
	GetDlgItemText(IDC_EDIT_CU_Passwd, passwd);
	GetDlgItemText(IDC_EDIT_CU_PasswdCheck, passwd_check);
	if (loginName.IsEmpty())
	{
		MessageBox(_T("�������û�����"));
		//SetFocus();
		return;
	}
	if (passwd.IsEmpty())
	{
		MessageBox(_T("���������룡"));
		return;
	}
	if (passwd.Compare(passwd_check))
	{
		MessageBox("������������벻һ�£�");
		return;
	}
	usr.regist(loginName, photo, userName, passwd);
	CreateUser::OnOK();
}


void CreateUser::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CreateUser::OnCancel();
}


void CreateUser::OnEnKillfocusEditCuPasswdcheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString passwd, passwd_check;
	GetDlgItemText(IDC_EDIT_CU_Passwd, passwd);
	GetDlgItemText(IDC_EDIT_CU_PasswdCheck, passwd_check);
	if (passwd.Compare(passwd_check) != 0)
	{
		MessageBox("������������벻һ�£�");
		SetDlgItemText(IDC_EDIT_CU_Passwd, "");
		SetDlgItemText(IDC_EDIT_CU_PasswdCheck, "");
	}
}


HBRUSH CreateUser::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(255, 255, 0)); //������ɫ
		//pDC->SetBkColor(RGB(0, 0, 255)); //���屳��ɫ
		pDC->SetBkMode(TRANSPARENT);   //���ñ���͸�� 
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	return hbr;

}


void CreateUser::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect  rect;
	GetClientRect(&rect);
	CDC  dcMem;   //����һ�������䣨�豸�����ģ�
	dcMem.CreateCompatibleDC(&dc);///��������DC 
	CBitmap  bmpBackground;   //λͼ����
	bmpBackground.LoadBitmap(IDB_BITMAP5);   //IDB_BITMAP�����Լ���ͼ��Ӧ��ID  
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
