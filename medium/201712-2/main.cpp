#include <iostream>

#include <vector>
#include <list>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::list;

// 游戏
// 有n个小朋友围成一圈玩游戏，小朋友从1至n编号，2号小朋友坐在1号小朋友的顺时针方向，3号小朋友坐在2号小朋友的顺时针方向，……，1号小朋友坐在n号小朋友的顺时针方向。
// 　　游戏开始，从1号小朋友开始顺时针报数，接下来每个小朋友的报数是上一个小朋友报的数加1。若一个小朋友报的数为k的倍数或其末位数（即数的个位）为k，则该小朋友被淘汰出局，不再参加以后的报数。当游戏中只剩下一个小朋友时，该小朋友获胜。
// 　　例如，当n=5, k=2时：
// 　　1号小朋友报数1；
// 　　2号小朋友报数2淘汰；
// 　　3号小朋友报数3；
// 　　4号小朋友报数4淘汰；
// 　　5号小朋友报数5；
// 　　1号小朋友报数6淘汰；
// 　　3号小朋友报数7；
// 　　5号小朋友报数8淘汰；
// 　　3号小朋友获胜。

int main(int argc, char **argv)
{
	int n;  // 孩子个数 1 <= n <= 1000
	int k;  // 淘汰数字 1 <= 9
	cin >> n >> k;
	list<int> children;
	auto iter = children.begin();
	for (int i = 0; i < n; i++)
		children.insert(iter, i + 1);
	int baoshu = 1;
	while (children.size() != 1)
	{
		iter = children.begin();
		while (iter != children.end())
		{
			if (baoshu % k == 0 || baoshu % 10 == k)
			{
				iter = children.erase(iter);
				if (children.size() == 1)    goto res;
			}
			else
				iter++;
			baoshu++;
		}
	}
res:
	cout << *children.begin() << endl;

	system("pause");
	return 0;
}