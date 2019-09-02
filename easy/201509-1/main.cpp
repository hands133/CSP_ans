#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

int main(int argc, char **argv)
{
    int n;
    cin >> n;
    vector<int> vec(n,0);
    for(int &n : vec)   cin >> n;
    
    int segCount = 1;
    // 快慢指针
    int i = 0, j = 1;
    while(j < n)
    {
        if(vec[i] != vec[j])
        {
            segCount ++;
            i = j;
            j = i + 1;
            if(j == n)
                break;
        }
        while(vec[i] == vec[j]) j++;
    }

    cout << segCount << endl;
    // system("pause");
    return 0;
}