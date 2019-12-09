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
DDA��ֱ���㷨
*/
void DDALine(const POINT& A, const POINT& B, const COLORREF& color) {
	line_buffer.clear();//���buffer
	float inc_x, inc_y;
	float x = float(A.x);
	float y = float(A.y);
	//б�ʾ���ֵ����1��stepsȡ|dx|:stepsȡ|dy|
	int steps = max(abs(A.x - B.x), abs(A.y - B.y));
	//��ȡx��y������
	inc_x = (float)(B.x - A.x) / steps;//���б��Ϊ0~1����ôstepsȡ|dx|����1=inc_x
	inc_y = (float)(B.y - A.y) / steps;//���б��Ϊ0~1����ôstepsȡ|dx|,��k==inc_yΪtrue
	//ѭ��������������ֱ�ߡ�
	int x_int, y_int;
	for (int i = 1; i <= steps; i++) {
		//����˴�û�к�ɫ������ص㣬���¼�����ص�
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

//�е㻭ֱ���㷨
void MidPointLine(const POINT& A, const POINT& B, const COLORREF& color) {
	line_buffer.clear();
	int dx = abs(B.x - A.x);
	int dy = abs(B.y - A.y);
	int d = 2 * dy - dx;
	int d1, d2;
	int x = A.x;
	int y = A.y;
	//��ȡx��yӦ�е�������Ҳ�����ĸ���������1
	int inc_x = A.x < B.x ? 1 : -1;
	int inc_y = A.y < B.y ? 1 : -1;

	if (true == isNoPixel(x, y)) {
		putpixel(x, y, color);
		line_buffer.push_back(POINT{ LONG(x),LONG(y) });
	}
	//б�ʾ���ֵС��1
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
	//б�ʾ���ֵС��1
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

//���line_buffer�д洢�����ص���ͨ�����ɺ�ɫʵ��
void ClearLine() {
	for (auto iter : line_buffer)
		putpixel(iter.x, iter.y, BLACK);
	line_buffer.clear();
}

#endif
