#pragma once
#include <fstream>
#include <string>
class MakeMap
{
public:
	MakeMap();
	~MakeMap();
	static bool File_Exist(string filename);
	static bool File_Creat(string filename);
	static bool File_Edit(string filename, vector<Node>::iterator start, vector<Node>::iterator end, vector<Node>::iterator it);
};

