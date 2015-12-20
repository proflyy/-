#pragma once
#define ADDR "127.0.0.1"
#define PORT 6666
//#define ADDR "bluecare.wicp.net"
//#define PORT 29362
class ConnectStruct
{
protected:

	SOCKET Client_Sock;
	int ret;
public:
	ConnectStruct();
	~ConnectStruct();	
	int StartupWSA();

	int BuildSOCKET();
	int CleanupWSA();
	int Close();
	int Connect();
	int Send(const char *buf, int len);
	int Recv(char *buf, int len);
	int ConvertGBKToUtf8(std::string& amp, std::string strGBK);
};

