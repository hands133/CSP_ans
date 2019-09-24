#include <iostream>

#include <vector>

// 俄罗斯方块

using std::cin;
using std::cout;
using std::endl;

using std::vector;

const int static ROWS = 15;
const int static COLS = 10;
const int static BLOCKSIZE = 4;

void swap(int& i, int& j)
{
	int k = i;
	i = j;
	j = k;
}

int main(int argc, char **argv)
{
	vector<vector<int>> grid(ROWS, vector<int>(COLS, 0));
	for (auto &iter : grid)
		for (int &item : iter)
			cin >> item;

	vector<vector<int>> block(BLOCKSIZE, vector<int>(BLOCKSIZE, 0));
	for (auto &iter : block)
		for (auto &item : iter)
			cin >> item;
	int iniIndex = 0;
	cin >> iniIndex;
	iniIndex--;	// 代表 Y 方向的下标

	for (int i = 0; i < BLOCKSIZE; i++)
		grid.insert(grid.begin(), vector<int>(COLS, 0));

	vector<int> posOf1XDir(4, -1);	// 四个 1 在竖直方向的坐标
	for (int i = 0; i < BLOCKSIZE; i++)
		for (int j = 0; j < BLOCKSIZE; j++)
		{
			grid[i][iniIndex + j] = block[i][j];
			if (block[i][j] == 1)
			{
				if (i > posOf1XDir[j])
					posOf1XDir[j] = i;
			}
		}
	grid.push_back(vector<int>(COLS, 1));	// 用于判断越界
	// 计算最远能到多远
	int maxDistance = 20;
	for (int i = 0; i < BLOCKSIZE; i++)
	{
		if (posOf1XDir[i] != -1)
		{
			int iniRow = posOf1XDir[i] + 1;
			int colDistance = 0;
			while (grid[iniRow++][iniIndex + i] != 1) {}
			if (iniRow - 1 - posOf1XDir[i] < maxDistance)
				maxDistance = iniRow - 1 - posOf1XDir[i];
		}
	}
	for (int i = 0; i < BLOCKSIZE; i++)
		for (int j = 0; j < BLOCKSIZE; j++)
		{
			if (grid[i][iniIndex + j] == 1)
				swap(grid[i][iniIndex + j], grid[i + maxDistance - 1][iniIndex + j]);
		}
	for (int i = BLOCKSIZE; i < 19; i++)
	{
		for (int &item : grid[i])
			cout << item << " ";
		cout << endl;
	}
	return 0;
}