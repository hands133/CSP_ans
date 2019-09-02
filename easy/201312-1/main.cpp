#include <iostream>

#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

vector<int> counts(10000,0);

int main(int argc, char *argv[])
{
    int N = 0;
    cin >> N;   // 数字个数
    int number = 0;
    if(N == 1)
    {
        cin >> number;
        cout<< number<<endl;
        return 0;
    }    
    vector<int> nums;
    nums.resize(N);

    int maxTimes = 0;
    int maxIndex = -1;
    for(int i=0;i<N;i++)
    {
        cin >> number;
        counts[number-1] ++;
    }
    for(int i=0;i<10000;i++)
        if(maxTimes < counts[number-1])
        {
            maxTimes = counts[number-1];
            maxIndex = number - 1;
        }
    cout<<maxIndex + 1<<endl;
    //system("pause");
    return 0;
}