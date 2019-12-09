#ifndef _CZM_EDGETABLE_
#define _CZM_EDGETABLE_

#include"DrawLine.hpp"
#include<algorithm>
#include<vector>
#include<list>
using std::list;
/*
* ɨ�����������ı߽�����
*/
class AET {
public:
	float x;//�߽�������
	float dx;//����һ�߽�������Ĳ�ֵ
	int ymax;//�����õ�����ı߽������������
	AET(float xx = 0.0, float ddxx = 0.0, int yy = 0)
		:x(xx), dx(ddxx), ymax(yy) {}
	~AET() {
		x = dx = ymax = 0;
	}
};

/*
* �±߱��Ͱ�ڵ����
*/
class Bucket {
public:
	int y_scanline;//ɨ����������
	list<AET>edges;//ɨ������Ҫ��������ı߽���б�
	Bucket(int yy = -1, list<AET> new_edge = {}) :y_scanline(yy), edges(new_edge) {}
	~Bucket() {
		edges.clear();
		y_scanline = 0;
	}
};

//�����±߱�
void GenNetTable(const std::vector<POINT>& vertex, Bucket* BucketNodes, const int& ymin) {
	int N = vertex.size();
	list<AET> aet{};
	for (int i = 0; i < N; i++) {
		int i_next = (i + 1) % N;//������������һ�����������
		int dx = vertex[i].x - vertex[i_next].x;
		int dy = vertex[i].y - vertex[i_next].y;
		if (0 == dy)continue;
		int i_flag = dy < 0 ? i : i_next;//��Ҫ�����±߱��еı�־�������
		int ymax = dy > 0 ? vertex[i].y : vertex[i_next].y;//�±ߵ����ymax
		aet = BucketNodes[vertex[i_flag].y - ymin].edges;
		if (true == aet.empty())
			BucketNodes[vertex[i_flag].y - ymin].y_scanline = vertex[i_flag].y;
		BucketNodes[vertex[i_flag].y - ymin].edges.push_back({ float(vertex[i_flag].x),dx / float(dy),ymax });
	}
}

//������߱�
void GenAetTable(const int& ymax, const int& ymin, Bucket * BucketNodes) {
	list<AET> bn_aet;
	list<AET> nextBn_aet;
	for (int i{ 0 }; i < ymax - ymin + 1; i++) {
		bn_aet = BucketNodes[i].edges;
		if (true == bn_aet.empty())//�����ɨ�����ޱ߽�㣬����
			continue;
		for (AET ele : bn_aet) {
			if (ele.ymax > i + ymin + 1) {//�˴��ܱ����Ⱥ���
				nextBn_aet = BucketNodes[i + 1].edges;
				if (true == nextBn_aet.empty())
					BucketNodes[i + 1].y_scanline = i + ymin + 1;
				BucketNodes[i + 1].edges.push_back({ ele.x + ele.dx, ele.dx, ele.ymax });
			}
		}
	}
}

//���ɨ��������
void FillScanArea(const int& ymax, const int& ymin, const Bucket* BucketNodes, const COLORREF& fill_cr) {
	BeginBatchDraw();
	std::vector<int> x_scanline{};
	int y_scanline;
	list<AET>bn_aet{};
	for (int i{ 0 }; i < ymax - ymin + 1; i++) {
		bn_aet = BucketNodes[i].edges;
		//�����ɨ�����ϴ������ĵ�
		//???��߱�Ĵ�Сһ��Ϊż����Ϊʲô��
		if (false == bn_aet.empty()) {
			y_scanline = BucketNodes[i].y_scanline;
			for (AET ele : bn_aet) {
				x_scanline.push_back(ele.x);
			}
			//���򣺽�xֵ����������
			std::sort(x_scanline.begin(), x_scanline.end(), [](int a, int b) {return a < b; });
			//��Բ���ɫ
			int count = x_scanline.size();
			if (0 != count % 2)continue;
			for (int j{ 0 }; j < count; j += 2) {
				DrawScanLine(x_scanline[j], x_scanline[j + 1], y_scanline, fill_cr);
			}
			x_scanline.clear();
		}
	}
	EndBatchDraw();
}


//�����ɨ��������㷨
void EdgeRelatedFill(const std::vector<POINT>& vertex, const COLORREF& fill_cr) {
	int N = vertex.size();
	//��ymin��ymax
	int ymin{ vertex[0].y }, ymax{ vertex[0].y };
	for (int i{ 0 }; i < N; i++) {
		ymin = min(vertex[i].y, ymin);
		ymax = max(vertex[i].y, ymax);
	}
	Bucket* BucketNodes = new Bucket[ymax - ymin + 1];
	//�����±߱�
	GenNetTable(vertex, BucketNodes, ymin);
	//���ɻ�߱�
	GenAetTable(ymax, ymin, BucketNodes);
	//�󽻣������±߱� => ��߱�
	//����ɨ��
	FillScanArea(ymax, ymin, BucketNodes, fill_cr);
}


#endif
