#ifndef _CZM_DRAWLINE_FUN_
#define _CZM_DRAWLINE_FUN_

#include<graphics.h>
#include<vector>

std::vector<POINT> line_buffer;//临时线条像素点阵存储

/*
判断该点是否为非黑色像素点
*/
bool isNoPixel(const int& x, const int& y) {
	return getpixel(x, y) == BLACK ? true : false;
}

/*
DDA画直线算法
*/
void DDALine(const POINT& A, const POINT& B, const COLORREF& color) {
	line_buffer.clear();//清空buffer
	float inc_x, inc_y;
	float x = float(A.x);
	float y = float(A.y);
	//斜率绝对值大于1？steps取|dx|:steps取|dy|
	int steps = max(abs(A.x - B.x), abs(A.y - B.y));
	//获取x，y的增量
	inc_x = (float)(B.x - A.x) / steps;//如果斜率为0~1，那么steps取|dx|，则1=inc_x
	inc_y = (float)(B.y - A.y) / steps;//如果斜率为0~1，那么steps取|dx|,则k==inc_y为true
	//循环按增量“爬出直线”
	int x_int, y_int;
	for (int i = 1; i <= steps; i++) {
		//如果此处没有黑色外的像素点，则记录该像素点
		x_int = int(x);
		y_int = int(y);
		if (true == isNoPixel(x_int, y_int)) {
			putpixel(x_int, y_int, color);
			line_buffer.push_back(POINT{ x_int,y_int });
		}
		x += inc_x;
		y += inc_y;
	}
}

/*
Bresenham画直线算法
*/
void BresenhamLine(const POINT& A, const POINT& B, const COLORREF& color) {
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
			if (true == isNoPixel(x, y)) {
				putpixel(x, y, color);
				line_buffer.push_back(POINT{ x,y });
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
			if (true == isNoPixel(x, y)) {
				putpixel(x, y, color);
				line_buffer.push_back(POINT{ x,y });
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

//中点画直线算法
void MidPointLine(const POINT& A, const POINT& B, const COLORREF& color) {
	line_buffer.clear();
	int dx = abs(B.x - A.x);
	int dy = abs(B.y - A.y);
	int d = 2 * dy - dx;
	int d1, d2;
	int x = A.x;
	int y = A.y;
	//获取x和y应有的增量，也即向哪个方向增加1
	int inc_x = A.x < B.x ? 1 : -1;
	int inc_y = A.y < B.y ? 1 : -1;

	if (true == isNoPixel(x, y)) {
		putpixel(x, y, color);
		line_buffer.push_back(POINT{ LONG(x),LONG(y) });
	}
	//斜率绝对值小于1
	if (dx > dy) {
		d1 = 2 * dy;
		d2 = 2 * (dy - dx);
		while (abs(x - B.x) > 0) {
			x += inc_x;
			if (d > 0) {
				y += inc_y;
				d += d2;
			}
			else
				d += d1;
			if (true == isNoPixel(x, y)) {
				putpixel(x, y, color);
				line_buffer.push_back(POINT{ LONG(x),LONG(y) });
			}
		}
	}
	//斜率绝对值小于1
	else {
		d1 = -2 * dx;
		d2 = 2 * (-dx + dy);
		while (abs(y - B.y) > 0) {
			y += inc_y;
			if (d < 0) {
				x += inc_x;
				d += d2;
			}
			else
				d += d1;
			if (true == isNoPixel(x, y)) {
				putpixel(x, y, color);
				line_buffer.push_back(POINT{ LONG(x),LONG(y) });
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

#endif
