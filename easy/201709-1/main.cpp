#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// 打酱油
// N 元钱买酱油，10 元一瓶，满三瓶送一瓶，满五瓶送两瓶，问最多可换多少酱油

int main(int argc, char **argv)
{
    int N = 0;
    cin >> N;   // 钱
    // 三瓶送一瓶，平均一瓶 30 / 4 = 7.5 元
    // 五瓶送两瓶，平均一瓶 50 / 7 approx 7.142857...
    int max = 0;        //  最多酱油数
    int count = 0;      //  计数
    if(N < 50)
        max = N / 10 + ((N >= 30) ? 1 : 0);
    else
    {
        while(N > 50)
        {
            max += 7;
            N -= 50;
        }
        max += N / 10 + ((N >= 30) ? 1 : 0);
        if(N == 50) max++;
    }
    cout << max << endl;
    // system("pause");
    return 0;
}