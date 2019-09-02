#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

// 神 TM 卖菜

int main(int argc, char **argv)
{
    int numShops = 0;
    cin >> numShops;
    numShops+=2;
    vector<int> prices(numShops,0);
    for(int i=1; i<numShops-1; i++)
        cin >> prices[i];
    prices[0] = (prices[1] + prices[2]) / 2;
    prices[numShops-1] = (prices[numShops-2] + prices[numShops-3]) / 2;
    vector<int> result(numShops - 2,0);
    for(int i=1;i<numShops-1;i++)
        result[i-1] = (prices[i-1] + prices[i] + prices[i+1])/3;
    for(int &n : result)
        cout<<n<<" ";
    cout<<endl;

    //system("pause");

    return 0;
}