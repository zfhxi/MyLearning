#ifndef _CZM_EDGETABLE_
#define _CZM_EDGETABLE_

#include"DrawLine.hpp"
#include<algorithm>
#include<vector>
#include<list>
using std::list;
/*
* 扫描线填充区间的边界点对象
*/
class AET {
public:
	float x;//边界点横坐标
	float dx;//与下一边界点横坐标的差值
	int ymax;//递增得到后代的边界点的最大纵坐标
	AET(float xx = 0.0, float ddxx = 0.0, int yy = 0)
		:x(xx), dx(ddxx), ymax(yy) {}
	~AET() {
		x = dx = ymax = 0;
	}
};

/*
* 新边表的桶节点对象
*/
class Bucket {
public:
	int y_scanline;//扫描线纵坐标
	list<AET>edges;//扫描线需要填充的区间的边界点列表
	Bucket(int yy = -1, list<AET> new_edge = {}) :y_scanline(yy), edges(new_edge) {}
	~Bucket() {
		edges.clear();
		y_scanline = 0;
	}
};

//建立新边表
void GenNetTable(const std::vector<POINT>& vertex, Bucket* BucketNodes, const int& ymin) {
	int N = vertex.size();
	list<AET> aet{};
	for (int i = 0; i < N; i++) {
		int i_next = (i + 1) % N;//顶点序列中下一个顶点的索引
		int dx = vertex[i].x - vertex[i_next].x;
		int dy = vertex[i].y - vertex[i_next].y;
		if (0 == dy)continue;
		int i_flag = dy < 0 ? i : i_next;//需要插入新边表中的标志点的索引
		int ymax = dy > 0 ? vertex[i].y : vertex[i_next].y;//新边的最大ymax
		aet = BucketNodes[vertex[i_flag].y - ymin].edges;
		if (true == aet.empty())
			BucketNodes[vertex[i_flag].y - ymin].y_scanline = vertex[i_flag].y;
		BucketNodes[vertex[i_flag].y - ymin].edges.push_back({ float(vertex[i_flag].x),dx / float(dy),ymax });
	}
}

//建立活动边表
void GenAetTable(const int& ymax, const int& ymin, Bucket * BucketNodes) {
	list<AET> bn_aet;
	list<AET> nextBn_aet;
	for (int i{ 0 }; i < ymax - ymin + 1; i++) {
		bn_aet = BucketNodes[i].edges;
		if (true == bn_aet.empty())//如果该扫描线无边界点，跳过
			continue;
		for (AET ele : bn_aet) {
			if (ele.ymax > i + ymin + 1) {//此处能保留等号吗？
				nextBn_aet = BucketNodes[i + 1].edges;
				if (true == nextBn_aet.empty())
					BucketNodes[i + 1].y_scanline = i + ymin + 1;
				BucketNodes[i + 1].edges.push_back({ ele.x + ele.dx, ele.dx, ele.ymax });
			}
		}
	}
}

//填充扫描线区域
void FillScanArea(const int& ymax, const int& ymin, const Bucket* BucketNodes, const COLORREF& fill_cr) {
	BeginBatchDraw();
	std::vector<int> x_scanline{};
	int y_scanline;
	list<AET>bn_aet{};
	for (int i{ 0 }; i < ymax - ymin + 1; i++) {
		bn_aet = BucketNodes[i].edges;
		//如果该扫描线上存在填充的点
		//???活动边表的大小一定为偶数吗？为什么？
		if (false == bn_aet.empty()) {
			y_scanline = BucketNodes[i].y_scanline;
			for (AET ele : bn_aet) {
				x_scanline.push_back(ele.x);
			}
			//排序：将x值按升序排列
			std::sort(x_scanline.begin(), x_scanline.end(), [](int a, int b) {return a < b; });
			//配对并着色
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


//边相关扫描线填充算法
void EdgeRelatedFill(const std::vector<POINT>& vertex, const COLORREF& fill_cr) {
	int N = vertex.size();
	//求ymin，ymax
	int ymin{ vertex[0].y }, ymax{ vertex[0].y };
	for (int i{ 0 }; i < N; i++) {
		ymin = min(vertex[i].y, ymin);
		ymax = max(vertex[i].y, ymax);
	}
	Bucket* BucketNodes = new Bucket[ymax - ymin + 1];
	//生成新边表
	GenNetTable(vertex, BucketNodes, ymin);
	//生成活动边表
	GenAetTable(ymax, ymin, BucketNodes);
	//求交：更新新边表 => 活动边表
	//逐行扫描
	FillScanArea(ymax, ymin, BucketNodes, fill_cr);
}


#endif
