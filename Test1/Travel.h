#pragma once

#include "stdafx.h"
#include "Node.h"
using namespace std;
class Travel
{
public:
	CString travelName;		//�����ļ�����travelName.html
	CString starttime;		//�ó�ʱ��
	CString lasttime;
	CString notes;		//�ó̼�¼

	//Node *current;
	//Node *startNode;		//������ͷ
	//Node *endNode;

	vector<Node> pics;

	Travel() {
		//Node *current = NULL;
		//Node *startNode = NULL;		//������ͷ
		//Node *endNode = NULL;
	}
	Travel(CString tName) :travelName(tName), starttime(""), lasttime(""), notes("") {
		//Node *current = NULL;
		//Node *startNode = NULL;		//������ͷ
		//Node *endNode = NULL;
	}
	~Travel() {}
	void addNode(Node *node);
};

void Travel::addNode(Node *node)
{

}