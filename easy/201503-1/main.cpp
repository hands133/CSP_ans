#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

int main(int argc, char **argv)
{
    int m,n;
    cin >> m >> n;
    vector<vector<int>> matrix(n, vector<int>(m, 0));
    for(int i = 0; i < m; i++)
        for(int j = 0;j < n; j++)
            cin >> matrix[n - j - 1][i];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
    // system("pause");
    return 0;
}