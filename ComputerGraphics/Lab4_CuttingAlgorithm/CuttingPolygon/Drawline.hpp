#pragma once
#include<graphics.h>
#include<vector>
using std::vector;

vector<POINT> line_buffer;//��ʱ�������ص���洢

//�½�����
class mpoint {
public:
	float x;
	float y;
	int flag;//0Ϊ��㣬1Ϊ���㣬2Ϊ�����ڵĵ㣬-1Ϊ������ĵ�
	mpoint(float xx = 0.0, float yy = 0.0, int ff = 2) :x(xx), y(yy), flag(ff) {}
};


class PointCr {
public:
	POINT point;
	COLORREF cr;
	PointCr(POINT pt = POINT{ 0,0 }, COLORREF color = BLACK) :point(pt), cr(color) {}
};

vector<PointCr> CurPtsBuffer{};//��ǰ���󻺳���

/*
�жϸõ��Ƿ�Ϊ�Ǻ�ɫ���ص�
*/
bool isNoPixel(const int& x, const int& y) {
	return getpixel(x, y) == BLACK ? true : false;
}

/*
Bresenham��ֱ���㷨
*/
void BresenhamLine(const POINT& A, const POINT& B, const COLORREF& color, const bool&save_pixel = true) {
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
	//б�ʾ���ֵ��С��1
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
//���line_buffer�д洢�����ص���ͨ�����ɺ�ɫʵ��
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

//��ɨ�����������
void DrawScanLine(const int& x0, const int& x1, const int& y_scanline, const COLORREF& cr) {
	for (int i{ x0 }; i <= x1; i++)
		putpixel(i, y_scanline, cr);
}

//��������ʽ
float Det(const int& x0, const int& y0, const int&x1, const int&y1) {
	return x0 * y1 - y0 * x1;
}

//�߶��Ƿ��ཻ
bool isCross(const POINT&A, const POINT&B, const POINT&C, const POINT&D) {
	int Xba = A.x - B.x;
	int Xcd = D.x - C.x;
	int Yba = A.y - B.y;
	int Ycd = D.y - C.y;

	int delta = Det(Xba, Xcd, Yba, Ycd);
	if (0 == delta) //�߶�ƽ�У��޽���
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
