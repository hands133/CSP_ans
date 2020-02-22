#include <iostream>
#include <vector>
#include <iomanip>  //限制小数位数
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
	int N = 0;
	vector<int> container;
	cin >> N;   //输入数组的长度
	if (N <= 0)
	{
		cout << 0 << " " << 0 << " " << 0;
		return 0;
	}
	container.resize(N);
	for (int &n : container)
		cin >> n;
	std::sort(container.begin(), container.end());
	//输出最大值、中位数和最小值
	int max = 0;
	int min = 0;
	if (container[0] < container.back())
	{
		min = container[0];
		max = container.back();
	}
	else
	{
		min = container.back();
		max = container[0];
	}
	cout << max << " ";
	if (N % 2 == 1)
		cout << container[N / 2] << " ";
	else
	{
		int mid = container[N / 2 - 1] + container[N / 2];
		if (mid % 2 == 0)
			cout << mid / 2 << " ";
		else
			cout << setiosflags(ios::fixed)
			<< setiosflags(ios::right)
			<< setprecision(1)
			<< mid / 2.0f << " ";
	}
	cout << min << " " << endl;
	return 0;
}