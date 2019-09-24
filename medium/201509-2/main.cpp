#include <iostream>

#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

// 日期计算

const bool judgeRun(const int& year)
{
    if(year / 4 == 0 && year / 100 != 0)    return true;
    if(year / 400 == 0) return true;
    return false;
}

int main(int argc, char **argv)
{
    int y;  // 年份
    int d;  // 天数
    cin >> y >> d;
    vector<int> daysPerMonth = 
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(judgeRun(y)) daysPerMonth[1]++;
    int index = 0;
    while(d != 0)
    {
        if(d > daysPerMonth[index])
            d -= daysPerMonth[index++];
        else{ index++; break; }
    }
    cout << index << endl;
    cout << d;
    // system("pause");
    return 0;
}