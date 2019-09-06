#include <iostream>

#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

// 火车购票
// 座位编号从 1 开始
// 每人购买不超过 5 张火车票

int ticketNo = 1;

void buy(vector<vector<int>> &seats, int& num)
{   // 向 seats 中填入 num 个数字
	for (int i = 0; i < 20; i++)
	{
		auto &row = seats[i];
		if (5 - row.size() >= num)
		{
			for (int j = 0; j < num; j++)
			{
				cout << i * 5 + row.size() + 1 << " ";
				row.push_back(ticketNo++);
			}
			return;
		}
	}
	int index = 0;
	auto iter = seats[0].begin();

	while (num > 0)
	{
		if (seats[index].size() == 5)
			iter = seats[++index].end();
		seats[index].insert(iter++, ticketNo++);
		cout << index * 5 + (iter - seats[index].begin()) << " ";
		num--;
	}
}

int main(int argc, char **argv)
{
	int n;  //购票指令数量
	cin >> n;
	vector<vector<int>> seats(20, vector<int>(0, 0));
	for (int i = 0; i < n; i++)
	{
		int k;
		cin >> k;
		buy(seats, k);
		cout << endl;
	}
	return 0;
}