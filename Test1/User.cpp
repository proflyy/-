#include "stdafx.h"
#include "User.h"

User::User()
{
}
User::~User()
{
}

//登录
BOOL User::login(CString passwd)
{
	//return TRUE;
	Json::Value sendJson;
	Json::Value recvJson;
	char sendbuf[1024];
	char recvbuf[1024];
	//MessageBox(0, "Test", "Login", 0);
	sendJson["com"] = Json::Value(1);
	Json::Value meg;
	meg["loginName"] = Json::Value(loginName);
	meg["userPwd"] = Json::Value(passwd);
	sendJson["meg"] = meg;
	//std::string out = sendJson.toStyledString();
	strcpy(sendbuf, sendJson.toStyledString().c_str());
	con.Connect();
	con.Send(sendbuf, 1024);
	con.Recv(recvbuf, 1024);
	con.Close();
	json_reader->parse(recvbuf, recvJson);
	if (recvJson.get("state", 0) == 200)
	{
		//MessageBox(0, "Success", "Login", 0);
		return TRUE;
	}
	else if(recvJson.get("state", 0) == 202)
	{
		MessageBox(0, "用户名或密码错误！", "登录", 0);
	}
	else
	{
		MessageBox(0, "服务器连接错误！", "登录", 0);
	}
	return FALSE;
}
//注册
BOOL User::regist(CString loginName, CString photo, CString userName, CString passwd)
{
	//return TRUE;
	Json::Value sendJson;
	Json::Value recvJson;
	char sendbuf[1024];
	char recvbuf[1024];
	sendJson["com"] = Json::Value(2);
	Json::Value meg;
	meg["loginName"] = Json::Value(loginName);
	meg["userName"] = Json::Value(userName);
	meg["userPwd"] = Json::Value(passwd);
	meg["userPhoto"] = Json::Value(photo);
	meg["userAddr"] = Json::Value("");
	meg["userSex"] = Json::Value("");
	sendJson["meg"] = meg;
	strcpy(sendbuf, sendJson.toStyledString().c_str());
	con.Connect();
	con.Send(sendbuf, 1024);
	con.Recv(recvbuf, 1024);
	con.Close();
	json_reader->parse(recvbuf, recvJson);
	if (recvJson.get("state", 0) == 200)
	{
		MessageBox(0, "注册成功，请登录使用！", "注册", 0);
		return TRUE;
	}
	else if (recvJson.get("state", 0) == 204)
	{
		MessageBox(0, "用户已经存在！", "注册", 0);
		return FALSE;
	}
	else
	{
		MessageBox(0, "服务器连接错误！", "注册", 0);
		return FALSE;
	}
	return TRUE;
}
//加载信息
BOOL User::loading(CString passwd)
{
	//return TRUE;
	Json::Value sendJson;
	Json::Value recvJson;
	char sendbuf[1024];
	sendJson["com"] = Json::Value(3);
	Json::Value meg;
	meg["loginName"] = Json::Value(loginName);
	meg["userPwd"] = Json::Value(passwd);
	sendJson["meg"] = meg;
	strcpy(sendbuf, sendJson.toStyledString().c_str());

	CString recvbuf;
	char buf[129];
	int i;
	con.Connect();
	con.Send(sendbuf, 1024);

	while ((i = con.Recv(buf, 128)) > 0)
	{
		buf[i] = '\0';
		recvbuf += buf;
	}
	con.Close();

	recvbuf = U2G(recvbuf);

	json_reader->parse(recvbuf.GetBuffer(), recvJson);
	meg = recvJson["ret_meg"];
	int n = meg.size();
	
	for (int i = 0;i < n;i++)
	{
		Travel t;
		t.travelName = meg[i]["travelName"].asString().c_str();
		t.notes = meg[i]["experience"].asString().c_str();
		t.starttime = meg[i]["start_time"].asString().c_str();
		t.lasttime = meg[i]["end_time"].asString().c_str();
		for (int j = 0;j < meg[i]["pictureInfo"].size();j++)
		{
			Node node;
			node.fileName	 = meg[i]["pictureInfo"][j]["pictureName"].asString().c_str();
			node.time		 = meg[i]["pictureInfo"][j]["time"].asString().c_str();
			node.longitude	 = meg[i]["pictureInfo"][j]["longituid"].asString().c_str();
			node.latitude	 = meg[i]["pictureInfo"][j]["latituid"].asString().c_str();
			t.pics.push_back(node);
		}
		usr.travel.push_back(t);
	}
	//MessageBox(0, recvbuf, "加载", 0);
	return TRUE;
}
//创建行程
BOOL User::create_travel(Travel * t)
{
	//return TRUE;
	Json::Value sendJson;
	Json::Value recvJson;
	
	Json::Value meg;
	sendJson["com"] = Json::Value(4);
	meg["loginName"] = Json::Value(loginName);
	meg["key"] = Json::Value("");
	meg["travelName"] = Json::Value(t->travelName);
	meg["experience"] = Json::Value(t->notes);
	sendJson["meg"] = meg;
	
	char *sendbuf;
	char *recvbuf;
	sendbuf = new char[1024];
	recvbuf = new char[1024];
	
	strcpy(sendbuf, sendJson.toStyledString().c_str());
	con.Connect();
	con.Send(sendbuf, 1024);
	con.Recv(recvbuf, 1024);
	con.Close();
	json_reader->parse(recvbuf, recvJson);
	if (recvJson.get("state", 0) == 200)
	{
		//MessageBox(0, sendbuf, "发送", 0);
		//MessageBox(0, recvbuf, "创建", 0);
		MessageBox(0, "新增行程成功！", "创建", 0);
		usr.travel.push_back(*t);
		return TRUE;
	}
	else if (recvJson.get("state", 0) == 205)
	{
		MessageBox(0, "行程已经存在了！", "创建", 0);
	}
	delete sendbuf;
	delete recvbuf;
	return FALSE;
}
//上载照片
BOOL User::uploadPic(Travel *t, Node * node)
{
	//return TRUE;
	
	Json::Value sendJson;
	Json::Value recvJson;
	Json::Value meg;
	sendJson["com"] = Json::Value(6);
	meg["loginName"] = Json::Value(loginName);
	meg["key"] = Json::Value("");
	meg["travelName"] = Json::Value(t->travelName);
	meg["pictureName"] = Json::Value(node->filePF);
	meg["cameraTime"] = Json::Value(node->time);
	meg["cameraPosition"] = Json::Value(node->Location);
	meg["longituid"] = Json::Value(node->longitude);
	meg["latituid"] = Json::Value(node->latitude);
	meg["pictureStream"] = Json::Value("");
	sendJson["meg"] = meg;
	char *sendbuf;
	char *recvbuf;
	sendbuf = new char[1024];
	recvbuf = new char[1024];
	strcpy(sendbuf, sendJson.toStyledString().c_str());

	//MessageBox(0, sendbuf, "发送：上载照片", 0);
	con.Connect();
	con.Send(sendbuf, sizeof(sendbuf));
	con.Recv(recvbuf, 1024);
	con.Close();
	json_reader->parse(recvbuf, recvJson);
	delete sendbuf;
	delete recvbuf;
	if (recvJson.get("state", 0) == 200)
	{
		//t->pics.push_back(*node);
		return TRUE;
	}
	MessageBox(0, recvbuf, "接收：上载照片失败", 0);
	return FALSE;
}
//修改、删除行程
BOOL User::updataTravel(Travel *t, CString newTravelName, CString newNodes, int tag)
{
	//return TRUE;
	Json::Value sendJson;
	Json::Value recvJson;

	Json::Value meg;
	sendJson["com"] = Json::Value(7);
	meg["loginName"] = Json::Value(loginName);
	meg["key"] = Json::Value("");
	meg["travelName"] = Json::Value(t->travelName);
	meg["travelNameNew"] = Json::Value(newTravelName);
	meg["experience"] = Json::Value(newNodes);
	if(tag == 1)
		meg["tag"] = Json::Value("1");				//修改
	else
		meg["tag"] = Json::Value("0");				//删除
	sendJson["meg"] = meg;

	char *sendbuf;
	char *recvbuf;
	sendbuf = new char[1024];
	recvbuf = new char[1024];

	strcpy(sendbuf, sendJson.toStyledString().c_str());
	con.Connect();
	con.Send(sendbuf, 1024);
	con.Recv(recvbuf, 1024);
	con.Close();
	json_reader->parse(recvbuf, recvJson);
	//MessageBox(0, sendbuf, "发送：编辑行程", 0);
	//MessageBox(0, recvbuf, "接收：编辑行程", 0);
	if (recvJson.get("state", 0) == 200)
	{
		if (tag == 1)
		{
			vector<Travel>::iterator it;
			for (it = travel.begin();it != travel.end();it++) {
				if (it->travelName.Compare(t->travelName) == 0)
				{
					it->travelName = newTravelName;
					it->notes = newNodes;
					break;
				}
			}
		}
		else
		{
			vector<Travel>::iterator it;
			for (it = travel.begin();it != travel.end();it++) {
				if (it->travelName.Compare(t->travelName) == 0)
				{
					travel.erase(it);
					break;
				}
			}
		}
		

		return TRUE;
	}
	delete sendbuf;
	delete recvbuf;
	return FALSE;
}
//删除照片
BOOL User::deletePic(Travel *t, CString picName)
{
	//return TRUE;
	Json::Value sendJson;
	Json::Value recvJson;
	Json::Value meg;
	sendJson["com"] = Json::Value(8);
	meg["loginName"] = Json::Value(loginName);
	meg["key"] = Json::Value("");
	meg["travelName"] = Json::Value(t->travelName);
	meg["pictureName"] = Json::Value(picName);
	sendJson["meg"] = meg;
	char *sendbuf;
	char *recvbuf;
	sendbuf = new char[1024];
	recvbuf = new char[1024];
	strcpy(sendbuf, sendJson.toStyledString().c_str());

	MessageBox(0, sendbuf, "发送：删除照片", 0);
	con.Connect();
	con.Send(sendbuf, sizeof(sendbuf));
	con.Recv(recvbuf, 1024);
	con.Close();
	json_reader->parse(recvbuf, recvJson);
	delete sendbuf;
	delete recvbuf;
	if (recvJson.get("state", 0) == 200)
	{
		//t->pics.push_back(*node);
		vector<Node>::iterator it;
		for (it = t->pics.begin();it != t->pics.end();it++) {
			if (it->fileName.Compare(picName) == 0)
			{
				t->pics.erase(it);
				break;
			}
		}
		return TRUE;
	}
	MessageBox(0, recvbuf, "接收：删除照片失败", 0);
	return FALSE;
}