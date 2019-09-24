#include <iostream>

#include <set>

using std::cin;
using std::cout;
using std::endl;

using std::set;
using std::pair;

// 画图

int main(int argc, char **argv)
{
    int n;  // 矩形个数
    cin >> n;
    set<pair<int,int>> s;
    int x1, x2, x3, x4;
    for(int i = 0;i < n;i++)
    {
        cin >> x1 >> x2 >> x3 >> x4;
        for(int i = x1; i <= x3; i++)
            for(int j = x2; j <= x4; j++)
                s.insert(pair<int,int>(i,j));
    }
    cout << s.size() << endl;

    // system("pause");
    return 0;
}