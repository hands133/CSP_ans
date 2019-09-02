#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

// 折点计数
// 给定n个整数表示一个商店连续n天的销售量。如果某天之前销售量在增长，而后一天销售量减少，则称这一天为折点，反过来如果之前销售量减少而后一天销售量增长，也称这一天为折点。其他的天都不是折点。如下图中，第3天和第6天是折点。
// 给定n个整数a1, a2, …, an表示销售量，请计算出这些天总共有多少个折点。
// 为了减少歧义，我们给定的数据保证：在这n天中相邻两天的销售量总是不同的，即ai-1≠ai。注意，如果两天不相邻，销售量可能相同。
// 只有一天或者两天的数据应该不是折点
int main(int argc, char **argv)
{
    int n;
    cin >> n;

    vector<int> price(n, 0);
    bool increasing = true;
    int points = 0;
    if(n < 3)   goto res;
    for(auto &n : price)    cin >> n;
    
    for(int i = 1; i < n - 1; i++)
    {
        if((price[i] - price[i-1]) * (price[i+1] - price[i]) < 0)   points++;
    }

res:
    cout << points << endl;
    system("pause");
    return 0;
}