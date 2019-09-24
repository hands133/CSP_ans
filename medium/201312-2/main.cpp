#include <iostream>

#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::string;

// ISBN

const string rectify(vector<char> &ISBN)
{
    int sum = 0;
    int step = 1;
    string str = "";
    for(int i = 0;i < ISBN.size() - 1;i ++)
    {
        if(ISBN[i]>= '0' && ISBN[i]<= '9')
            sum += (ISBN[i] - '0') * (step++);
        str += ISBN[i];
    }
    if(sum % 11 == ((ISBN.back() == 'X') ? 10 : ISBN.back() - '0'))
        str = "Right";
    else    str += ((sum % 11 == 10) ? 'X' : (sum % 11 + '0'));
    return str;
}

int main(int argc, char **argv)
{
    vector<char> ISBN(13,'\0');
    for(char &c : ISBN) cin >> c;
    cout << rectify(ISBN) << endl;

    // system("pause");
    return 0;
}