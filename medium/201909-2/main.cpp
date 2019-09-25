#include <iostream>

#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

// 小明种苹果（续）

int main(int argc, char **argv)
{
	int N;
	cin >> N;
	vector<int> apples(N, 0);	// 苹果树颗数
	vector<bool> dropped(N, false);
	long long int T = 0;
	int D = 0;
	int E = 0;
	for (int i = 0; i < N; i++)
	{
		int mi = 0;
		cin >> mi;
		cin >> apples[i];
		for (int j = 0; j < mi - 1; j++)
		{
			int item;
			cin >> item;
			if (item > 0)
			{
				if (item != apples[i])
				{
					apples[i] = item;
					dropped[i] = true;
				}
			}
			else apples[i] += item;
		}
        T += apples[i];
	}
	for(const auto &e : dropped)
        if(e)   ++D;
	if(N >= 3){
		if(dropped[N-1] && dropped[0] && dropped[1])
            ++E;
		if(dropped[N-2] && dropped[N-1] && dropped[0])
            ++E;
	}
	for(int i = 0 ; i < N-2 ; ++i)
		if(dropped[i] && dropped[i+1] && dropped[i+2])
            ++E;
	cout << T << ' ' << D << ' ' << E << endl;
	return 0;
}