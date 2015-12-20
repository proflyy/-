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
	ConnectStruct con = ConnectStruct();		//连接SOCKET
	User();
	~User();
	BOOL login(CString passwd);																//登录						com:1
	BOOL regist(CString loginName, CString photo, CString userName, CString passwd);		//注册用户					com:2
	BOOL loading(CString passwd);															//加载用户信息				com:3
	BOOL create_travel(Travel * t);															//新建旅程					com:4
	BOOL uploadPic(Travel *t, Node * node);													//上载图片					com:6
	BOOL downloadPic();																		//下载图片					com:5
	BOOL updataTravel(Travel *t, CString newTravelName, CString newNodes, int tag);			//修改、删除旅程			com:7
	BOOL deletePic(Travel *t, CString picName);												//删除图片					com:8
	//Travel * searchTravel(int style, CString value);
};
