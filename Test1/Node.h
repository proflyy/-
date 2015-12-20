#pragma once
class Node
{
public:
	CString time;			//游览时间
	CString longitude;		//经度
	CString latitude;		//纬度
	CString Location;		//地点
	Node *next;
	CString filePF;		//文件地址
	CString fileName;
	Node(){}
	Node(CString fileName, CString filePF, double lng, double lat, CString time, CString Location) : fileName(fileName), filePF(filePF), time(time), Location(Location) {
		longitude.Format("%f", lng);
		latitude.Format("%f", lat);
	}
	~Node() {}
//	Node *preNode();
	Node *nextNode();
	BOOL NodeInfo();
	BOOL addNode(CString fileName);
	BOOL delNode(CString fileName);
	//bool operator< (const Node &a)  const;
	friend bool sort_by_time (const Node &a, const Node &b);
};

