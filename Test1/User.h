#pragma once
//#include<vector>
#include "stdafx.h"
#include <json/json.h>
#include "Travel.h"
#include "Connect.h"
using namespace std;
class User
{
	
public:
	CString loginName;
	CString photo;
	CString userName;
	vector <Travel> travel;
	Travel * select_travel;
	//char send[1024];
	//char buf[1024];
	Json::Reader *json_reader = new Json::Reader(Json::Features::strictMode());
	ConnectStruct con = ConnectStruct();		//����SOCKET
	User();
	~User();
	BOOL login(CString passwd);																//��¼						com:1
	BOOL regist(CString loginName, CString photo, CString userName, CString passwd);		//ע���û�					com:2
	BOOL loading(CString passwd);															//�����û���Ϣ				com:3
	BOOL create_travel(Travel * t);															//�½��ó�					com:4
	BOOL uploadPic(Travel *t, Node * node);													//����ͼƬ					com:6
	BOOL downloadPic();																		//����ͼƬ					com:5
	BOOL updataTravel(Travel *t, CString newTravelName, CString newNodes, int tag);			//�޸ġ�ɾ���ó�			com:7
	BOOL deletePic(Travel *t, CString picName);												//ɾ��ͼƬ					com:8
	//Travel * searchTravel(int style, CString value);
};
