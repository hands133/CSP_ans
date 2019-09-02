#include <iostream>

#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

// 中间数
// 在一个整数序列a1, a2, ..., an中，如果存在某个数，大于它的整数数量等于小于它的整数数量，则称其为中间数。在一个序列中，可能存在多个下标不相同的中间数，这些中间数的值是相同的。
// 给定一个整数序列，请找出这个整数序列的中间数的值。

struct chainNode
{
    chainNode() : numLess(0), numGreater(0), element(-1), next(NULL) {}
    int numLess;    // 小于当前值的元素个数
    int numGreater; // 大于当前值的元素个数
    int element;    // 元素
    chainNode *next;// 下一个结点指针
};

int main(int argc, char **argv)
{
    int n = 0;
    cin >> n;
    
    vector<int> vec(n, 0);
    for(auto &n : vec)    cin >> n;

    int midValue = -1;
    if(n == 1)  midValue = vec[0];
    else if(n == 2)  midValue = ((vec[0] == vec[1]) ? vec[0] : -1);
    else
    {
        for(int j = 0; j < n; j++){
            int mcount = 0, lcount = 0;
            for(int k = 0; k < n; k++){
                if(vec[j] < vec[k]) mcount++;
                if(vec[j] > vec[k]) lcount++;
            }
            if(mcount == lcount) midValue = vec[j];
        }
    }
    cout<< midValue << endl;
    
    system("pause");
    return 0;
}