#include <iostream>

#include <vector>
#include <stack>

#include <stdio.h>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::stack;
using std::srand;
using std::rand;

const int cal(const int& l, const int& r, const char& opCode)
{
	switch (opCode)
	{
	case '+':   return l + r;
	case '-':   return l - r;
	case 'x':   return l * r;
	case '/':   return l / r;
	default:   break;
	}
}

const int encode(const char &c)
{
	switch (c)
	{
	case 'x':  return 2;
	case '/':  return 2;
	case '+':  return 1;
	case '-':  return 1;
	default:  return 0;
	}
}

const bool priority(const char& op1, const char& op2)
{
	return encode(op1) >= encode(op2);
}

void getLastOrder(char* buffer)
{
	if (buffer == NULL)  return;
	// stack<int> numStack;    // 数字栈
	stack<char> opStack;    // 符号栈
	char newBuffer[7] = { '\0' };   //新缓冲区
	int index = 0;
	for (int i = 0; i < 7; i++)
	{
		char c = buffer[i];
		if (c >= '0' && c <= '9')    newBuffer[index++] = c;
		else
		{   // 符号
			if (opStack.empty()) opStack.push(c);
			else
			{
				while (opStack.top() == ')' || priority(opStack.top(), c))
				{
					newBuffer[index++] = opStack.top();
					opStack.pop();
					if (opStack.empty())	break;
				}
				opStack.push(c);
			}
		}
	}
	while (!opStack.empty())
	{
		newBuffer[index++] = opStack.top();
		opStack.pop();
	}
	for (int i = 0; i < 7; i++)    buffer[i] = newBuffer[i];
}

const int calResult(char *buffer)
{
	if (buffer == NULL)  return -1;
	stack<int> numStack;
	for (int i = 0; i < 7; i++)
	{
		char c = buffer[i];
		if (c >= '0' && c <= '9')    numStack.push(c - '0');
		else
		{
			int n1 = numStack.top();
			numStack.pop();
			int n2 = numStack.top();
			numStack.pop();
			numStack.push(cal(n2, n1, c));
		}
	}
	return numStack.top();
}


void randomize(char *buffer)
{
    
    char map[4] = { '+' , '-' , 'x' , '/' };
    for(int i = 0; i < 7; i++)
    {
        if(i % 2 == 0)
        {
            if(i != 0 && buffer[i-1] == '/')
                buffer[i] = rand() % 9 + '1';
            else
                buffer[i] = rand() % 10 + '0';
        }
        else buffer[i] = map[rand() % 2];
        cout << buffer[i];
    }
    cout << endl;
}

int main(int argc, char **argv)
{
    srand((unsigned)time(NULL));
	//输入由四个数字和三个操作符 + - * / 组成的算式
	// 结果为 24 则输出 Yes，否则输出 No
	// 注意这里除法是整数除法
	int num = 0;
	cin >> num;
	if (num == 0)
		return 0;
	char buffer[7];
	vector<bool> result(num, false);
	int n1, n2, n3, n4;
	char op1, op2, op3;
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < 7; j++)   cin >> buffer[j];
        // randomize(buffer);
		n1 = buffer[0] - '0';
		n2 = buffer[2] - '0';
		n3 = buffer[4] - '0';
		n4 = buffer[6] - '0';
		op1 = buffer[1];
		op2 = buffer[2];
		op3 = buffer[3];
		getLastOrder(buffer);   //转化为后缀表达式
		result[i] = (calResult(buffer) == 24);
	}
	for (const bool &b : result)
		cout << (b ? "Yes" : "No") << endl;
	// system("pause");
	return 0;
}