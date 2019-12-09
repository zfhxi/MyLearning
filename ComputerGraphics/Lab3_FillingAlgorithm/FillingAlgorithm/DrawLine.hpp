#ifndef _CZM_DRAWLINE_FUN_
#define _CZM_DRAWLINE_FUN_

#include<graphics.h>
#include<vector>

std::vector<POINT> line_buffer;//��ʱ�������ص���洢

/*
�жϸõ��Ƿ�Ϊ�Ǻ�ɫ���ص�
*/
bool isNoPixel(const int& x, const int& y) {
	return getpixel(x, y) == BLACK ? true : false;
}

/*
Bresenham��ֱ���㷨
*/
void BresenhamLine(const POINT& A, const POINT& B, const COLORREF& color) {
	line_buffer.clear();
	int abs_dx = abs(B.x - A.x);
	int abs_dy = abs(B.y - A.y);
	int x = A.x;
	int y = A.y;
	//��ȡx��yӦ�е�������Ҳ�����ĸ���������1
	int inc_x = A.x < B.x ? 1 : -1;
	int inc_y = A.y < B.y ? 1 : -1;
	int e;

	int delta_e_x = 2 * abs_dx;
	int delta_e_y = 2 * abs_dy;

	//б�ʾ���ֵС��1
	if (abs_dx > abs_dy) {
		e = -abs_dx;//��ʼ��e
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
	//б�ʾ���ֵ��С��1
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

//���line_buffer�д洢�����ص���ͨ�����ɺ�ɫʵ��
void ClearLine() {
	for (auto iter : line_buffer)
		putpixel(iter.x, iter.y, BLACK);
	line_buffer.clear();
}

//��ɨ�����������
void DrawScanLine(const int& x0, const int& x1, const int& y_scanline, const COLORREF& cr) {
	for (int i{ x0 }; i <= x1; i++)
		putpixel(i, y_scanline, cr);
}

#endif