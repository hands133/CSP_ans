#include <iostream>

#include <vector>
#include <cstdlib>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

using std::ios;

// Z 扫描

// ！！超时！！
// ！！超时！！
// ！！超时！！
// ！！超时！！
// ！！超时！！
// ！！超时！！


enum dir { RIGHT, DIAGDOWN, DOWN, DIAGUP };
dir direction[4] = { RIGHT, DIAGDOWN, DOWN, DIAGUP };

int lastDir = 0;	// 上一次的方向下标
void inc(int& i) { i = (i + 1) % 4; }
#define INC() { inc(lastDir); }

int N;
vector<vector<int>> matrix;

unsigned seed = time(0);

const bool judge(const int& i, const int& j)
{
	if (i < 0 || i >= N || j < 0 || j >= N)	return false;
	return true;
}

const bool nextStep(const int& i, const int& j, const dir& direction)
{	// 判断在位置 (i, j) 并按照 direction 方向走一步是否合法
	switch (direction)
	{
	case RIGHT:		return judge(i, j + 1);		break;
	case DIAGDOWN:	return judge(i + 1, j - 1);	break;
	case DOWN:		return judge(i + 1, j);		break;
	case DIAGUP:	return judge(i - 1, j + 1);	break;
	}
}

void disp(const int& i) { cout << i << " "; }

const bool gothrough(const vector<vector<int>> &matrix, int &i, int &j)
{
	int count = 0;
	switch (direction[lastDir])
	{
	case RIGHT:
	{
		disp(matrix[i][j]);
		j++;
		do { INC(); count++; } while (!nextStep(i, j, direction[lastDir]) && count < 5);
	}
	break;
	case DIAGDOWN:
	{
		while (nextStep(i, j, DIAGDOWN)) { disp(matrix[i][j]); i++; j--; }
		do { INC(); count++; } while (!nextStep(i, j, direction[lastDir]) && count < 5);
		if (direction[lastDir] == DIAGUP)	lastDir++;
	}
	break;
	case DOWN:
	{
		disp(matrix[i][j]);
		i++;
		do { INC(); count++; } while (!nextStep(i, j, direction[lastDir]) && count < 5);
	}
	break;
	case DIAGUP:
	{
		while (nextStep(i, j, DIAGUP)) { disp(matrix[i][j]); i--; j++; }
		do { INC(); count++; } while (!nextStep(i, j, direction[lastDir]) && count < 5);
		if (direction[lastDir] == DIAGDOWN)	lastDir++;
	}
	break;
	}
	return !(i == N - 1 && j == N - 1);
}

int main(int argc, char **argv)
{
	ios::sync_with_stdio(false);
	srand(seed);
	cin >> N;	// 矩阵大小
	// N = 100;
	if (N == 1)
	{
		int one;
		cin >> one;
		cout << one << endl;
		exit(0);
	}
	matrix.resize(N, vector<int>(N, 0));
	for (auto &iter : matrix)
		for (auto &item : iter)
			cin >> item;
	// item = rand() % 1000;
	int i = 0;
	int j = 0;

	while (gothrough(matrix, i, j)) {}
	cout << matrix[N - 1][N - 1] << endl;
	// system("pause");
	return 0;
}
