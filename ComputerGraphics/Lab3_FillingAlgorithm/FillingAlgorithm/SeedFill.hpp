#ifndef _CZM_SEEDFILL_FUNS_
#define _CZM_SEEDFILL_FUNS_

#include<stack>
#define BG_CLOLOR BLACK

//获取种子点左右边界
void TestBoundary(const POINT& seed, POINT& left, POINT& right) {
	int y_scan = seed.y;
	int x_seed = seed.x;
	int x_max = getmaxx();
	COLORREF seed_cr = BG_CLOLOR;//假设种子颜色为背景色
	//获取左边界
	for (int i{ x_seed }; i > -1; i--) {
		if (getpixel(i, y_scan) != seed_cr) {
			left = { i + 1,y_scan };
			break;
		}
	}
	//获取右边界
	for (int j{ x_seed }; j <= x_max; j++) {
		if (getpixel(j, y_scan) != seed_cr) {
			right = { j - 1 ,y_scan };
			break;
		}
	}
}

int TestXrmax(const int& x, const int&y) {
	//获取右边界
	int x_max = getmaxx();
	COLORREF unfill_cr = BG_CLOLOR;//getpixel(x, y);//获取种子点当前颜色
	for (int j{ x }; j <= x_max; j++) {
		if (getpixel(j, y) != unfill_cr) {
			return j;
		}
	}
	return x;
}

//找到当前扫描线上下扫描线的种子点
void FindNextSeed(const int&x_l, const int&x_r, const int&y_cur, std::stack<POINT>& seeds,const COLORREF& fill_cr) {
	POINT right{ -1,-1 }, left{ -1,-1 };
	//上一条扫描线的种子点添加
	int i{ x_l };
	int y{ y_cur + 1 };
	int x_max = TestXrmax(x_r, y);
	for (; i <= x_max; i++) {
		while (getpixel(i, y) != fill_cr)
			if (++i > x_max)break;
		if (i - 1 >= x_l && getpixel(i - 1, y) != fill_cr)
			seeds.push(POINT{ i - 1 ,y });
		while (getpixel(i, y) == fill_cr)
			if (++i > x_max)break;
	}
	//下一条扫描线的种子点添加
	i = x_l;
	y = y_cur - 1;
	x_max = TestXrmax(x_r, y);
	for (; i <= x_max; i++) {
		while (getpixel(i, y) != fill_cr)
			if (++i > x_max)break;
		if (i - 1 >= x_l && getpixel(i - 1, y) != fill_cr)
			seeds.push(POINT{ i - 1 ,y });
		while (getpixel(i, y) == fill_cr)
			if (++i > x_max)break;
	}
}

void SeedFill(std::stack<POINT>&seeds, const COLORREF& fill_cr) {
	POINT stack_top;//栈顶取出的元素
	POINT left{ -1,-1 }, right{ -1,-1 };//种子左边界右边界
	while (false == seeds.empty()) {
		stack_top = seeds.top();
		seeds.pop();
		TestBoundary(stack_top, left, right);//得到当前的左右边界
		DrawScanLine(left.x, right.x, left.y, fill_cr);//填充当前扫描线
		FindNextSeed(left.x, right.x, left.y, seeds,fill_cr);//获取上下的种子节点，并入栈
	}
}

//画边框
void DrawBorder(const COLORREF&fill_cr) {
	for (int i{ 0 }; i <= getmaxx(); i++) {
		putpixel(i, 0, fill_cr);
		putpixel(i, getmaxy(), fill_cr);
	}
	for (int i{ 0 }; i <= getmaxy(); i++) {
		putpixel(0, i, fill_cr);
		putpixel(getmaxx(), i, fill_cr);
	}
}

#endif // !_CZM_SEEDFILL_FUNS_
