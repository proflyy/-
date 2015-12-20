// CreateUser.cpp : 实现文件
//

#include "stdafx.h"
#include "Test1.h"
#include "CreateUser.h"
#include "afxdialogex.h"


// CreateUser 对话框

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


// CreateUser 消息处理程序


void CreateUser::OnBnClickedCdCreateusr()
{
	// TODO: 在此添加控件通知处理程序代码
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
		MessageBox(_T("请输入用户名！"));
		//SetFocus();
		return;
	}
	if (passwd.IsEmpty())
	{
		MessageBox(_T("请输入密码！"));
		return;
	}
	if (passwd.Compare(passwd_check))
	{
		MessageBox("两次输入的密码不一致！");
		return;
	}
	usr.regist(loginName, photo, userName, passwd);
	CreateUser::OnOK();
}


void CreateUser::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CreateUser::OnCancel();
}


void CreateUser::OnEnKillfocusEditCuPasswdcheck()
{
	// TODO: 在此添加控件通知处理程序代码
	CString passwd, passwd_check;
	GetDlgItemText(IDC_EDIT_CU_Passwd, passwd);
	GetDlgItemText(IDC_EDIT_CU_PasswdCheck, passwd_check);
	if (passwd.Compare(passwd_check) != 0)
	{
		MessageBox("两次输入的密码不一致！");
		SetDlgItemText(IDC_EDIT_CU_Passwd, "");
		SetDlgItemText(IDC_EDIT_CU_PasswdCheck, "");
	}
}


HBRUSH CreateUser::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(255, 255, 0)); //字体颜色
		//pDC->SetBkColor(RGB(0, 0, 255)); //字体背景色
		pDC->SetBkMode(TRANSPARENT);   //设置背景透明 
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	return hbr;

}


void CreateUser::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect  rect;
	GetClientRect(&rect);
	CDC  dcMem;   //定义一个工具箱（设备上下文）
	dcMem.CreateCompatibleDC(&dc);///建立关联DC 
	CBitmap  bmpBackground;   //位图对象
	bmpBackground.LoadBitmap(IDB_BITMAP5);   //IDB_BITMAP是你自己的图对应的ID  
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
