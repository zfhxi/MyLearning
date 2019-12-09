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
		//�������
		poly_vtx.clear();
		if (m.uMsg == WM_LBUTTONDOWN) {
			CatCursorPos(candidate);
			poly_vtx.push_back(candidate);
			while (1) {
				while (true == GetMouseMsg().mkLButton) {
					CatCursorPos(candidate);
					BeginBatchDraw();//����ͼ���طŻ�����
					ClearLine();
					BresenhamLine(poly_vtx.back(), candidate, fill_cr);
					EndBatchDraw();//�������������ؿ��ٻ�����
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

			//��ȡ�ü����ڵĶ���
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

						//�����µĶ������У�1.����ζ������У�2.���ڶ�������
						vector<mpoint> polyvertx{};//�ü������εĶ�������
						vector<mpoint> wndvtx = PointVec2MpointVec(win_vtx);
						if (2 == poly_vtx.size()) {
							LineCutting(poly_vtx,win_vtx,stroke_cr);
							break;
						}
						//�����ÿ������ü���������󽻣�������õĽ�����봰�ڶ���������
						UpdateVtxsByCorssPt(poly_vtx, polyvertx, win_vtx, wndvtx);

						//�����ü����ͼ��
						int poly_in_wnd = DrawCuttedPoly(polyvertx, wndvtx, stroke_cr);
						if (-1 == poly_in_wnd) {//�����ڶ�����ڲ� OR �����������޽���
							//���׻���������
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