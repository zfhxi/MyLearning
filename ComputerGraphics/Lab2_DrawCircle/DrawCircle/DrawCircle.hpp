#ifndef _CZM_DRAWCIRCLE_FUN_
#define _CZM_DRAWCIRCLE_FUN_

#include<graphics.h>
#include<vector>
#include<map>

#define dx (x-x0)
#define dy (y-y0)

class PointCr {
public:
	POINT point;
	COLORREF cr;
	PointCr(POINT pt = POINT{ 0,0 }, COLORREF color = BLACK) :point(pt), cr(color) {}
};

std::vector<PointCr> current_points_buffer;//当前点阵缓冲区


//监听鼠标当前坐标，并传给point
void CatCursorPos(POINT& point) {
	MOUSEMSG m = GetMouseMsg();
	point.x = m.x;
	point.y = m.y;
}

//计算两点之间的距离，用于算圆的半径，返回取整后的值
int CalcDistanceForTwoPoints(const POINT& A, const POINT& B) {
	int ddx = A.x - B.x;
	int ddy = A.y - B.y;
	return int(sqrtf(ddx * ddx + ddy * ddy) + 1/2);
}

//画点函数，并保存该点之前的状态
void MyPutPixel(const int& x, const int& y, const COLORREF& cr) {
	current_points_buffer.push_back(PointCr{ POINT{x,y},getpixel(x,y) });
	putpixel(x, y, cr);
}

//画一个点，对称画出其余3个点
void SetFourPixels(const int& x0, const int& y0, const int& x, const int& y, const COLORREF& cr) {
	MyPutPixel(x, y, cr);
	if (y != y0)
		MyPutPixel(x, 2 * y0 - y, cr);
	if (x != x0)
		MyPutPixel(2 * x0 - x, y, cr);
	if (x != x0 && y != y0)
		MyPutPixel(2 * x0 - x, 2 * y0 - y, cr);
}

//画一个点，对称画出其余7个点
void SetEightPixels(const int& x0, const int& y0, const int& x, const int& y, const COLORREF & cr) {
	MyPutPixel(x, y, cr);
	if (y != y0)
		MyPutPixel(x, 2 * y0 - y, cr);
	if (x != x0)
		MyPutPixel(2 * x0 - x, y, cr);
	if (x != x0 && y != y0)
		MyPutPixel(2 * x0 - x, 2 * y0 - y, cr);
	if (dx < dy) {
		MyPutPixel(x0 + dy, y0 + dx, cr);
		if (dx != 0)
			MyPutPixel(x0 + dy, 2 * y0 - (y0 + dx), cr);
		if (dy != 0)
			MyPutPixel(2 * x0 - (x0 + dy), y0 + dx, cr);
		if (dy != 0 && dx != 0)
			MyPutPixel(2 * x0 - (x0 + dy), 2 * y0 - (y0 + dx), cr);
	}
}


//中点画圆算法
void MidPointCircle(const POINT & O, const int& R, const COLORREF & cr) {
	int x0, y0, x, y;
	x0 = O.x, y0 = O.y;
	x = x0, y = y0 + R;
	int e = 1 - R;
	while (dx <= dy) {
		SetEightPixels(x0, y0, x, y, cr);
		if (e < 0)e += 2 * dx + 3;
		else {
			e += 2 * (dx - dy) + 5;
			y--;
		}
		x++;
	}
}

//Bresenham画8分之一圆，对称得到整个圆
void BresenhamCircle(const POINT & O, const int& R, const COLORREF & cr) {
	int x0{ O.x }, y0{ O.y }, x{ x0 }, y{ y0 + R };
	int delta{ 2 * (1 - R) }, delta1{ 0 }, delta2{ 0 };
	int direciton{ 0 };
	while (dy >= dx) {
		SetEightPixels(x0, y0, x, y, cr);
		if (delta < 0) {
			delta1 = 2 * (delta + dy) - 1;
			direciton = delta1 <= 0 ? 1 : 2;

		}
		else if (delta > 0) {
			delta2 = 2 * (delta - dx) - 1;
			direciton = delta2 < 0 ? 2 : 3;
		}
		else
			direciton = 2;
		switch (direciton)
		{
		case 1:
			x++;
			delta += 2 * dx + 1;
			break;
		case 2:
			x++;
			y--;
			delta += 2 * (dx - dy + 1);
			break;
		case 3:
			y--;
			delta += (-2 * dy + 1);
			break;
		default:
			break;
		}
	}
}

//中点画四分之一椭圆，对称得到其他部分
void MidpointEllipse(const POINT & O, const int& a, const int& b, const COLORREF & cr) {
	int x0{ O.x }, y0{ O.y };
	int x{ x0 }, y{ y0 + b };
	int aa = a * a;
	int bb = b * b;
	int d = 2 * bb + aa * (-2 * b) + aa / 2;
	//斜率绝对值小于1
	while (2 * bb * (dx + 1) < aa * (2 * dy - 1)) {
		SetFourPixels(x0, y0, x, y, cr);
		//中点在椭圆内，选择正右方向的点
		if (d <= 0) {
			d += 2 * bb * (2 * dx + 3);
		}
		//中点在椭圆外，选择右下方的点
		else {
			d += 2 * bb * (2 * dx + 3) + 2 * aa * (-2 * dy + 2);
			y--;
		}
		x++;
	}
	//斜率绝对值不小于1
	d = bb * (dx + 1 / 2) * (2 * dx + 1)
		+ 2 * aa * (dy - 1) * (dy - 1)
		- 2 * aa * bb;
	while (dy >= 0) {
		SetFourPixels(x0, y0, x, y, cr);
		//中点在椭圆内，选择右下方的点
		if (d <= 0) {
			d += 2 * bb * (2 * dx + 2) + 2 * aa * (-2 * dy + 3);
			x++;
		}
		//中点在椭圆外，选择正下方的点
		else {
			d += 2 * aa * (-2 * dy + 3);
		}
		y--;
	}
}

//缓冲区清空
void ClearBuffer() {
	for (auto iter : current_points_buffer)
		putpixel(iter.point.x, iter.point.y, iter.cr);
	current_points_buffer.clear();
}

#endif
