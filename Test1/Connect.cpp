#include "stdafx.h"
#include "Connect.h"


ConnectStruct::ConnectStruct()
{
	StartupWSA();
}


ConnectStruct::~ConnectStruct()
{
}


int ConnectStruct::StartupWSA()
{
	WSADATA wsa;
	/*初始化socket资源*/
	if (WSAStartup(MAKEWORD(1, 1), &wsa) == 0)
	{
		return 1;   //代表成功
	}
	return -1;		//代表失败
}


int ConnectStruct::CleanupWSA()
{
	return 1;
}


int ConnectStruct::BuildSOCKET()
{
	Client_Sock = socket(AF_INET, SOCK_STREAM, 0);
	return 1;
}


int ConnectStruct::Connect()
{

	BuildSOCKET();
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(PORT);
	addrSrv.sin_addr.S_un.S_addr = *(unsigned long *)gethostbyname(ADDR)->h_addr;
	ret = connect(Client_Sock, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (ret == 0)
	{
		//MessageBox(0, "success", "Connect", 0);
		return 1;
	}
	else
		return ret;
}

int ConnectStruct::Send(const char *buf, int len)
{

	std::string str;
	len = ConvertGBKToUtf8(str, buf);
	char output[1024];
	strcpy(output, str.c_str());
	return send(Client_Sock, output, len, 0);
}


int ConnectStruct::Recv(char *buf, int len)
{
	return recv(Client_Sock, buf, len, 0);
}


int ConnectStruct::Close()
{
	return closesocket(Client_Sock);
}

int ConnectStruct::ConvertGBKToUtf8(std::string& amp, std::string strGBK)
{
	int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK.c_str(), -1, NULL, 0);
	unsigned short * wszUtf8 = new unsigned short[len + 1];
	memset(wszUtf8, 0, len * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK.c_str(), -1, (LPWSTR)wszUtf8, len);
	len = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = new char[len + 1];
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)wszUtf8, -1, szUtf8, len, NULL, NULL);
	//strGBK = szUtf8; 
	amp = szUtf8;
	delete[] szUtf8;
	delete[] wszUtf8;
	return len;
}