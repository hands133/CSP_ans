#include <iostream>

#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::priority_queue;

using std::operator<;

// 数字排序

struct node
{
	int num;
	int times;
	node() : num(0), times(0) {}
	node(const int &num, const int& times)
	{
		this->num = num;
		this->times = times;
	}
	bool operator<(const node& n) const
	{
		if (times != n.times)	return times < n.times;
		else	return num > n.num;
	}
};

int main(int argc, char **argv)
{
	int n;  // 数字个数
	cin >> n;
	vector<int> container(1001, 0);
	for (int i = 0; i < n; i++)
	{
		int k;
		cin >> k;
		container[k] ++;
	}
	priority_queue<node, vector<node>, std::less<node>> queue;
	for (int i = 0; i < 1001; i++)
	{
		if (container[i] != 0)
			queue.push(node(i, container[i]));
	}
	while (!queue.empty())
	{
		auto &item = queue.top();
		cout << item.num << " " << item.times << endl;
		queue.pop();
	}
	//system("pause");
	return 0;
}