// DrawLine.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include"DrawLine.hpp"
#include<string>
#include<conio.h>

const COLORREF& line_color = RED;

void CatCursorPos(POINT& point) {
	MOUSEMSG m = GetMouseMsg();
	point.x = m.x;
	point.y = m.y;
}

/*
测试示例1，鼠标左击两个点，画直线
*/
void test_sample_1() {
	POINT pt[2] = { POINT{0,0},POINT{0,0} };
	MOUSEMSG m;
	while (1) {
		for (int i = 0; i < 2; i++) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				CatCursorPos(pt[i]);
			}
			else
				i--;
		}
		//DDALine(pt[0], pt[1], RED);
		//BresenhamLine(pt[0], pt[1], RED);
		MidPointLine(pt[0], pt[1], RED);
	}
}

/*
* 测试示例2，鼠标左击开始获取第一个点，按住不放开，动态画直线，实现橡皮筋效果，松开结束画线。
* 左击使用DDA算法，中键点击使用Bresenham，右键点击使用中点画圆
*
* 已知Bug:后面的直线无法覆盖之前的直线
*
*/

void test_sample_2() {
	POINT pt[2] = { POINT{0,0},POINT{0,0} };
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		//左键按下,使用DDALine画直线算法
		if (m.uMsg == WM_LBUTTONDOWN) {
			CatCursorPos(pt[0]);
			while (1)
				if (true == m.mkLButton) {
					CatCursorPos(pt[1]);
					BeginBatchDraw();//将绘图像素放缓冲区
					ClearLine();
					DDALine(pt[0], pt[1], line_color);
					EndBatchDraw();//将缓冲区的像素快速画出来
					if (false == GetMouseMsg().mkLButton) {
						line_buffer.clear();
						break;
					}
				}
		}
		//中键按下,使用Bresenham画直线算法
		else if (m.uMsg == WM_MBUTTONDOWN) {
			CatCursorPos(pt[0]);
			while (1)
				if (true == m.mkMButton) {
					CatCursorPos(pt[1]);
					BeginBatchDraw();
					ClearLine();
					BresenhamLine(pt[0], pt[1], line_color);
					EndBatchDraw();
					if (false == GetMouseMsg().mkMButton) {
						line_buffer.clear();
						break;
					}
				}
		}
		//右键按下,使用中点画直线算法
		else if (m.uMsg == WM_RBUTTONDOWN) {
			CatCursorPos(pt[0]);
			while (1)
				if (true == m.mkRButton) {
					CatCursorPos(pt[1]);
					BeginBatchDraw();
					ClearLine();
					MidPointLine(pt[0], pt[1], line_color);
					EndBatchDraw();
					if (false == GetMouseMsg().mkRButton) {
						line_buffer.clear();
						break;
					}
				}
		}
		//按下ESC退出
		if (TRUE == _kbhit()) {//如果有按键按下，则_kbhit()函数返回真
			if (27 == _getch()) {//当按下ESC时，ESC键的键值时27.
				closegraph();
				break;
			}
		}

	}

}

int main()
{
	initgraph(1280, 800);//初始化绘图窗口
	test_sample_2();
	//输入任意字符退出
	char ch = getchar();
	return 0;
}
