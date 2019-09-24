#include <iostream>

#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

// 三消游戏

int n;  // 行数
int m;  // 列数

enum dir { ROW, COL };

void cal(const vector<vector<int>> &board, vector<vector<int>> &copyBoard, const dir& direction)
{
	int left, right, top, bottom;
	switch (direction)
	{
		case ROW:
		{
			left = 0;
			right = (m - 2 < 0) ? 0 : m - 2;
			top = 0;
			bottom = n;
		}
		break;
		case COL:
		{
			left = 0;
			right = m;
			top = 0;
			bottom = (n - 2 < 0) ? 0 : n - 2;
		}
	}
	int deltaX = 0;
	int deltaY = 0;
	for(int i = top; i < bottom; i++)
		for (int j = left; j < right; j++)
		{
			int type = board[i][j];
			switch (direction)
			{
			case ROW:	deltaY = 1;	break;
			case COL:	deltaX = 1;	break;
			}
			if (board[i + deltaX][j + deltaY] == type &&
				board[i + deltaX * 2][j + deltaY * 2] == type)
			{
				copyBoard[i][j] = 0;
				copyBoard[i + deltaX][j + deltaY] = 0;
				copyBoard[i + deltaX * 2][j + deltaY * 2] = 0;
			}
		}
}

int main(int argc, char **argv)
{
	cin >> n >> m;
	vector<vector<int>> board(n, vector<int>(m, 0));
	vector<vector<int>> copyBoard(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			cin >> board[i][j];
			copyBoard[i][j] = board[i][j];
		}
	cal(board, copyBoard, ROW);
	cal(board, copyBoard, COL);
	for (auto &iter : copyBoard)
	{
		for (auto &item : iter)
			cout << item << " ";
		cout << endl;
	}

	// system("pause");
	return 0;
}