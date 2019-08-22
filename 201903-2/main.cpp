#include <iostream>

#include <vector>
#include <stack>

using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::stack;

bool isPriority(const char &c1, const char &c2)
{   //判断两个运算符的优先级，第一是否比第二优先
    int p1 = 0;
    int p2 = 1;
    p1 = (c1 == '+' || c1 == '-') ? 1 : 2;
    p2 = (c2 == '+' || c2 == '-') ? 1 : 2;
    return p1 > p2;
}

char *postSeq(const char* buffer)
{
    char *poSeq = new char[7];
    int i = 0;
    for(int i=0;i<7;i++)
    {
        if(buffer[i] >= '0' && buffer[i] <= '9')
            poSeq[i] = buffer[i];
        else
        {   //遇到符号
            
        }
        
    }
}

int build_up(stack<int> &numStack, stack<char> &opStack, char *buffer)
{
    while(!numStack.empty())
        numStack.pop();
    while(!opStack.empty())
        opStack.pop();
    //将中缀表达式转化为后缀表达式
    char *postSeq = transfer(buffer);
    for (int i = 0; i < 7; i++)
    {
        if(buffer[i] <= '9' && buffer[i] >= '0')
            numStack.push(buffer[i] - '0');
        else
        {   //读取到符号，进行判断
            
        }
        
    }
    
}

int main(int argc, char **argv)
{
    //输入由四个数字和三个操作符 + - * / 组成的算式
    // 结果为 24 则输出 Yes，否则输出 No
    // 注意这里除法是整数除法
    int num = 0;
    cin >> num;
    if(num == 0)
        return 0;
    char buffer[7];
    std::stack<int> numStack;    //数字栈
    std::stack<char> opStack;    //符号栈
    std::vector<bool> result;    //结果数组
    vector<bool>::iterator iter = result.begin();
    result.resize(num);
    int number = 0;
    char opCode = '\0';
    while(num > 0)
    {
        for (int i = 0; i < 7; i++)
            cin>>buffer[i];
        (*iter) = (build_up(numStack, opStack, buffer) == 24) ? true : false;
        iter++;
        num--;
    }
    for(bool &n : result)
    {
        if(result)  cout<<"Yes"<<endl;
        else        cout<<"No"<<endl;
    }
    system("pause");
    return 0;
}