// FillingAlgorithm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"DrawLine.hpp"
#include"EdgeFill.hpp"
#include"SeedFill.hpp"
#include<stack>
#include<conio.h>

//获取鼠标当前坐标，放入POINT对象中
void CatCursorPos(POINT& point) {
	MOUSEMSG m = GetMouseMsg();
	point.x = m.x;
	point.y = m.y;
}

//容器中是否有该对象
bool existInVec(const POINT& element, const std::vector<POINT>& vec) {
	for (POINT ele : vec) {
		if (element.x == ele.x&&element.y == ele.y)
			return true;
	}
	return false;
}

int main()
{
	initgraph(600, 600);
	std::vector<POINT>vertex;
	COLORREF fill_cr = RED;
	MOUSEMSG m;
	POINT candidate{ 0,0 };
	POINT seed;
	std::vector<POINT>final_vertex;
	//*
	while (1) {
		m = GetMouseMsg();
		//左键按下,使用DDALine画直线算法
		if (m.uMsg == WM_LBUTTONDOWN) {
			CatCursorPos(candidate);
			vertex.push_back(candidate);
			while (1) {
				while (true == GetMouseMsg().mkLButton) {
					CatCursorPos(candidate);
					BeginBatchDraw();//将绘图像素放缓冲区
					ClearLine();
					BresenhamLine(vertex.back(), candidate, fill_cr);
					EndBatchDraw();//将缓冲区的像素快速画出来
				}
				if (!existInVec(candidate, vertex))
					vertex.push_back(candidate);
				line_buffer.clear();
				if (GetMouseMsg().mkRButton == true) {
					BresenhamLine(vertex.back(), vertex.front(), fill_cr);
					line_buffer.clear();
					final_vertex = vertex;
					vertex.clear();
					break;
				}
			}
		}
		if (TRUE == _kbhit())
			switch (_getch())
			{
			case 13: {//按下回车键，种子填充算法
				//种子填充
				while (GetMouseMsg().mkLButton == false);
				CatCursorPos(seed);
				std::stack<POINT> seeds;//种子栈
				seeds.push(seed);//第一个种子入栈
				DrawBorder(fill_cr);
				BeginBatchDraw();
				SeedFill(seeds, fill_cr);
				EndBatchDraw();
				DrawBorder(BLACK);
				break;
			}

			case 32: {//按下空格键
				//边相关扫描填充
				EdgeRelatedFill(final_vertex, fill_cr);
				break;
			}
			case 27: {//按下ESC
				closegraph();
				break;
			}
			default:
				break;
			}
	}
	//*/
	char ch = getchar();
	closegraph();
	return 0;
}
