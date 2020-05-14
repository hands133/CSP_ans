#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<fstream>
//prim算法，邻接链表(set)储存，超时，得分20
using namespace std;


struct edge {
	int u = 0;
	int v = 0;
	int w = 0;
	edge() {}
	edge(int uu, int vv, int ww) :u(uu), v(vv), w(ww) {}
	bool operator < (const edge& a) const
	{
		int min = u > v ? v : u;
		int max = u > v ? u : v;
		int min1 = a.u > a.v ? a.v : a.u;
		int max1 = a.u > a.v ? a.u : a.v;
		if (w == a.w)
			if (min == min1)
				return max < max1;
			else
				return min < min1;
		else
			return w < a.w;
	}
};

int main()
{
	int m, n, root;
	cin >> n >> m >> root;

	vector<set<edge>> g(n + 1);//边的集合


	int i, j, w;
	for (int s = 0; s < m; s++)
	{
		cin >> i >> j >> w;
		g[i].insert(edge(i, j, w));
		g[j].insert(edge(j, i, w));
	}

	set<int> vs;//从中遍历点的邻接链表以选择合适的边
	vs.insert(root);

	edge min, max;
	while (vs.size() != n)
	{
		for (auto it = vs.begin(); it != vs.end(); it++)
		{
			for (auto ite = g[*it].begin(); ite != g[*it].end(); ite++)
			{
				if (vs.count(ite->v) == 1)//如果形成环
					continue;
				if (min.w == 0 || ite->w < min.w)
					min = *ite;
				break;//因为邻接链表组织成了set，有序，所以对于一个点来说，找到其邻接的第一个不成环的边即可结束循环
				
			}
		}
		vs.insert(min.u);
		vs.insert(min.v);
		if (min.w > max.w)
			max = min;
		if (vs.size() == n)
			break;

		g[min.u].erase(min);
		g[min.v].erase(min);
		min = edge();


	}
	cout << max.w;
	return 0;
}
/*
4
5
1
1 2 3
1 3 4
1 4 5
2 3 8
3 4 2
*/
