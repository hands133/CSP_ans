#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

// 分蛋糕
// n 块蛋糕重量分别为 a1, a2, ..., an
// 每个朋友至少分到重量为 k 的蛋糕
// 每次给编号最小的蛋糕，不够的话从剩下蛋糕中编号最小的附带上，直到给够了 k

int main(int argc, char **argv)
{
    int n = 0;
    int k = 0;
    cin >> n;
    cin >> k;
    vector<int> cakes(n, 0);
    for(int &n : cakes)    cin >> n;

    vector<int>::iterator iter = cakes.begin();
    int cakePerPeople = 0;
    int peopleCount = 0;
    while(iter != cakes.end())
    {
        cakePerPeople = 0;
        // 每次计算一个人
        while(cakePerPeople < k)
        {
            cakePerPeople += *(iter ++);
            if(iter == cakes.end())
            {
                if(cakePerPeople != 0)
                    peopleCount ++;
                goto res;
            }
        }
        peopleCount ++;
    }
res:
    cout << peopleCount << endl;
    system("pause");
    return 0;
}