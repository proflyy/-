#pragma once
#include "explorer2.h"
#include "afxwin.h"
#define CREATE	1
#define SAVE	0
using namespace std;
// ADD_Travel 对话框

class ADD_Travel : public CDialogEx
{
	DECLARE_DYNAMIC(ADD_Travel)

public:
	ADD_Travel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ADD_Travel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	int save_style;//
	CExplorer2 m_web_add;//没用
	//vector<Node> openFiles;
	Travel newTravel;
	CString ADD_Travel::BootOpenDialog();///////通知处理程序代码
	afx_msg void OnBnClickedButtonAddpic();//显示地图
	// 经度
	double m_Add_lng;
	double m_Add_lat;
	CString m_Add_PicTime;
	CString m_Add_Location;
	CComboBox m_Add_TravelName;
	afx_msg void OnCbnEditchangeTravelName();//编辑行程名称
	afx_msg void OnCbnSelchangeComboAddTravelname();//查重旅程名称//查询
	afx_msg void OnBnClickedButtonAddSave();//照片保存到数组
	afx_msg void OnEnChangeEditAddTravelname();///////没用，以后修改
	afx_msg void OnEnSetfocusEditAddTravelname();///////获得光标，处理
	afx_msg void OnEnKillfocusEditAddTravelname();////////失去光标
	CComboBox m_Add_Pics;//文件名称
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeComboAddFilename();//显示图片信息
};
