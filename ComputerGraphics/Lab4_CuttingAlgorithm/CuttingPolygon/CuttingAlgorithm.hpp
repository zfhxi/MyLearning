#pragma once

//encode [上,下,右,左]
#define TOP 8
#define BOTTOM 4
#define RIGHT 2
#define LEFT 1
#define INPOINT 0
#define OUTPOINT 1


#include<vector>
#include"DrawPolygon.hpp"
#include"EdgeFill.hpp"
using std::vector;



//求点的区域编码
int EnCode(float x, float y, const vector<POINT>&win_vtx) {
	int xmin = win_vtx[1].x;
	int ymin = win_vtx[1].y;
	int xmax = win_vtx[3].x;
	int ymax = win_vtx[3].y;
	int code = 0;
	if (x < xmin)code |= LEFT;
	if (x > xmax) code |= RIGHT;
	if (y < ymin)code |= BOTTOM;
	if (y > ymax)code |= TOP;
	return code;
}

//更新(x,y)为可能的交点
void UpdateToIntersection(const int& c, float& x, float&y, const float&k, const vector<POINT>& win_vtx) {
	int xmin = win_vtx[1].x;
	int ymin = win_vtx[1].y;
	int xmax = win_vtx[3].x;
	int ymax = win_vtx[3].y;
	if (0 != (c&LEFT)) {//端点在左侧
		y += k * (xmin - x);
		x = xmin;
	}
	else if (0 != (c&RIGHT)) {//端点在右侧
		y += k * (xmax - x);
		x = xmax;
	}
	else if (0 != (c&BOTTOM)) {//端点在下侧
		x += (ymin - y) / k;
		y = ymin;
	}
	else {//端点在上侧
		x += (ymax - y) / k;
		y = ymax;
	}
}

//直线裁剪
void LineCutting(const vector<POINT>line_vtx, const vector<POINT>&win_vtx, const COLORREF& stroke_cr) {
	float x0{ float(line_vtx[0].x) }, y0{ float(line_vtx[0].y) };
	float x1{ float(line_vtx[1].x) }, y1{ float(line_vtx[1].y) };
	int c0{ EnCode(x0,y0,win_vtx) };
	int c1{ EnCode(x1,y1,win_vtx) };
	int draw_flag = 1;
	const float k{ (y1 - y0) / (x1 - x0) };

	while (0 != c0) {//如果端点在窗口外
		if (0 != (c0&c1)) {//直线段两断点在窗口同侧
			draw_flag = 0;//不需要画直线
			break;
		}
		//更新为与窗口的端点
		UpdateToIntersection(c0, x0, y0, k, win_vtx);
		//重新编码
		c0 = EnCode(x0, y0, win_vtx);
	}
	while ((1 == draw_flag) && 0 != c1) {//如果端点在窗口外
		//更新为与窗口的端点
		UpdateToIntersection(c1, x1, y1, k, win_vtx);
		//重新编码
		c1 = EnCode(x1, y1, win_vtx);
	}
	if (1 == draw_flag)
		BresenhamLine(POINT{ int(x0 + 0.5),int(y0 + 0.5) }, POINT{ int(x1 + 0.5) ,int(y1 + 0.5) }, stroke_cr, false);
}

//定位元素在向量中的索引
int GetPosInVec(const mpoint&point, const vector<mpoint>& vec) {
	int vecsize = vec.size();
	for (int i{ 0 }; i < vecsize; i++)
		if (Fequal(point.x, vec[i].x)
			&& Fequal(point.y, vec[i].y)
			&& (point.flag == vec.at(i).flag))
			return i;
	return -1;
}

//向窗口序列中插入交点
void InsCrossPt2Wnd(int code, const mpoint& mpt, vector<mpoint>& win_vec, const vector<POINT> win_vtx) {
	float xmin = win_vtx[1].x;
	float ymin = win_vtx[1].y;
	float xmax = win_vtx[3].x;
	float ymax = win_vtx[3].y;
	float xx{ mpt.x }, yy{ mpt.y };
	if (0 != (code&LEFT)) {//端点在左侧
		auto e = win_vec.begin() + GetPosInVec({ xmin,ymax }, win_vec);
		auto posend = win_vec.begin() + GetPosInVec({ xmin,ymin }, win_vec);
		while (yy <= (*e).y)if (++e > posend)break;
		win_vec.insert(e, mpt);
	}
	else if (0 != (code&RIGHT)) {//端点在右侧
		auto e = win_vec.begin() + GetPosInVec({ xmax,ymin }, win_vec);
		auto posend = win_vec.begin() + GetPosInVec({ xmax,ymax }, win_vec);
		while (yy >= (*e).y)if (++e > posend)break;
		win_vec.insert(e, mpt);
	}
	else if (0 != (code&TOP)) {//端点在屏幕下侧，窗口坐标系的上侧
		auto e = win_vec.begin() + GetPosInVec({ xmax,ymax }, win_vec);
		auto posend = win_vec.end();
		while (xx <= (*e).x)if (++e >= posend)break;
		win_vec.insert(e, mpt);
	}
	else {//端点在屏幕上侧，窗口坐标系的下侧
		auto e = win_vec.begin() + GetPosInVec({ xmin,ymin }, win_vec);
		auto posend = win_vec.begin() + GetPosInVec({ xmax,ymin }, win_vec);
		while (xx >= (*e).x)if (++e > posend)break;
		win_vec.insert(e, mpt);
	}

}

//迭代求交点
mpoint GetInterSection(const float&x, const float&y, const int&theother_code, const float&k, const vector<POINT>& win_vtx, int type, vector<mpoint>& win_vec) {
	float xx{ x }, yy{ y };
	int code{ EnCode(xx, yy, win_vtx) };
	int tmpcode;
	mpoint intersec;
	if (0 == code)//在窗口内。或者窗口边
		return mpoint{ xx,yy,2 };
	while (0 != code) {//在窗口外,可能有交点，也可能无交点
		if (0 != (code&theother_code))//如果无交点，那么最后会同侧
			return { -1,-1,-10 };
		UpdateToIntersection(code, xx, yy, k, win_vtx);
		tmpcode = EnCode(xx, yy, win_vtx);
		if (0 == tmpcode) {//插入交点到窗口顶点序列
			intersec = { float(int(xx+0.5)),float(int(yy+0.5)),type };
			if (!existInVec(intersec, win_vec)) {
				InsCrossPt2Wnd(code, intersec, win_vec, win_vtx);
			}
		}
		code = tmpcode;
	}
	return intersec;
}

//从多边形顶点序列中取入点到出点的所有点，返回出点
mpoint GetOutPoint(const mpoint& in_point, vector<mpoint>&polyvertx, vector<POINT>&dstvec) {
	int in_idx = GetPosInVec(in_point, polyvertx);
	int i{ in_idx };
	int len = polyvertx.size();
	mpoint out_point{};
	mpoint p{};
	while (true) {
		i = (i + 1) % len;
		p = *(polyvertx.begin() + i);
		dstvec.push_back({ int(p.x + 0.5),int(p.y + 0.5) });
		if (1 == p.flag) {
			out_point = p;
			break;
		}
	}
	//擦除入点和下一个出点之间的点
			//DrawPoints(cuttedvertx);
	if (in_idx <= i)
		polyvertx.erase(polyvertx.begin() + in_idx, polyvertx.begin() + i + 1);
	else {
		polyvertx.erase(polyvertx.begin() + in_idx, polyvertx.end());
		polyvertx.erase(polyvertx.begin(), polyvertx.begin() + i + 1);
	}
	return out_point;
}

//从窗口顶点序列中取出点到入点的所有点，返回入点
mpoint GetInPoint(const mpoint& out_point, const vector<mpoint>&wndvtx, vector<POINT>&dstvec) {
	int out_idx = GetPosInVec(out_point, wndvtx);
	int i{ out_idx };
	int len = wndvtx.size();
	mpoint in_point{};
	mpoint p{};
	while (true) {
		i = (i + 1) % len;
		p = *(wndvtx.begin() + i);
		dstvec.push_back({ int(p.x + 0.5),int(p.y + 0.5) });
		if (0 == p.flag) {
			in_point = p;
			break;
		}
	}
	return in_point;
}

//通过求交点更新窗口和多边形顶点序列
void UpdateVtxsByCorssPt(const vector<POINT>&poly_vtx, vector<mpoint>&polyvertx, const vector<POINT>& win_vtx, vector<mpoint>&wndvtx) {
	mpoint tmpoint;
	float x0, y0, x1, y1;
	int code0, code1;
	float k;
	int polysize = poly_vtx.size();
	int flag0, flag1;
	for (int i{ 0 }; i < polysize; ++i) {
		//获取多边形某边两端点坐标
		x0 = float(poly_vtx.at(i%polysize).x);
		y0 = float(poly_vtx.at(i%polysize).y);
		x1 = float(poly_vtx.at((i + 1) % polysize).x);
		y1 = float(poly_vtx.at((i + 1) % polysize).y);
		code0 = EnCode(x0, y0, win_vtx);
		code1 = EnCode(x1, y1, win_vtx);
		//取得斜率
		k = (y1 - y0) / (x1 - x0);
		//需要从某端点求交吗？默认需要求交
		flag0 = 1;
		flag1 = 1;
		if (0 == code0) { //在窗口
			polyvertx.push_back({ x0,y0,2 });
			flag0 = 0;//不再需要求交
		}
		if (0 == code1) { //在窗口
			//为何此处不插入，因为第二个点会在下一轮成为第一个点
			flag1 = 0;//不再需要求交
		}
		//两个端点在窗外不同侧,也可能是其中一个在窗内
		if (0 == (code0&code1)) {
			if (1 == flag0) {//求第一个交点
				tmpoint = GetInterSection(x0, y0, code1, k, win_vtx, INPOINT, wndvtx);
				if (-10 != tmpoint.flag) {
					tmpoint.x = int(tmpoint.x + 0.5);
					tmpoint.y = int(tmpoint.y + 0.5);
					polyvertx.push_back(tmpoint);
				}
			}
			if (1 == flag1) {//求第二个交点
				tmpoint = GetInterSection(x1, y1, code0, k, win_vtx, OUTPOINT, wndvtx);
				if (-10 != tmpoint.flag) {
					tmpoint.x = int(tmpoint.x + 0.5);
					tmpoint.y = int(tmpoint.y + 0.5);
					polyvertx.push_back(tmpoint);
				}
			}
		}
		if (2 == polysize)break;//如果是一条直线
	}
}

//从构建的多边形顶点序列和窗口序列中分别搜寻出入点对，找到裁剪后的多边形，画出来
int DrawCuttedPoly(vector<mpoint>&polyvertx, const vector<mpoint>&wndvtx, const COLORREF& cr) {
	vector<POINT>cuttedvertx{};//裁剪后的多边形顶点序列
	mpoint p_inpt{ -1,-1 };//多边形入点
	mpoint tmpt{};//临时暂存点
	int poly_in_wnd = 0;//0-》多边形的边不全在窗口内，且多边形与窗口有交集 OR 多边形的边全在窗口内，-1》窗口全在多边形内 OR 窗口与多边形无交集
	//窗口全在多边形内. --> 特征：新建的多边形顶点序列全为空
	if (true == polyvertx.empty())//窗口在多边形内部 OR 窗口与多边形无交集
		poly_in_wnd = -1;
	else {
		while (false == polyvertx.empty()) {
			//寻找第一个入点，万一没找到怎么办？//在多边形全在窗口内时，无入点
			for (const auto& e : polyvertx) {
				if (0 == e.flag) {
					p_inpt = e;
					cuttedvertx.push_back({ int(p_inpt.x + 0.5),int(p_inpt.y + 0.5) });
					break;
				}
			}
			if (-1 == p_inpt.x) {//多边形全在窗口内；
				for (auto e : polyvertx)
					cuttedvertx.push_back({ int(e.x + 0.5),int(e.y + 0.5) });
				polyvertx.clear();
			}
			else {
				while (1) {
					//获取入出点对到目标向量
					tmpt = GetOutPoint(p_inpt, polyvertx, cuttedvertx);
					//通过刚加入的出点，在窗口序列中找出入点对
					tmpt = GetInPoint(tmpt, wndvtx, cuttedvertx);
					if (cuttedvertx.back() == cuttedvertx.front()) {
						cuttedvertx.pop_back();
						break;
					}
					p_inpt = tmpt;
				}
			}
			EdgeRelatedFill(cuttedvertx, cr);
			DrawPolygon(cuttedvertx, cr);
			cuttedvertx.clear();
			p_inpt = { -1,-1 };
		}
	}
	return poly_in_wnd;
}

void DrawWndOrNot(const vector<POINT>&poly_vtx, const vector<POINT>&win_vtx, const vector<mpoint>&wndvtx, const COLORREF&stroke_cr) {
	//判断点在多边形内还是外，奇偶检测，以窗口顶点{xmax,ymax}为例
	POINT A = { win_vtx[3].x,win_vtx[3].y };
	POINT B = { getmaxx(),win_vtx[3].y };

	int counter{};
	int len = poly_vtx.size();
	int x_next{}, y_next{}, x_cur{}, y_cur{};
	for (int i{}; i < len; i++) {
		x_cur = poly_vtx[i].x;
		y_cur = poly_vtx[i].y;
		x_next = poly_vtx[(i + 1) % len].x;
		y_next = poly_vtx[(i + 1) % len].y;
		if (x_cur > A.x&&y_cur == A.y) {//交点为当前顶点
			//if(y_cur<=y_next)，计数加0
			if (y_cur > y_next)counter++;
		}
		else if (x_next > A.x&&y_next == A.y) {//交点为下一顶点
			//if(y_cur>=y_next)，计数加0
			if (y_cur < y_next)counter++;
		}
		else {
			if (true == isCross(A, B, { x_cur,y_cur }, { x_next,y_next }))//两线段交于非端点
				counter++;
		}
	}
	if (0 != counter % 2) {//窗口右上点在多边形外
		DrawPolygon(wndvtx, stroke_cr);
		EdgeRelatedFill(MpointVec2PointVec(wndvtx), stroke_cr);
	}
}

//显示裁剪窗口
void ShowCuttingWindow(const POINT&left_bottom, const POINT&right_top, const COLORREF& cr) {
	int xmin = min(left_bottom.x, right_top.x);
	int xmax = max(left_bottom.x, right_top.x);
	int ymin = min(left_bottom.y, right_top.y);
	int ymax = max(left_bottom.y, right_top.y);
	for (int i{ xmin + 1 }; i < xmax; i++) {
		if (0 != i % 5) {
			CurPtsBuffer.push_back(PointCr{ POINT{i,ymin},getpixel(i,ymin) });
			putpixel(i, ymin, cr);
			CurPtsBuffer.push_back(PointCr{ POINT{i,ymax},getpixel(i,ymax) });
			putpixel(i, ymax, cr);
		}
	}
	for (int j{ ymin }; j <= ymax; j++) {
		if (0 != j % 5) {
			CurPtsBuffer.push_back(PointCr{ POINT{xmin,j},getpixel(xmin,j) });
			putpixel(xmin, j, cr);
			CurPtsBuffer.push_back(PointCr{ POINT{xmax,j},getpixel(xmax,j) });
			putpixel(xmax, j, cr);
		}
	}
}

