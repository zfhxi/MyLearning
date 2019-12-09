#pragma once
#include<graphics.h>
#include<vector>
using std::vector;

vector<POINT> line_buffer;//临时线条像素点阵存储

//新建点类
class mpoint {
public:
	float x;
	float y;
	int flag;//0为入点，1为出点，2为窗口内的点，-1为窗口外的点
	mpoint(float xx = 0.0, float yy = 0.0, int ff = 2) :x(xx), y(yy), flag(ff) {}
};


class PointCr {
public:
	POINT point;
	COLORREF cr;
	PointCr(POINT pt = POINT{ 0,0 }, COLORREF color = BLACK) :point(pt), cr(color) {}
};

vector<PointCr> CurPtsBuffer{};//当前点阵缓冲区

/*
判断该点是否为非黑色像素点
*/
bool isNoPixel(const int& x, const int& y) {
	return getpixel(x, y) == BLACK ? true : false;
}

/*
Bresenham画直线算法
*/
void BresenhamLine(const POINT& A, const POINT& B, const COLORREF& color, const bool&save_pixel = true) {
	line_buffer.clear();
	int abs_dx = abs(B.x - A.x);
	int abs_dy = abs(B.y - A.y);
	int x = A.x;
	int y = A.y;
	//获取x和y应有的增量，也即向哪个方向增加1
	int inc_x = A.x < B.x ? 1 : -1;
	int inc_y = A.y < B.y ? 1 : -1;
	int e;

	int delta_e_x = 2 * abs_dx;
	int delta_e_y = 2 * abs_dy;

	//斜率绝对值小于1
	if (abs_dx > abs_dy) {
		e = -abs_dx;//初始化e
		for (int i = 0; i <= abs_dx; i++) {
			if (true == save_pixel) {
				if (true == isNoPixel(x, y)) {
					putpixel(x, y, color);
					line_buffer.push_back(POINT{ x,y });
				}
			}
			else {
				putpixel(x, y, color);
			}
			x += inc_x;
			e += delta_e_y;
			if (e >= 0) {
				y += inc_y;
				e -= delta_e_x;
			}
		}
	}
	//斜率绝对值不小于1
	else {
		e = -abs_dy;
		for (int i = 0; i <= abs_dy; i++) {
			if (true == save_pixel) {
				if (true == isNoPixel(x, y)) {
					putpixel(x, y, color);
					line_buffer.push_back(POINT{ x,y });
				}
			}
			else {
				putpixel(x, y, color);
			}
			y += inc_y;
			e += delta_e_x;
			if (e >= 0) {
				x += inc_x;
				e -= delta_e_y;
			}
		}
	}
}
//清除line_buffer中存储的像素点阵，通过画成黑色实现
void ClearLine() {
	for (auto iter : line_buffer)
		putpixel(iter.x, iter.y, BLACK);
	line_buffer.clear();
}
void ClearCuttingWnd() {
	for (auto iter : CurPtsBuffer)
		putpixel(iter.point.x, iter.point.y, iter.cr);
	CurPtsBuffer.clear();
}

//画扫描线填充区域
void DrawScanLine(const int& x0, const int& x1, const int& y_scanline, const COLORREF& cr) {
	for (int i{ x0 }; i <= x1; i++)
		putpixel(i, y_scanline, cr);
}

//计算行列式
float Det(const int& x0, const int& y0, const int&x1, const int&y1) {
	return x0 * y1 - y0 * x1;
}

//线段是否相交
bool isCross(const POINT&A, const POINT&B, const POINT&C, const POINT&D) {
	int Xba = A.x - B.x;
	int Xcd = D.x - C.x;
	int Yba = A.y - B.y;
	int Ycd = D.y - C.y;

	int delta = Det(Xba, Xcd, Yba, Ycd);
	if (0 == delta) //线段平行，无交点
		return false;
	else {
		int Xbd = D.x - B.x;
		int Ybd = D.y - B.y;
		float fdelta = (float)delta;
		float lambda = Det(Xbd, Xcd, Ybd, Ycd) / fdelta;
		float mu = Det(Xba, Xbd, Yba, Ybd) / fdelta;
		if (0 < lambda&&lambda < 1 && 0 < mu&&mu < 1)
			return true;
	}
	return false;
}
