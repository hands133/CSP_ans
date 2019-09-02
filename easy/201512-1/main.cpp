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
    int result = 0;
    while(n != 0)
    {
        result += n % 10;
        n /= 10;
    }
    cout << result << endl;

    //system("pause");
    return 0;
}