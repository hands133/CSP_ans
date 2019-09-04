#include <iostream>

#include <vector>
#include <set>

using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::set;
using std::pair;

// 碰撞的小球

enum dir { LEFT, RIGHT };    // 小球方向
const int SPEED = 1;        // 小球速度

struct ball
{
	dir direction;
	int pos;
	ball(const int& p) : direction(RIGHT), pos(p) {}
};

void changeDir(ball & b)
{
	b.direction = (b.direction == LEFT) ? RIGHT : LEFT;
}


int main(int argc, char** argv)
{
	int L;  // 线段长度
	int n;  // 小球个数
	int t;  // 时间间隔
	cin >> n >> L >> t;
	vector<ball> container(n, ball(0));
	vector<pair<int, int>> mapping(L + 1, pair<int, int>(-1, -1));  // 球下标到位置的映射

	for(int i = 0; i < n; i++)
	{
		auto &item = container[i];
		cin >> item.pos;
		if (item.pos == L)   item.direction = LEFT;
		mapping[item.pos].first = i;	// 一开始保证小球不相交
	}

	set<int> collapseIndex;

	for (int p = 0; p < t; p++)
	{   // 根据碰撞，小球的顺序不会改变
		for (int i = 0; i < n; i++)
		{
			auto &item = container[i];	//获得小球
			int originPos = item.pos;	// 小球位置
			mapping[originPos] = pair<int, int>(-1, -1);	// 位置归零

			if (item.pos == 0)   item.direction = RIGHT;
			if (item.pos == L)   item.direction = LEFT;
			if (item.direction == LEFT)		item.pos--;
			if (item.direction == RIGHT)	item.pos++;
	
			if (mapping[item.pos].first == -1)	mapping[item.pos].first = i;
			else
			{
				mapping[item.pos].second = i;
				collapseIndex.insert(item.pos);	//注意碰撞的小球会让下标记录两次
			}
		}
		// 处理碰撞小球
		auto index = collapseIndex.begin();
		while (index != collapseIndex.end())
		{
			int ball1Index = mapping[*index].first;	// 小球 1 下标
			int ball2Index = mapping[*index].second;	// 小球 2 下标
			ball &ball1 = container[ball1Index];	// 小球 1
			ball &ball2 = container[ball2Index];	// 小球 2
			changeDir(ball1);
			changeDir(ball2);
			index++;
		}
		collapseIndex.clear();
	}
	for (auto &item : container)
		cout << item.pos << " ";
	cout << endl;

	//system("pause");
	return 0;
}