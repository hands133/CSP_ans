//小明上学
// 输入：红灯 x 秒 黄灯 y 秒 绿灯 g 秒
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char ** argv)
{
    int timeR, timeY, timeG;
    cin >> timeR >> timeY >> timeG; //红灯、黄灯和绿灯
    int numLights;
    cin>>numLights;
    // 第一个数字表示遇到的红绿等灯的种类
    // 0: 经过一段路，耗时 t 秒
    // 1: 红灯  2: 黄灯  3: 绿灯
    // 第二个数字表示看到的要等待的时间
    int k,t;
    int timeInNeed = 0; //总时间
    while(numLights > 0)
    {   //灯的顺序：红灯->绿灯->黄灯
        cin >> k;
        cin >> t;
        switch(k)
        {
            case 0: //经过空路
                timeInNeed += t;
            break;
            case 1: //等红灯
                timeInNeed += t;
            break;
            case 2: //等黄灯
                timeInNeed += (t + timeR);
            break;
            case 3: //绿灯直接通行
            break;
        }
        numLights --;
    }
    cout<<timeInNeed<<endl;
    system("pause");    //这一行 TMD 就少不了
    return 0;
}