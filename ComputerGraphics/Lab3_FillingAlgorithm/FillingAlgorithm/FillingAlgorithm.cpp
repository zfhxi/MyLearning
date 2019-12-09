// FillingAlgorithm.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include"DrawLine.hpp"
#include"EdgeFill.hpp"
#include"SeedFill.hpp"
#include<stack>
#include<conio.h>

//��ȡ��굱ǰ���꣬����POINT������
void CatCursorPos(POINT& point) {
	MOUSEMSG m = GetMouseMsg();
	point.x = m.x;
	point.y = m.y;
}

//�������Ƿ��иö���
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
		//�������,ʹ��DDALine��ֱ���㷨
		if (m.uMsg == WM_LBUTTONDOWN) {
			CatCursorPos(candidate);
			vertex.push_back(candidate);
			while (1) {
				while (true == GetMouseMsg().mkLButton) {
					CatCursorPos(candidate);
					BeginBatchDraw();//����ͼ���طŻ�����
					ClearLine();
					BresenhamLine(vertex.back(), candidate, fill_cr);
					EndBatchDraw();//�������������ؿ��ٻ�����
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
			case 13: {//���»س�������������㷨
				//�������
				while (GetMouseMsg().mkLButton == false);
				CatCursorPos(seed);
				std::stack<POINT> seeds;//����ջ
				seeds.push(seed);//��һ��������ջ
				DrawBorder(fill_cr);
				BeginBatchDraw();
				SeedFill(seeds, fill_cr);
				EndBatchDraw();
				DrawBorder(BLACK);
				break;
			}

			case 32: {//���¿ո��
				//�����ɨ�����
				EdgeRelatedFill(final_vertex, fill_cr);
				break;
			}
			case 27: {//����ESC
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
