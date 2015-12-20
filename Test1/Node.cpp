#include "stdafx.h"
#include "Node.h"

//
//Node::Node(CString fileName)
//{
//
//}
//
//
//Node::~Node()
//{
//}


Node * Node::nextNode()
{
	return this->next;
}


BOOL Node::NodeInfo()
{
	return TRUE;
}


BOOL Node::addNode(CString fileName)
{

	return TRUE;
}


BOOL Node::delNode(CString fileName)
{

	return TRUE;
}

//bool Node::sort_by_time (const Node &a)  const
//{
//	if (time.CompareNoCase(a.time) < 0)
//		return TRUE;
//	else
//		return FALSE;
//}

bool sort_by_time(const Node &a, const Node &b)
{
	if (a.time.CompareNoCase(b.time) < 0)
		return TRUE;
	else
		return FALSE;
}
