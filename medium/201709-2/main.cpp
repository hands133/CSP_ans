#include <iostream>

#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::priority_queue;

using std::operator>;

// 公共钥匙盒

vector<int> box;

struct request
{
    int No;         // 申请教室编号
    int startTime;  // 开始时间
    int deltaT;     // 持续时间
};

int main(int argc, char **argv)
{
    int N;  // 钥匙数量
    int K;  // 上课老师数
    cin >> N >> K;
    // 盒子容器，从 1 开始编号
    vector<int> container(N, 0);
    for(int i = 0; i <  N; i++)    container[i] = i + 1;
    // 空出来的位置（下标）
    std::priority_queue<int,vector<int>,std::less<int>> occupiedNo;
    box.resize(N);
    for(int i =0;i<K;i++)
    {
        int w,s,c;
        cin >> w >> s >> c;
        
    }


    system("pause");
    return 0;
}