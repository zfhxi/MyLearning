#include <iostream>
#include<vector>
#include "Drawline.hpp"
#include"DrawPolygon.hpp"
#include"CuttingAlgorithm.hpp"
using std::vector;

void CatCursorPos(POINT& point) {
	MOUSEMSG m = GetMouseMsg();
	point.x = m.x;
	point.y = m.y;
}



int main()
{
	//initgraph(640, 480);
	initgraph(1024, 768);
	POINT pt[] = { {100,100},{420,400} };
	COLORREF stroke_cr = BLUE;
	int xmin{}, ymin{}, xmax{}, ymax{};
	COLORREF fill_cr = RED;
	MOUSEMSG m;
	POINT candidate{ 0,0 };
	POINT seed;
	vector<POINT>poly_vtx{};
	vector<POINT>win_vtx{};
	while (1) {
		m = GetMouseMsg();
		//左键按下
		poly_vtx.clear();
		if (m.uMsg == WM_LBUTTONDOWN) {
			CatCursorPos(candidate);
			poly_vtx.push_back(candidate);
			while (1) {
				while (true == GetMouseMsg().mkLButton) {
					CatCursorPos(candidate);
					BeginBatchDraw();//将绘图像素放缓冲区
					ClearLine();
					BresenhamLine(poly_vtx.back(), candidate, fill_cr);
					EndBatchDraw();//将缓冲区的像素快速画出来
				}
				if (!existInVec(candidate, poly_vtx))
					poly_vtx.push_back(candidate);
				line_buffer.clear();
				if (GetMouseMsg().mkRButton == true) {
					BresenhamLine(poly_vtx.back(), poly_vtx.front(), fill_cr);
					line_buffer.clear();
					break;
				}
			}
			MakeClockWise(poly_vtx);

			//获取裁剪窗口的顶点
			while (1) {
				if (GetMouseMsg().uMsg == WM_LBUTTONDOWN) {
					CatCursorPos(candidate);
					POINT candidate1{};
					while (1) {
						while (true == GetMouseMsg().mkLButton) {
							CatCursorPos(candidate1);
							xmin = min(candidate.x, candidate1.x);
							xmax = max(candidate.x, candidate1.x);
							ymin = min(candidate.y, candidate1.y);
							ymax = max(candidate.y, candidate1.y);

							BeginBatchDraw();
							ClearCuttingWnd();
							ShowCuttingWindow({ xmin,ymin }, { xmax,ymax }, LIGHTGRAY);
							EndBatchDraw();
						}
						CurPtsBuffer.clear();
						win_vtx.clear();
						win_vtx.push_back({ xmin,ymax });
						win_vtx.push_back({ xmin,ymin });
						win_vtx.push_back({ xmax,ymin });
						win_vtx.push_back({ xmax,ymax });
						DrawPolygon(poly_vtx, RED);

						//构建新的顶点序列：1.多边形顶点序列，2.窗口顶点序列
						vector<mpoint> polyvertx{};//裁剪后多边形的顶点序列
						vector<mpoint> wndvtx = PointVec2MpointVec(win_vtx);
						if (2 == poly_vtx.size()) {
							LineCutting(poly_vtx,win_vtx,stroke_cr);
							break;
						}
						//多边形每条边与裁剪窗口逐个求交，并将求得的交点插入窗口顶点序列中
						UpdateVtxsByCorssPt(poly_vtx, polyvertx, win_vtx, wndvtx);

						//画出裁剪后的图形
						int poly_in_wnd = DrawCuttedPoly(polyvertx, wndvtx, stroke_cr);
						if (-1 == poly_in_wnd) {//窗口在多边形内部 OR 窗口与多边形无交集
							//到底画不画窗口
							DrawWndOrNot(poly_vtx, win_vtx, wndvtx, stroke_cr);
						}
						break;
					}
					break;
				}
			}
		}
	}


	char ch = getchar();
	return 0;
}