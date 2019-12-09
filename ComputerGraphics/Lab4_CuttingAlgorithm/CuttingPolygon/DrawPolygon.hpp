#pragma once
#include<vector>
#include<graphics.h>
#include<algorithm>
#include"Drawline.hpp"
using std::vector;

//#define epsinon 0.000001
#define epsinon 0.5
//判断浮点数是否相等
bool Fequal(const float&l, const float&r) {
	if (fabs(l - r) < epsinon)
		return true;
	else
		return false;
}

//重载点比较大小的操作运算符
bool operator==(const POINT& l, const POINT& r) {
	if ((l.x == r.x) && (l.y == r.y))
		return true;
	return false;
}
bool operator==(const mpoint& l, const mpoint& r) {
	if (Fequal(l.x, r.x) && Fequal(l.y, r.y))
		return true;
	return false;
}
//容器中是否有该对象
bool existInVec(const POINT& element, const vector<POINT>& vec) {
	for (POINT ele : vec)
		if (element == ele)
			return true;
	return false;
}
bool existInVec(const mpoint& element, const vector<mpoint>& vec) {
	for (mpoint ele : vec)
		if (element == ele)
			return true;
	return false;
}


//画多边形
void DrawPolygon(const vector<POINT>& vec, const COLORREF& cr) {
	for (auto e = begin(vec); e != end(vec) - 1; e++)
		BresenhamLine(*e, *(e + 1), cr);
	BresenhamLine(vec.back(), vec.front(), cr);
}
void DrawPolygon(const vector<mpoint>& vec, const COLORREF& cr) {
	POINT tmp0, tmp1;
	for (auto e = begin(vec); e != end(vec) - 1; e++) {
		tmp0 = { int((*e).x + 0.5),int((*e).y + 0.5) };
		tmp1 = { int((*(e + 1)).x + 0.5),int((*(e + 1)).y + 0.5) };
		BresenhamLine(tmp0, tmp1, cr);
	}
	tmp0 = { int(vec.back().x + 0.5),int(vec.back().y + 0.5) };
	tmp1 = { int(vec.front().x + 0.5),int(vec.front().y + 0.5) };
	BresenhamLine(tmp0, tmp1, cr);
}

//将mpoint的向量转POINT型向量
vector<POINT> MpointVec2PointVec(const vector<mpoint>& mpvec) {
	vector<POINT> pvec{};
	for (auto e : mpvec)
		pvec.push_back(POINT{ int(e.x + 0.5),int(e.y + 0.5) });
	return pvec;
}

//将POINT的向量转mpoint型向量
vector<mpoint> PointVec2MpointVec(const vector<POINT>& pvec) {
	vector<mpoint> mpvec{};
	for (auto e : pvec)
		mpvec.push_back(mpoint{ float(e.x),float(e.y) });
	return mpvec;
}

/*
判断多边形顶点的排列顺序是顺时针 OR 逆时针？从用户角度
找最右的点，通过叉乘判断
*/
bool isClockWise(const vector<POINT>& poly) {
	int xmax = poly.front().x;
	int len = poly.size();
	int pos{ -1 };
	for (int i{}; i < len; i++)
		if (xmax < poly[i].x) {
			xmax = poly[i].x;
			pos = i;
		}
	if (pos > -1) {
		int prev = (pos - 1) % len;
		int next = (pos + 1) % len;
		int x1 = poly[pos].x - poly[prev].x;
		int y1 = poly[pos].y - poly[prev].y;
		int x2 = poly[next].x - poly[pos].x;
		int y2 = poly[next].y - poly[pos].y;
		//计算叉乘的模，负代表用户的逆时针，非负代表用户的顺时针，
		return Det(x1, y1, x2, y2) < 0 ? false : true;
	}
	return true;
}

//将多边形顶点序列按照用户顺时针方向排列
void MakeClockWise(vector<POINT>& poly) {
	if (false == isClockWise(poly))
		reverse(poly.begin(), poly.end());
}

