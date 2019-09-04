#include <iostream>

#include <vector>
#include <tuple>

using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::pair;
using std::tuple;

// 买菜

// 小H和小W来到了一条街上，两人分开买菜，他们买菜的过程可以描述为，去店里买一些菜然后去旁边的一个广场把菜装上车，两人都要买n种菜，所以也都要装n次车。具体的，对于小H来说有n个不相交的时间段[a1,b1],[a2,b2]...[an,bn]在装车，对于小W来说有n个不相交的时间段[c1,d1],[c2,d2]...[cn,dn]在装车。其中，一个时间段[s, t]表示的是从时刻s到时刻t这段时间，时长为t-s。
// 　　由于他们是好朋友，他们都在广场上装车的时候会聊天，他们想知道他们可以聊多长时间。

const int max(const int &l, const int &r)
{
	return (l >= r) ? l : r;
}

const int min(const int &l, const int &r)
{
	return (l <= r) ? l : r;
}

std::tuple<int, bool> compare(const pair<int, int> &Hiter, const pair<int, int> &W)
{
	int timeGap = 0;
	int maxL = max(Hiter.first, W.first);
	int minR = min(Hiter.second, W.second);
	int minL = min(Hiter.first, W.first);
	int maxR = max(Hiter.second, W.second);
	if (maxL >= minR)
		return std::make_tuple(0, W.second < Hiter.second);
	timeGap = minR - maxL;
	return std::make_tuple(timeGap, W.second <= Hiter.second);
}

int main(int argc, char **argv)
{
	int n;
	cin >> n;   // 时间段
	vector<pair<int, int>> littleH(n, pair<int, int>(0, 0)), littleW(n, pair<int, int>(0, 0));
	int time = 0;
	std::tuple<int, bool> comp;
	for (pair<int, int> &iter : littleH)
		cin >> iter.first >> iter.second;
	for (pair<int, int> &iter : littleW)
	{
		cin >> iter.first >> iter.second;
		for (auto &iterH : littleH)
		{
			comp = compare(iterH, iter);
			time += std::get<0>(comp);
			if (std::get<1>(comp) == true)	break;
		}
	}
	cout << time << endl;
	// system("pause");
	return 0;
}