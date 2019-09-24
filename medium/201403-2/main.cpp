#include <iostream>

#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::pair;

// 窗口

struct window
{
	int left, right, top, bottom, No;
	window() : left(0), right(0), top(0), bottom(0), No(0) {}
	window(const window& w)
	{
		left = w.left;
		right = w.right;
		bottom = w.bottom;
		top = w.top;
		No = w.No;
	}
	void set(const int& x1, const int& y1, 
		const int& x2, const int& y2, const int& No)
	{
		left = x1;
		right = x2;
		bottom = y1;
		top = y2;
		this->No = No;
	}
};

void judge(vector<window> &windows, const int& px, const int& py)
{
	auto iter = windows.rbegin();   //反向迭代器
	while (iter != windows.rend())
	{
		if ((*iter).left <= px && px <= (*iter).right
			&& (*iter).bottom <= py && py <= (*iter).top)
		{
			cout << (*iter).No << endl;
			window item = *iter;
			windows.erase(--iter.base());
			windows.push_back(item);
			return;
		}
		iter++;
	}
	cout << "IGNORED" << endl;
}

int main(int argc, char **argv)
{
	int N;  // 窗口数量
	int M;  // 鼠标点击次数
	cin >> N >> M;
	vector<window> windows(N);
	vector<pair<int,int> > mouseFunc(M);
	int i = 1;
	for (window &iter : windows)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		iter.set(x1, y1, x2, y2, i++);
	}
	for (pair<int, int> &iter : mouseFunc)
		cin >> iter.first >> iter.second;
	for (pair<int, int> &iter : mouseFunc)
		judge(windows, iter.first, iter.second);
	//system("pause");
	return 0;
}