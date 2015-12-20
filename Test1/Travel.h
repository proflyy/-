#pragma once

#include "stdafx.h"
#include "Node.h"
using namespace std;
class Travel
{
public:
	CString travelName;		//生成文件名：travelName.html
	CString starttime;		//旅程时间
	CString lasttime;
	CString notes;		//旅程纪录

	//Node *current;
	//Node *startNode;		//点链表头
	//Node *endNode;

	vector<Node> pics;

	Travel() {
		//Node *current = NULL;
		//Node *startNode = NULL;		//点链表头
		//Node *endNode = NULL;
	}
	Travel(CString tName) :travelName(tName), starttime(""), lasttime(""), notes("") {
		//Node *current = NULL;
		//Node *startNode = NULL;		//点链表头
		//Node *endNode = NULL;
	}
	~Travel() {}
	void addNode(Node *node);
};

void Travel::addNode(Node *node)
{

}