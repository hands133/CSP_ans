#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

// 门禁系统
// 涛涛最近要负责图书馆的管理工作，需要记录下每天读者的到访情况。每位读者有一个编号，每条记录用读者的编号来表示。给出读者的来访记录，请问每一条记录中的读者是第几次出现。

int main(int argc, char **argv)
{
    int n;
    cin >> n;
    vector<int> record(n, 0);
    for(int &n : record)    cin >> n;

    vector<int> result(n, 0);
    int iter = 0;
    for(int i = 0; i < n; i++)
    {
        iter = record[i];
        // 向前查找相同的数字，次数为其加一
        for(int j = i - 1; j >= 0; j--)
            if(record[i] == record[j])
            {
                result[i] = result[j] + 1;
                break;
            }
        result[i] = (result[i] == 0) ? 1 : result[i];
    }
    for(int &n : result)
        cout << n << " ";
    cout << endl;
    // system("pause");
    return 0;
}