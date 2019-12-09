#pragma once

//encode [��,��,��,��]
#define TOP 8
#define BOTTOM 4
#define RIGHT 2
#define LEFT 1
#define INPOINT 0
#define OUTPOINT 1


#include<vector>
#include"DrawPolygon.hpp"
#include"EdgeFill.hpp"
using std::vector;



//�����������
int EnCode(float x, float y, const vector<POINT>&win_vtx) {
	int xmin = win_vtx[1].x;
	int ymin = win_vtx[1].y;
	int xmax = win_vtx[3].x;
	int ymax = win_vtx[3].y;
	int code = 0;
	if (x < xmin)code |= LEFT;
	if (x > xmax) code |= RIGHT;
	if (y < ymin)code |= BOTTOM;
	if (y > ymax)code |= TOP;
	return code;
}

//����(x,y)Ϊ���ܵĽ���
void UpdateToIntersection(const int& c, float& x, float&y, const float&k, const vector<POINT>& win_vtx) {
	int xmin = win_vtx[1].x;
	int ymin = win_vtx[1].y;
	int xmax = win_vtx[3].x;
	int ymax = win_vtx[3].y;
	if (0 != (c&LEFT)) {//�˵������
		y += k * (xmin - x);
		x = xmin;
	}
	else if (0 != (c&RIGHT)) {//�˵����Ҳ�
		y += k * (xmax - x);
		x = xmax;
	}
	else if (0 != (c&BOTTOM)) {//�˵����²�
		x += (ymin - y) / k;
		y = ymin;
	}
	else {//�˵����ϲ�
		x += (ymax - y) / k;
		y = ymax;
	}
}

//ֱ�߲ü�
void LineCutting(const vector<POINT>line_vtx, const vector<POINT>&win_vtx, const COLORREF& stroke_cr) {
	float x0{ float(line_vtx[0].x) }, y0{ float(line_vtx[0].y) };
	float x1{ float(line_vtx[1].x) }, y1{ float(line_vtx[1].y) };
	int c0{ EnCode(x0,y0,win_vtx) };
	int c1{ EnCode(x1,y1,win_vtx) };
	int draw_flag = 1;
	const float k{ (y1 - y0) / (x1 - x0) };

	while (0 != c0) {//����˵��ڴ�����
		if (0 != (c0&c1)) {//ֱ�߶����ϵ��ڴ���ͬ��
			draw_flag = 0;//����Ҫ��ֱ��
			break;
		}
		//����Ϊ�봰�ڵĶ˵�
		UpdateToIntersection(c0, x0, y0, k, win_vtx);
		//���±���
		c0 = EnCode(x0, y0, win_vtx);
	}
	while ((1 == draw_flag) && 0 != c1) {//����˵��ڴ�����
		//����Ϊ�봰�ڵĶ˵�
		UpdateToIntersection(c1, x1, y1, k, win_vtx);
		//���±���
		c1 = EnCode(x1, y1, win_vtx);
	}
	if (1 == draw_flag)
		BresenhamLine(POINT{ int(x0 + 0.5),int(y0 + 0.5) }, POINT{ int(x1 + 0.5) ,int(y1 + 0.5) }, stroke_cr, false);
}

//��λԪ���������е�����
int GetPosInVec(const mpoint&point, const vector<mpoint>& vec) {
	int vecsize = vec.size();
	for (int i{ 0 }; i < vecsize; i++)
		if (Fequal(point.x, vec[i].x)
			&& Fequal(point.y, vec[i].y)
			&& (point.flag == vec.at(i).flag))
			return i;
	return -1;
}

//�򴰿������в��뽻��
void InsCrossPt2Wnd(int code, const mpoint& mpt, vector<mpoint>& win_vec, const vector<POINT> win_vtx) {
	float xmin = win_vtx[1].x;
	float ymin = win_vtx[1].y;
	float xmax = win_vtx[3].x;
	float ymax = win_vtx[3].y;
	float xx{ mpt.x }, yy{ mpt.y };
	if (0 != (code&LEFT)) {//�˵������
		auto e = win_vec.begin() + GetPosInVec({ xmin,ymax }, win_vec);
		auto posend = win_vec.begin() + GetPosInVec({ xmin,ymin }, win_vec);
		while (yy <= (*e).y)if (++e > posend)break;
		win_vec.insert(e, mpt);
	}
	else if (0 != (code&RIGHT)) {//�˵����Ҳ�
		auto e = win_vec.begin() + GetPosInVec({ xmax,ymin }, win_vec);
		auto posend = win_vec.begin() + GetPosInVec({ xmax,ymax }, win_vec);
		while (yy >= (*e).y)if (++e > posend)break;
		win_vec.insert(e, mpt);
	}
	else if (0 != (code&TOP)) {//�˵�����Ļ�²࣬��������ϵ���ϲ�
		auto e = win_vec.begin() + GetPosInVec({ xmax,ymax }, win_vec);
		auto posend = win_vec.end();
		while (xx <= (*e).x)if (++e >= posend)break;
		win_vec.insert(e, mpt);
	}
	else {//�˵�����Ļ�ϲ࣬��������ϵ���²�
		auto e = win_vec.begin() + GetPosInVec({ xmin,ymin }, win_vec);
		auto posend = win_vec.begin() + GetPosInVec({ xmax,ymin }, win_vec);
		while (xx >= (*e).x)if (++e > posend)break;
		win_vec.insert(e, mpt);
	}

}

//�����󽻵�
mpoint GetInterSection(const float&x, const float&y, const int&theother_code, const float&k, const vector<POINT>& win_vtx, int type, vector<mpoint>& win_vec) {
	float xx{ x }, yy{ y };
	int code{ EnCode(xx, yy, win_vtx) };
	int tmpcode;
	mpoint intersec;
	if (0 == code)//�ڴ����ڡ����ߴ��ڱ�
		return mpoint{ xx,yy,2 };
	while (0 != code) {//�ڴ�����,�����н��㣬Ҳ�����޽���
		if (0 != (code&theother_code))//����޽��㣬��ô����ͬ��
			return { -1,-1,-10 };
		UpdateToIntersection(code, xx, yy, k, win_vtx);
		tmpcode = EnCode(xx, yy, win_vtx);
		if (0 == tmpcode) {//���뽻�㵽���ڶ�������
			intersec = { float(int(xx+0.5)),float(int(yy+0.5)),type };
			if (!existInVec(intersec, win_vec)) {
				InsCrossPt2Wnd(code, intersec, win_vec, win_vtx);
			}
		}
		code = tmpcode;
	}
	return intersec;
}

//�Ӷ���ζ���������ȡ��㵽��������е㣬���س���
mpoint GetOutPoint(const mpoint& in_point, vector<mpoint>&polyvertx, vector<POINT>&dstvec) {
	int in_idx = GetPosInVec(in_point, polyvertx);
	int i{ in_idx };
	int len = polyvertx.size();
	mpoint out_point{};
	mpoint p{};
	while (true) {
		i = (i + 1) % len;
		p = *(polyvertx.begin() + i);
		dstvec.push_back({ int(p.x + 0.5),int(p.y + 0.5) });
		if (1 == p.flag) {
			out_point = p;
			break;
		}
	}
	//����������һ������֮��ĵ�
			//DrawPoints(cuttedvertx);
	if (in_idx <= i)
		polyvertx.erase(polyvertx.begin() + in_idx, polyvertx.begin() + i + 1);
	else {
		polyvertx.erase(polyvertx.begin() + in_idx, polyvertx.end());
		polyvertx.erase(polyvertx.begin(), polyvertx.begin() + i + 1);
	}
	return out_point;
}

//�Ӵ��ڶ���������ȡ���㵽�������е㣬�������
mpoint GetInPoint(const mpoint& out_point, const vector<mpoint>&wndvtx, vector<POINT>&dstvec) {
	int out_idx = GetPosInVec(out_point, wndvtx);
	int i{ out_idx };
	int len = wndvtx.size();
	mpoint in_point{};
	mpoint p{};
	while (true) {
		i = (i + 1) % len;
		p = *(wndvtx.begin() + i);
		dstvec.push_back({ int(p.x + 0.5),int(p.y + 0.5) });
		if (0 == p.flag) {
			in_point = p;
			break;
		}
	}
	return in_point;
}

//ͨ���󽻵���´��ںͶ���ζ�������
void UpdateVtxsByCorssPt(const vector<POINT>&poly_vtx, vector<mpoint>&polyvertx, const vector<POINT>& win_vtx, vector<mpoint>&wndvtx) {
	mpoint tmpoint;
	float x0, y0, x1, y1;
	int code0, code1;
	float k;
	int polysize = poly_vtx.size();
	int flag0, flag1;
	for (int i{ 0 }; i < polysize; ++i) {
		//��ȡ�����ĳ�����˵�����
		x0 = float(poly_vtx.at(i%polysize).x);
		y0 = float(poly_vtx.at(i%polysize).y);
		x1 = float(poly_vtx.at((i + 1) % polysize).x);
		y1 = float(poly_vtx.at((i + 1) % polysize).y);
		code0 = EnCode(x0, y0, win_vtx);
		code1 = EnCode(x1, y1, win_vtx);
		//ȡ��б��
		k = (y1 - y0) / (x1 - x0);
		//��Ҫ��ĳ�˵�����Ĭ����Ҫ��
		flag0 = 1;
		flag1 = 1;
		if (0 == code0) { //�ڴ���
			polyvertx.push_back({ x0,y0,2 });
			flag0 = 0;//������Ҫ��
		}
		if (0 == code1) { //�ڴ���
			//Ϊ�δ˴������룬��Ϊ�ڶ����������һ�ֳ�Ϊ��һ����
			flag1 = 0;//������Ҫ��
		}
		//�����˵��ڴ��ⲻͬ��,Ҳ����������һ���ڴ���
		if (0 == (code0&code1)) {
			if (1 == flag0) {//���һ������
				tmpoint = GetInterSection(x0, y0, code1, k, win_vtx, INPOINT, wndvtx);
				if (-10 != tmpoint.flag) {
					tmpoint.x = int(tmpoint.x + 0.5);
					tmpoint.y = int(tmpoint.y + 0.5);
					polyvertx.push_back(tmpoint);
				}
			}
			if (1 == flag1) {//��ڶ�������
				tmpoint = GetInterSection(x1, y1, code0, k, win_vtx, OUTPOINT, wndvtx);
				if (-10 != tmpoint.flag) {
					tmpoint.x = int(tmpoint.x + 0.5);
					tmpoint.y = int(tmpoint.y + 0.5);
					polyvertx.push_back(tmpoint);
				}
			}
		}
		if (2 == polysize)break;//�����һ��ֱ��
	}
}

//�ӹ����Ķ���ζ������кʹ��������зֱ���Ѱ�����ԣ��ҵ��ü���Ķ���Σ�������
int DrawCuttedPoly(vector<mpoint>&polyvertx, const vector<mpoint>&wndvtx, const COLORREF& cr) {
	vector<POINT>cuttedvertx{};//�ü���Ķ���ζ�������
	mpoint p_inpt{ -1,-1 };//��������
	mpoint tmpt{};//��ʱ�ݴ��
	int poly_in_wnd = 0;//0-������εı߲�ȫ�ڴ����ڣ��Ҷ�����봰���н��� OR ����εı�ȫ�ڴ����ڣ�-1������ȫ�ڶ������ OR �����������޽���
	//����ȫ�ڶ������. --> �������½��Ķ���ζ�������ȫΪ��
	if (true == polyvertx.empty())//�����ڶ�����ڲ� OR �����������޽���
		poly_in_wnd = -1;
	else {
		while (false == polyvertx.empty()) {
			//Ѱ�ҵ�һ����㣬��һû�ҵ���ô�죿//�ڶ����ȫ�ڴ�����ʱ�������
			for (const auto& e : polyvertx) {
				if (0 == e.flag) {
					p_inpt = e;
					cuttedvertx.push_back({ int(p_inpt.x + 0.5),int(p_inpt.y + 0.5) });
					break;
				}
			}
			if (-1 == p_inpt.x) {//�����ȫ�ڴ����ڣ�
				for (auto e : polyvertx)
					cuttedvertx.push_back({ int(e.x + 0.5),int(e.y + 0.5) });
				polyvertx.clear();
			}
			else {
				while (1) {
					//��ȡ�����Ե�Ŀ������
					tmpt = GetOutPoint(p_inpt, polyvertx, cuttedvertx);
					//ͨ���ռ���ĳ��㣬�ڴ����������ҳ�����
					tmpt = GetInPoint(tmpt, wndvtx, cuttedvertx);
					if (cuttedvertx.back() == cuttedvertx.front()) {
						cuttedvertx.pop_back();
						break;
					}
					p_inpt = tmpt;
				}
			}
			EdgeRelatedFill(cuttedvertx, cr);
			DrawPolygon(cuttedvertx, cr);
			cuttedvertx.clear();
			p_inpt = { -1,-1 };
		}
	}
	return poly_in_wnd;
}

void DrawWndOrNot(const vector<POINT>&poly_vtx, const vector<POINT>&win_vtx, const vector<mpoint>&wndvtx, const COLORREF&stroke_cr) {
	//�жϵ��ڶ�����ڻ����⣬��ż��⣬�Դ��ڶ���{xmax,ymax}Ϊ��
	POINT A = { win_vtx[3].x,win_vtx[3].y };
	POINT B = { getmaxx(),win_vtx[3].y };

	int counter{};
	int len = poly_vtx.size();
	int x_next{}, y_next{}, x_cur{}, y_cur{};
	for (int i{}; i < len; i++) {
		x_cur = poly_vtx[i].x;
		y_cur = poly_vtx[i].y;
		x_next = poly_vtx[(i + 1) % len].x;
		y_next = poly_vtx[(i + 1) % len].y;
		if (x_cur > A.x&&y_cur == A.y) {//����Ϊ��ǰ����
			//if(y_cur<=y_next)��������0
			if (y_cur > y_next)counter++;
		}
		else if (x_next > A.x&&y_next == A.y) {//����Ϊ��һ����
			//if(y_cur>=y_next)��������0
			if (y_cur < y_next)counter++;
		}
		else {
			if (true == isCross(A, B, { x_cur,y_cur }, { x_next,y_next }))//���߶ν��ڷǶ˵�
				counter++;
		}
	}
	if (0 != counter % 2) {//�������ϵ��ڶ������
		DrawPolygon(wndvtx, stroke_cr);
		EdgeRelatedFill(MpointVec2PointVec(wndvtx), stroke_cr);
	}
}

//��ʾ�ü�����
void ShowCuttingWindow(const POINT&left_bottom, const POINT&right_top, const COLORREF& cr) {
	int xmin = min(left_bottom.x, right_top.x);
	int xmax = max(left_bottom.x, right_top.x);
	int ymin = min(left_bottom.y, right_top.y);
	int ymax = max(left_bottom.y, right_top.y);
	for (int i{ xmin + 1 }; i < xmax; i++) {
		if (0 != i % 5) {
			CurPtsBuffer.push_back(PointCr{ POINT{i,ymin},getpixel(i,ymin) });
			putpixel(i, ymin, cr);
			CurPtsBuffer.push_back(PointCr{ POINT{i,ymax},getpixel(i,ymax) });
			putpixel(i, ymax, cr);
		}
	}
	for (int j{ ymin }; j <= ymax; j++) {
		if (0 != j % 5) {
			CurPtsBuffer.push_back(PointCr{ POINT{xmin,j},getpixel(xmin,j) });
			putpixel(xmin, j, cr);
			CurPtsBuffer.push_back(PointCr{ POINT{xmax,j},getpixel(xmax,j) });
			putpixel(xmax, j, cr);
		}
	}
}

