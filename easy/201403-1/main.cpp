#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

int main(int argc, char *argv[])
{
    int N = 0;  //元素非 0 且各不相同,不知道有什么文章可做
    cin >> N;   //数字的绝对值不超过 1000
    if(N <= 1)
    {
        cout<<0<<endl;
        return 0;
    }
    vector<int> container(N,0);
    for(int &n : container)
        cin >> n;
    int count = 0;
    for(int i=0;i<N-1;i++)
        for(int j=i+1;j<N;j++)
            if(container[i] + container[j] == 0)
                count ++;
    cout<<count<<endl;

    system("pause");
    return 0;
}