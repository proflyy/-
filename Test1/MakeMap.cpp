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
		file << "body, html, #allmap{ width:100 % ;height:100 % ;margin:0;font-family:\"微软雅黑\"; }\n";
		file << "#allmap{ width:100 % ;height:428px; }\n";
		file << "p{margin-left:5px; font-size:14px; }\n";
		file << "</style>\n";
	/*	file << "<style type=\"text/css\">";
		file << "body, html, #allmap{ width:100%;height:100%;overflow:hidden;margin:0;font-family:\"微软雅黑\";}</style>" << endl;*/
		file << "<script type=\"text/javascript\" src=\"http://api.map.baidu.com/api?v=2.0&ak=SpKZce3e03lHfPLflCuGZ8iE \"></script>" << endl;
		file << "<script src=\"http://libs.baidu.com/jquery/1.9.0/jquery.js\"></script>" << endl;
		file << "<title>百度地图</title>" << endl;
		file << "</head>" << endl;
		file << "<body>" << endl;
		file << "<div id=\"allmap\"></div>" << endl;
		file << "</body>" << endl;
		file << "</html>" << endl;
		file << "<script type =\"text/javascript\">" << endl;



		// 百度地图API功能
		file << "map=new BMap.Map(\"allmap\");" << endl;
		file << "map.centerAndZoom(new BMap.Point(" << it->longitude << "," << it->latitude << "),14);" << endl;
		//file << "map.enableScrollWheelZoom();" << endl;
		file << "var data_info = [" << endl;
		vector<Node>::iterator itt = start;
		do
		{
			CString info;
			info.Format("\"<img src='%s' width='250' height='187' title='%s 照于 %s'/>\"", ConvertPath(itt->fileName), itt->time, Match_City(atof(itt->longitude),atof(itt->latitude)));
			file << "[" << itt->longitude << "," << itt->latitude << "," << info << "]";
			itt++;
		} while ((itt < end)&&(file << ","));
		file << "]" << endl;
		file << "var opts = {" << endl;
		file << "width: 250," << endl;    // 信息窗口宽度";
		file << "height : 150," << endl;    // 信息窗口高度
		//file << "title : \"天安门\" ," << endl; // 信息窗口标题
		file << "enableMessage:true" << endl;//设置允许信息窗发送短息
		file << "};" << endl;
		file << "for (var i = 0;i<data_info.length;i++) {" << endl;
		file << "var myIcon = new BMap.Icon(\"C:/1.gif\", new BMap.Size(85, 85));" << endl;
		file << "var marker = new BMap.Marker(new BMap.Point(data_info[i][0], data_info[i][1]),{icon:myIcon})" << endl; // 创建标注\n;
		file << "var content = data_info[i][2];" << endl;
		file << "map.addOverlay(marker);" << endl;               // 将标注添加到地图中
		file << "addClickHandler(content, marker);" << endl;//keyidianji
		file << "}" << endl;

///////////////////////////画线
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


///////////////////////////途径
		//var p = [
		//	new BMap.Point(data_info[0][0], data_info[0][1]),
		//		new BMap.Point(116.508328, 39.919141),
		//		new BMap.Point(116.660000, 39.550000),
		//		new BMap.Point(116.666600, 39.555500),
		//		new BMap.Point(116.666666, 39.555555)
		//]
		//	var driving = new BMap.DrivingRoute(map, { renderOptions: {map: map, autoViewport : true} });
		//	driving.search(p[0], p[4], { waypoints:[p[1],p[2],p[3]] });//waypoints表示途经点
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
		file << "var infoWindow = new BMap.InfoWindow(content, opts);" << endl;  // 创建信息窗口对象
		file << "map.openInfoWindow(infoWindow, point);" << endl; //开启信息窗口
		file << "}" << endl;
		file << "</script>" << endl;
		file.close();
		return true;
	//}
}