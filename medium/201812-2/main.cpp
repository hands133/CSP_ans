#include <iostream>

#include <vector>
#include <tuple>

using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::tuple;

// 小明放学
// 输入的第一行包含空格分隔的三个正整数 r、y、g，表示红绿灯的设置。这三个数均不超过 10^6。
// 输入的第二行包含一个正整数 n，表示小明总共经过的道路段数和路过的红绿灯数目。
// 接下来的 n 行，每行包含空格分隔的两个整数 k、t。k=0 表示经过了一段道路，将会耗时 t 秒，此处 t 不超过 10^6；k=1、2、3 时，分别表示出发时刻，此处的红绿灯状态是红灯、黄灯、绿灯，且倒计时显示牌上显示的数字是 t，此处 t 分别不会超过 r、y、g。

/// 这个题知道了出发时各个灯的状态，需要计算在经过一段时间后灯的状态

int r = 0;  // 红灯时间
int g = 0;  // 绿灯时间
int y = 0;  // 黄灯时间

const std::tuple<int, int> getLight(int status, int iniTime, const unsigned long long int& timeGap)
{   // 返回经过 timeGap 后灯的状态和剩余的时间
	int s = status;
	if (s == 0)	return std::make_tuple(s, iniTime);	// 遇到道路就返回
	int endTime = 0;
	int restTime = timeGap % (r + g + y);

	switch (status)
	{	// 红灯 -- 绿灯 -- 黄灯 -- 红灯
		case 1:	// 红灯
		{
			if (restTime < iniTime)
			{ 	// 仍为红灯
				s = 1; 
				endTime = iniTime - restTime;
			}
			if (restTime >= iniTime && restTime < iniTime + g)	
			{	// 变为绿灯
				s = 3;
				endTime = iniTime + g - restTime;
			}
			if (restTime >= iniTime + g && restTime < iniTime + g + y)
			{	// 变为黄灯
				s = 2;
				endTime = iniTime + g + y - restTime;
			}
			if (restTime >= iniTime + g + y)
			{	// 变为红灯
				s = 1;
				endTime = r + g + y - (restTime - iniTime);
			}
		}
		break;
		case 2: // 黄灯
		{
			if (restTime < iniTime)
			{ 	// 仍为黄灯
				s = 2;
				endTime = iniTime - restTime;
			}
			if (restTime >= iniTime && restTime < iniTime + r)
			{	// 变为红灯
				s = 1;
				endTime = iniTime + r - restTime;
			}
			if (restTime >= iniTime + r && restTime < iniTime + r + g)
			{	// 绿灯
				s = 3;
				endTime = iniTime + r + g - restTime;
			}
			if (restTime >= iniTime + r + g)
			{	// 变为黄灯
				s = 2;
				endTime = r + g + y - (restTime - iniTime);
			}
		}
		break;
		case 3: // 绿灯
		{
			if (restTime < iniTime)
			{ 	// 仍为绿灯
				s = 3;
				endTime = iniTime - restTime;
			}
			if (restTime >= iniTime && restTime < iniTime + y)
			{	// 变为黄灯
				s = 2;
				endTime = iniTime + y - restTime;
			}
			if (restTime >= iniTime + y && restTime < iniTime + y + r)
			{	// 变为红灯
				s = 1;
				endTime = iniTime + y + r - restTime;
			}
			if (restTime >= iniTime + y + r)
			{	// 变为绿灯
				s = 3;
				endTime = r + g + y - (restTime - iniTime);
			}
		}
		break;
	}
	return std::make_tuple(s, endTime);
}

int main(int argc, char **argv)
{
	unsigned long long int currSeconds = 0;
	cin >> r >> y >> g;
	int n = 0;  // 道路数和路口数
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int k = 0;      // 0：道路 1：红灯 2：黄灯 3：绿灯
		int t = 0;      // 道路：行走的秒数  信号灯：剩余秒数
		cin >> k >> t;  // 经过道路的时间不会变化
		std::tuple<int, int> status = getLight(k, t, currSeconds);
		switch (std::get<0>(status))
		{
			case 0:	currSeconds += std::get<1>(status);		break;
			case 1: currSeconds += std::get<1>(status);		break;
			case 2: currSeconds += std::get<1>(status) + r;	break;
			case 3: currSeconds += 0;						break;
		}
	}
	cout << currSeconds << endl;
	// system("pause");
	return 0;
}