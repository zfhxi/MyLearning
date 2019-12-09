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

//清除line_buffer中存储的像素点阵，通过画成黑色实现
void ClearLine() {
	for (auto iter : line_buffer)
		putpixel(iter.x, iter.y, BLACK);
	line_buffer.clear();
}

//画扫描线填充区域
void DrawScanLine(const int& x0, const int& x1, const int& y_scanline, const COLORREF& cr) {
	for (int i{ x0 }; i <= x1; i++)
		putpixel(i, y_scanline, cr);
}

#endif