#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<stack>
using namespace std;
bool isLower(char k)
{
	if (k >= 'a' && k <= 'z')
		return true;
	return false;
}
bool isUpper(char k)
{
	if (k >= 'A' && k <= 'Z')
		return true;
	return false;
}
bool isDigit(char k)
{
	if (k >= '0' && k <= '9')
		return true;
	return false;
}

//以特定字符分割字符串
vector<string> split(string &str, char s)
{
	vector<string> temp;
	int size = str.length();
	int last = 0;



	for (int i = 0; i < size; i++)
	{
		if (str[i] == s)
		{
			temp.push_back(str.substr(last, i - last));
			last = i + 1;
		}

	}
	temp.push_back(str.substr(last));
	return temp;
}

//<整数> == <数字> | <整数> <数字>
int Digits(string &str, int start)
{//进入此函数条件，检测到str[start]为数字
	//从str从start开始获取一个数字返回，并将该数字从str中删除
	string snum;
	int tstart = start;
	while (isDigit(str[start]))
	{
		snum += str[start];
		start++;
	}
	str.erase(tstart, start - tstart);
	//cout << "获取数字 " << snum << ", 剩余字符串 " << str << "\n";
	return stoi(snum);
}
//<系数> == <整数> | 空
//<元素> == <大写字母> | <大写字母> <小写字母>
string element(string& str)
{//进入此函数条件，检测到str[start]为大写字母
	//从str从0开始获取一个元素返回，并将该元素在str中删除
	int start = 0;
	string ele;
	if (isUpper(str[start]))
	{
		ele += str[start++];
		while (isLower(str[start]))
		{
			ele += str[start++];
		}
	}
	str.erase(0, start);
	//cout << "获取元素 " << ele << ", 剩余字符串 " << str << "\n";
	return ele;

}
//<项> == <元素> | "("<化学式>")"
void term(string &str, map<string, int>& map, int times = 1)
{//进入此函数条件，检测到str[start]为大写字母或者str[start]为左括号
	//cout << "处理(项 + 系数) " << str << " 倍数为 " << times << "\n";
	int start = 0;
	if (str[start] == '(')
	{//如果遇到左括号，则向后寻找对应的右括号，然后提取括号内内容，并且探测右括号后的数字
		stack<int> leftbracket;
		leftbracket.push(start);
		for (int i = start + 1; i < str.length(); i++)
		{
			if (str[i] == '(')
				leftbracket.push(i);
			else if (str[i] == ')')
			{
				if (leftbracket.size() > 1)
					leftbracket.pop();
				else if (leftbracket.size() == 1)
				{

					if (isDigit(str[i + 1]))
					{//如果右括号后面有数字，则提取数字、添加倍数再进行左右分割
						int ttimes = Digits(str, i + 1);
						string left = str.substr(start + 1, i - start - 1);
						string right = str.substr(i + 1);
						term(left, map, ttimes * times);
						term(right,map, times);
					}
					else
					{//如果右括号后面没有数字，则直接进行左右分割
						string left = str.substr(start + 1, i - start - 1);
						string right = str.substr(i + 1);
						term(left, map, times);
						term(right, map, times);
					}
						
				}
					
			}
		}
	}
	else if (isUpper(str[start]))
	{//如果遇到大写字母，就进行元素转换，之后探测元素之后的数字
		string ele = element(str);
		if (isDigit(str[start]))
		{//如果元素后有数字，则提取数字、计算倍数后将对应元素添加至map；再处理剩余的项
			int ttimes = Digits(str, start);
			map[ele] += ttimes * times;
			//cout << "元素 " << ele << "后的数字为 " << ttimes << "\n";
			//cout << "添加key-value对 " << ele << "----" << ttimes * times << "\n";
			term(str, map, times);
		}
		else
		{//如果元素后没有数字，则以继承下来的倍数将对应元素添加至map；再处理剩余的项
			map[ele] += times;
			//cout << "添加key-value对 " << ele << "--" << times << "\n";
			term(str, map, times);
		}

		

	}


}
//<化学式> == <项> <系数> |<化学式> <项> <系数>
void formula(string &str, map<string, int> &map)
{
	if (isDigit(str[0]))
	{//尝试提取化学式前的数字
		int times = Digits(str, 0);
		term(str, map, times);
	}
	else//化学式前没有数字
		term(str, map);
}


int main()
{
	int n = 1;
	cin >> n;

	/*vector<string> total = {
		"H2+O2=H2O",
		"2H2+O2=2H2O",
		"H2+Cl2=2H+2Cl+O2",
	    "CaO+H2O+O2=Ca(OH)2",
	    "Cu+As=Cs+Au",
	    "3Ba(OH)2+2H3PO4=6H2O+Ba3(PO4)2"
	};*/
		
		
	
	for (int k = 0; k < n; k++)
	{
		string total;
		cin >> total;
		//total = "4Au+8NaCN+2H2O+O2=4Na(Au(CN)2)+4NaOH";
		string left = total.substr(0, total.find('=')), right = total.substr(total.find("=") + 1);
		vector<string> arr1 = split(left, '+'), arr2 = split(right, '+');
		map<string, int> le, re;

		
		for (int i = 0; i < arr1.size(); i++)
		{//计算等号左边的各元素数量
			formula(arr1[i], le);
		}
		for (int i = 0; i < arr2.size(); i++)
		{//计算等号右边的各元素数量
			formula(arr2[i], re);
		}
		map<string, int>::iterator it;
		bool flag = true;
		for (it = le.begin(); it != le.end(); it++)
		{//以左为基准对右进行匹配
			//cout << it->first << "    " << it->second << endl;
			if (re[it->first] == it->second)
			{
				re.erase(it->first);
				continue;

			}
			else
			{
				flag = false;
			}
		}
		if (flag && re.size() == 0)//匹配正确并且右边没有剩余元素
			cout << "Y" << endl;
		else
			cout << "N" << endl;
	}
	
	return 0;
}
