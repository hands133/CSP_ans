#include<iostream>
#include<string>
#include<vector>
#include<set>
//kruskal算法，错误，为什么？？？？
using namespace std;


struct edge {
	int u = 0;
	int v = 0;
	int w = 0;
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
int find(int son, vector<int>& pre) //查找根结点
{
	if (pre[son] == son)
		return son;
	else
	{
		pre[son] = find(pre[son], pre);
		return pre[son];
	}
		
}

int main()
{
	int m, n, root;
	cin >> n >> m >> root;

	set<edge> g;//边的集合
	vector<int> pre(n + 1);//并查集

	for (int i = 0; i <= n; i++)//初始化并查集
		pre[i] = i;

	int i, j, w;
	for (int s = 0; s < m; s++)
	{
		cin >> i >> j >> w;
		g.insert(edge(i, j, w));
	}


	int es = 0;
	int max = 0;
	for (auto it = g.begin(); it != g.end() && es != n; it++)
	{
		edge t = *it;
		int m = find(t.u, pre), n = find(t.v, pre);
		if (m != n)//如果不属于同一连通分支，则此边符合条件可插入，并设置为同一连通分量
		{
			pre[t.v] = t.u;
			es++;
			max = max > t.w ? max : t.w;
			//cout << "插入边 " << t.u << " " << t.v << " " << t.w << endl;

		}


	}
	cout << max;



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


5
5
2
1 2 3
1 3 5
2 3 4
3 5 1
4 5 6


9
11
4
1 2 1
1 3 2
6 2 3
9 5 4
5 4 2
8 3 7
4 1 2
6 9 4
8 9 2
1 7 3
7 9 4
*/
