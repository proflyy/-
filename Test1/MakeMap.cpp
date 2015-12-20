#include "stdafx.h"
#include "MakeMap.h"


MakeMap::MakeMap()
{
}

MakeMap::~MakeMap()
{
}

bool MakeMap::File_Exist(string filename) {
	fstream file(filename);
	if (!file) {
		file.close();
		return false;
	}
	else {
		return true;
		file.close();
	}
}

bool MakeMap::File_Creat(string filename) {
	fstream file;
	file.open(filename, ios::app);
	if (!file) {
		file.close();
		return false;
	}
	else {
		file.close();
		return true;
	}
}

bool MakeMap::File_Edit(string filename, vector<Node>::iterator start, vector<Node>::iterator end, vector<Node>::iterator it) {

	
	ofstream file;
	//file.open(filename);
	char buffer[1024];
	file.open(filename, ios::out);
	if (!file) {
		MessageBox(0, "ErrorNoFileCreate!", "Tap", 0);
		//return false;
		File_Creat(filename);
	}
	//else {
		file << "<!DOCTYPE html>" << endl;
		file << "<html>" << endl;
		file << "<head>" << endl;
		file << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\" />" << endl;
		file << "<meta name=\"viewport\" content = \"initial-scale=1.0, user-scalable=no\" />" << endl;
		file << "<style type=\"text/css\">";
		file << "body, html, #allmap{ width:100 % ;height:100 % ;margin:0;font-family:\"΢���ź�\"; }\n";
		file << "#allmap{ width:100 % ;height:428px; }\n";
		file << "p{margin-left:5px; font-size:14px; }\n";
		file << "</style>\n";
	/*	file << "<style type=\"text/css\">";
		file << "body, html, #allmap{ width:100%;height:100%;overflow:hidden;margin:0;font-family:\"΢���ź�\";}</style>" << endl;*/
		file << "<script type=\"text/javascript\" src=\"http://api.map.baidu.com/api?v=2.0&ak=SpKZce3e03lHfPLflCuGZ8iE \"></script>" << endl;
		file << "<script src=\"http://libs.baidu.com/jquery/1.9.0/jquery.js\"></script>" << endl;
		file << "<title>�ٶȵ�ͼ</title>" << endl;
		file << "</head>" << endl;
		file << "<body>" << endl;
		file << "<div id=\"allmap\"></div>" << endl;
		file << "</body>" << endl;
		file << "</html>" << endl;
		file << "<script type =\"text/javascript\">" << endl;



		// �ٶȵ�ͼAPI����
		file << "map=new BMap.Map(\"allmap\");" << endl;
		file << "map.centerAndZoom(new BMap.Point(" << it->longitude << "," << it->latitude << "),14);" << endl;
		//file << "map.enableScrollWheelZoom();" << endl;
		file << "var data_info = [" << endl;
		vector<Node>::iterator itt = start;
		do
		{
			CString info;
			info.Format("\"<img src='%s' width='250' height='187' title='%s ���� %s'/>\"", ConvertPath(itt->fileName), itt->time, Match_City(atof(itt->longitude),atof(itt->latitude)));
			file << "[" << itt->longitude << "," << itt->latitude << "," << info << "]";
			itt++;
		} while ((itt < end)&&(file << ","));
		file << "]" << endl;
		file << "var opts = {" << endl;
		file << "width: 250," << endl;    // ��Ϣ���ڿ��";
		file << "height : 150," << endl;    // ��Ϣ���ڸ߶�
		//file << "title : \"�찲��\" ," << endl; // ��Ϣ���ڱ���
		file << "enableMessage:true" << endl;//����������Ϣ�����Ͷ�Ϣ
		file << "};" << endl;
		file << "for (var i = 0;i<data_info.length;i++) {" << endl;
		file << "var myIcon = new BMap.Icon(\"C:/1.gif\", new BMap.Size(85, 85));" << endl;
		file << "var marker = new BMap.Marker(new BMap.Point(data_info[i][0], data_info[i][1]),{icon:myIcon})" << endl; // ������ע\n;
		file << "var content = data_info[i][2];" << endl;
		file << "map.addOverlay(marker);" << endl;               // ����ע��ӵ���ͼ��
		file << "addClickHandler(content, marker);" << endl;//keyidianji
		file << "}" << endl;

///////////////////////////����
		file << "var polyline = new BMap.Polyline([" << endl;
		itt = start;
		do
		{
			file << "new BMap.Point(" << itt->longitude << "," << itt->latitude << ")";
			itt++;
		} while ((itt < end) && (file << ","));
		file << "], { strokeColor:\"red\", strokeWeight : 5, strokeOpacity : 0.5 });" << endl;
		file << "map.addOverlay(polyline);" << endl;
		file << "function addClickHandler(content, marker) {" << endl;
		file << "marker.addEventListener(\"click\", function(e){" << endl;
		file << "	openInfo(content, e)}" << endl;
		file << ");" << endl;
		file << "}" << endl;


///////////////////////////;��
		//var p = [
		//	new BMap.Point(data_info[0][0], data_info[0][1]),
		//		new BMap.Point(116.508328, 39.919141),
		//		new BMap.Point(116.660000, 39.550000),
		//		new BMap.Point(116.666600, 39.555500),
		//		new BMap.Point(116.666666, 39.555555)
		//]
		//	var driving = new BMap.DrivingRoute(map, { renderOptions: {map: map, autoViewport : true} });
		//	driving.search(p[0], p[4], { waypoints:[p[1],p[2],p[3]] });//waypoints��ʾ;����
		itt = start;
		file << "var p = [" << endl;
		do
		{
			file << "new BMap.Point(" << itt->longitude << "," << itt->latitude << ")";
			itt++;
		} while ((itt < end) && (file << ","));
		file << "]" << endl;
		file << "var driving = new BMap.DrivingRoute(map, { renderOptions: {map: map, autoViewport : false} })" << endl;
		file << "driving.search(p[0] ,p[p.length-1],{ waypoints:[";
		itt = start;
		int i = 1;
		itt++;
		itt++;
//////		if()
		do
		{
			file << "p[" << i << "]";
			i++;
			itt++;
		} while ((itt < end) && (file << ","));
		file << "] });" << endl;

		/////////////////////////////////////////////////////////////////////////////////////
		file << "function openInfo(content, e) {" << endl;
		file << "var p = e.target;" << endl;
		file << "var point = new BMap.Point(p.getPosition().lng, p.getPosition().lat);" << endl;
		file << "var infoWindow = new BMap.InfoWindow(content, opts);" << endl;  // ������Ϣ���ڶ���
		file << "map.openInfoWindow(infoWindow, point);" << endl; //������Ϣ����
		file << "}" << endl;
		file << "</script>" << endl;
		file.close();
		return true;
	//}
}