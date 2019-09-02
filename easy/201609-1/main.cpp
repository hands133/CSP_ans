#include <iostream>

#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

// 最大波动
// 这只股票连续几天的最大波动值是多少，即在这几天中某天收盘价格与前一天收盘价格之差的绝对值最大是多少。

const int absDiff(const int& a, const int& b)
{
    return (a >= b) ? a - b : b - a;
}

int main(int argc, char **argv)
{
    int n = 0;
    cin >> n;
    vector<int> vec(n, 0);
    int maxValue = 0;
    for(int i = 0;i < n; i++)
    {
        cin >> vec[i];
        if(i > 0)
        {
            maxValue = (absDiff(vec[i], vec[i-1]) > maxValue) ? absDiff(vec[i], vec[i-1]) : maxValue;
        }
    }

    cout << maxValue << endl;
    // system("pause");
    return 0;
}