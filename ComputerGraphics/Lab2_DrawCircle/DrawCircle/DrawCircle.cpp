// DrawCircle.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "DrawCircle.hpp"
#include<conio.h>


void test_sample_0() {
	while (1) {
		POINT pt = { 400,400 };
		int r = 200;
		MidPointCircle(pt, r, RED);
	}
}


void test_sample_1() {
	current_points_buffer.clear();
	POINT pt[2] = { POINT{0,0},POINT{0,0} };
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		//左键被按下，使用中点画圆算法画圆
		if (WM_LBUTTONDOWN == m.uMsg) {
			CatCursorPos(pt[0]);
			while (1) {
				if (true == m.mkLButton) {
					CatCursorPos(pt[1]);
					BeginBatchDraw();
					ClearBuffer();
					MidPointCircle(pt[0], CalcDistanceForTwoPoints(pt[0], pt[1]), RED);
					EndBatchDraw();
					if (false == GetMouseMsg().mkLButton) {
						current_points_buffer.clear();
						break;
					}
				}
			}
		}
		//中键被按下，使用Bresenham画圆算法画圆
		else if (WM_MBUTTONDOWN == m.uMsg) {
			CatCursorPos(pt[0]);
			while (1) {
				if (true == m.mkMButton) {
					CatCursorPos(pt[1]);
					BeginBatchDraw();
					ClearBuffer();
					BresenhamCircle(pt[0], CalcDistanceForTwoPoints(pt[0], pt[1]), GREEN);
					EndBatchDraw();
					if (false == GetMouseMsg().mkMButton) {
						current_points_buffer.clear();
						break;
					}
				}
			}
		}
		//右键被按下，使用中点画椭圆算法画椭圆
		else if (WM_RBUTTONDOWN == m.uMsg) {
			CatCursorPos(pt[0]);
			while (1) {
				if (true == m.mkRButton) {
					CatCursorPos(pt[1]);
					BeginBatchDraw();
					ClearBuffer();
					MidpointEllipse(pt[0], abs(pt[1].x - pt[0].x), abs(pt[1].y - pt[0].y), BLUE);
					EndBatchDraw();
					if (false == GetMouseMsg().mkRButton) {
						current_points_buffer.clear();
						break;
					}
				}
			}
		}
		//ESC键退出图形界面
		if (TRUE == _kbhit()) {
			if (27 == _getch()) {
				closegraph();
				break;
			}
		}
	}

}

int main() {
	initgraph(960, 660);
	test_sample_1();
	char ch = getchar();
	return 0;
}
