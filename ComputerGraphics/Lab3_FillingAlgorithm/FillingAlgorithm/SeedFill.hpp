#ifndef _CZM_SEEDFILL_FUNS_
#define _CZM_SEEDFILL_FUNS_

#include<stack>
#define BG_CLOLOR BLACK

//��ȡ���ӵ����ұ߽�
void TestBoundary(const POINT& seed, POINT& left, POINT& right) {
	int y_scan = seed.y;
	int x_seed = seed.x;
	int x_max = getmaxx();
	COLORREF seed_cr = BG_CLOLOR;//����������ɫΪ����ɫ
	//��ȡ��߽�
	for (int i{ x_seed }; i > -1; i--) {
		if (getpixel(i, y_scan) != seed_cr) {
			left = { i + 1,y_scan };
			break;
		}
	}
	//��ȡ�ұ߽�
	for (int j{ x_seed }; j <= x_max; j++) {
		if (getpixel(j, y_scan) != seed_cr) {
			right = { j - 1 ,y_scan };
			break;
		}
	}
}

int TestXrmax(const int& x, const int&y) {
	//��ȡ�ұ߽�
	int x_max = getmaxx();
	COLORREF unfill_cr = BG_CLOLOR;//getpixel(x, y);//��ȡ���ӵ㵱ǰ��ɫ
	for (int j{ x }; j <= x_max; j++) {
		if (getpixel(j, y) != unfill_cr) {
			return j;
		}
	}
	return x;
}

//�ҵ���ǰɨ��������ɨ���ߵ����ӵ�
void FindNextSeed(const int&x_l, const int&x_r, const int&y_cur, std::stack<POINT>& seeds,const COLORREF& fill_cr) {
	POINT right{ -1,-1 }, left{ -1,-1 };
	//��һ��ɨ���ߵ����ӵ����
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
	//��һ��ɨ���ߵ����ӵ����
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
	POINT stack_top;//ջ��ȡ����Ԫ��
	POINT left{ -1,-1 }, right{ -1,-1 };//������߽��ұ߽�
	while (false == seeds.empty()) {
		stack_top = seeds.top();
		seeds.pop();
		TestBoundary(stack_top, left, right);//�õ���ǰ�����ұ߽�
		DrawScanLine(left.x, right.x, left.y, fill_cr);//��䵱ǰɨ����
		FindNextSeed(left.x, right.x, left.y, seeds,fill_cr);//��ȡ���µ����ӽڵ㣬����ջ
	}
}

//���߿�
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
