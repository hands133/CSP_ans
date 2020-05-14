#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<queue>
#include<set>
using namespace std;


//错误，得分40分
struct Poisition {
	int u = 0, v = 0;
	Poisition() {}
	Poisition(int x, int y) :u(x), v(y) {}
	bool operator < (const Poisition& p) const
	{
		if (u != p.u)
			return v < p.v;
		return u < p.u;
	}
};


int main()
{
	int T, n;
	cin >> T >> n;
	cin.get();
	/*
	思路：将yRx命令或xSy命令表示未(x,y)对，如果set中有对应的对就删除，如果没有就添加。如果执行了删除操作
	就表明两个进程指令可以向下进行，如果最后set中非空且指令序列已空则未死锁。
	*/
	vector<vector<string>> data(T, vector<string>(n));
	set<Poisition> graph;
	queue<int> no_deadlock;
	for (int i = 0; i < T; i++)
	{//读取数据并存储到data中
		for (int j = 0; j < n; j++)
		{
			string str;
			getline(cin, str);
			data[i][j] = str;

		}
	}


	for (int i = 0; i < T; i++)
	{
		vector<string>& all = data[i];
		for (int i = 0; i < n; i++)
		{//初始均没有死锁
			no_deadlock.push(i);
		}
		while (!no_deadlock.empty())
		{
			int u = no_deadlock.front();
			no_deadlock.pop();
			if (all[u].length() < 2)
				continue;
			string one = all[u].substr(0, 2);//进程t的一条指令
			all[u].erase(0, 3);

			int v = one[1] - 48;
			if (one[0] == 'R')
			{
				
				Poisition tp(v, u);
				if (graph.count(tp) == 1)
				{
					no_deadlock.push(u);
					no_deadlock.push(v);
					graph.erase(tp);
				}
				else
					graph.insert(tp);
			}
			else if (one[0] == 'S')
			{
				Poisition tp(u, v);
				if (graph.count(tp) == 1)
				{
					no_deadlock.push(u);
					no_deadlock.push(v);
					graph.erase(tp);
				}
				else
					graph.insert(tp);
			}

		}

		bool flag = true;
		for (int j = 0; j < all.size() && flag; j++)
		{
			if (all[j] != "")
				flag = false;
		}
		if (flag && graph.empty())//如果all空(即指令已经全部执行或待执行)，且graph没有未执行的指令对，则没有死锁
			cout << 0 << endl;
		else
			cout << 1 << endl;
		graph.clear();

	}




	return 0;
}
/*
3 2
R1 S1
S0 R0
R1 S1
R0 S0
R1 R1 R1 R1 S1 S1 S1 S1
S0 S0 S0 S0 R0 R0 R0 R0



2 3
R1 S1
R2 S0 R0 S2
S1 R1
R1
R2 S0 R0
S1 R1



*/
