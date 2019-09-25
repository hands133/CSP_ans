#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// 小明种苹果

int main(int argc, char **argv)
{
	int N;  // 苹果树棵树
	int M;  // 疏果操作
	cin >> N >> M;
	long long int T = 0;
	long long int k = 0;
	long long int P = 0;
	for (int i = 0; i < N; i++)
	{
		int appleOnTree;	// 每棵树上的苹果数
		cin >> appleOnTree;
		int tempDropSum = 0;
		for (int j = 0; j < M; j++)
		{
			int tempDrop;
			cin >> tempDrop;    // 这里是负数
			tempDropSum += tempDrop;
			if (P < -tempDropSum)
			{
				P = -tempDropSum;
				k = i;
			}
		}
		T += appleOnTree + tempDropSum;
	}
	cout << T << " " << k + 1 << " " << P << endl;

	//system("pause");
	return 0;
}