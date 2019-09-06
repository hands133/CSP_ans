#include <iostream>

#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

// 学生排队

vector<int> queue, mapping;
int n;  // 学生数量

const int ABS(const int& x)
{
	return (x <= 0) ? -x : x;
}

void swap(int &l, int& r)
{
	int t = l;
	l = r;
	r = t;
}

void adjuge(const int& p, const int& q)
{   // 将编号为 p 的移动 q 距离
	// q 为正向后移，为负向前移
	int index = mapping[p]; // p 从 1 起
	int loopTimes = ABS(q);
	int dir = q / loopTimes;
	if (dir == -1 && loopTimes > index)			loopTimes = index;
	if (dir == 1 && loopTimes > n - index - 1)	loopTimes = n - index - 1;
	for (int i = 0; i < loopTimes; i++)
	{
		mapping[queue[index + dir * (i + 1)]] -= dir;
		swap(queue[index + dir * i], queue[index + dir * (i + 1)]);
	}
	mapping[p] = loopTimes * dir + index;
}

int main(int argc, char **argv)
{
	cin >> n;   // 学生的数量
	queue.resize(n);
	mapping.resize(n + 1);

	// queue 存储学生的编号
	// mapping 存储对应编号学生所在位置的映射
	for (int i = 0; i < n; i++)
	{
		queue[i] = i + 1;
		mapping[i + 1] = i;
	}
	int m;  // 调整次数
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int p, q;
		cin >> p >> q;
		adjuge(p, q);
	}
	for (int &n : queue)
		cout << n << " ";
	cout << endl;

	// system("pause");
	return 0;
}