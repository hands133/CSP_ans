#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<fstream>
#include<map>
#include<sstream>
//错误，得分40
namespace mine {
	std::fstream cin("f:\\\in.txt");
}
using namespace std;
//using mine::cin;
int getpoint(string& str)
{//从str中获取'.'的个数，同时将'.'从str中删除
	int i = 0;
	while (i < str.length())
	{
		if (str[i] != '.')
			break;
		i++;
	}
	str.erase(0, i);
	return i;
}
void lower(string& str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
	}
}
vector<string> get(string& str)
{//以空格为分隔符将str分割，并以vector<string>类型返回，期间将标签转为小写，而id不动
	int last = -1, index = 0;
	string s;
	vector<string> temp;
	while ((index = str.find(' ', index)) < str.length())
	{
		s = str.substr(last + 1, index - last - 1);
		if (s[0] != '#')
			lower(s);
		temp.push_back(s);
		last = index++;
	}
	s = str.substr(last + 1);
	if (s[0] == '#')
		lower(s);
	temp.push_back(s);
	return temp;
}

struct tree {
	int id = 0;//行数
	vector<string> tit;//标签集合 
	vector<tree*> son;//子代元素集合 
	tree* parent;//父代元素 
	tree() {}
	tree(int i, string& s, map<string, vector<tree*>>& ele) :id(i)
	{
		int last = -1, index = 0;
		string str;
		while ((index = s.find(' ', index)) < s.length())
		{
			str = s.substr(last + 1, index - last - 1);
			last = index++;
			if (str[0] != '#')
				lower(str);
			tit.push_back(str);//自身的标签属性
			ele[str].push_back(this);//相同元素链接起来
		}
		str = s.substr(last + 1);//处理最后一个
		tit.push_back(str);
		ele[str].push_back(this);
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	cin.get();

	string str;
	int num;
	vector<string> query(m);//存放查询语句
	map<int, tree*> last;//存放最近的上级结点(相当于父结点)
	map<string, vector<tree*>> element;//存放相同元素的结点链表

	getline(cin, str);//读取第一行
	tree html(1, str, element);//第一个结点
	last[0] = &html;

	for (int i = 2; i <= n; i++)
	{
		getline(cin, str);
		num = getpoint(str);//获取有几个标签

		tree* node = new tree(i, str, element);

		tree* f = last[num - 2];//查找父结点并关联
		f->son.push_back(node);
		node->parent = f;

		last[num] = node;//修改本级结点


	}
	for (int i = 0; i < m; i++)
		getline(cin, query[i]);

	//mine::cin.close();//关闭文件

	for (int i = 0; i < m; i++)
	{
		string q = query[i];
		vector<string> qs = get(q);
			

		if (qs.size() == 1)//非后代选择器
		{
			string qse = qs[0];
			if (element.count(qse) == 1)//element的value是vector<tree*>属性的元素，所以(*it)是(tree*)属性的元素
			{
				cout << element[qse].size() << " ";
				for (auto it = element[qse].begin(); it != element[qse].end(); it++)
					cout << (*it)->id << " ";
			}
			else
				cout << 0;
			
		}
		else//后代选择器
		{
			string qse = qs[qs.size() - 1];
			if (element.count(qse) == 1)
			{//如果最后一级元素存在
				int number = 0;
				vector<int> nums;
				for (auto it = element[qse].begin(); it != element[qse].end(); it++)
				{//扫描对应链表获取结点
					tree* no = *it;
					if (no == NULL)
						continue;
					int i;
					for (i = qs.size() - 2; i >= 0; i--)
					{//往上匹配父结点元素
						if (no->parent != NULL && no->parent->tit[0] != qs[i])
							break;
						no = no->parent;
					}
					if (i == -1)//如果全部符合，则找到一个
					{
						number++;
						nums.push_back((*it)->id);
					}
				}
				cout << number << " ";
				for (int i = 0; i < nums.size(); i++)
					cout << nums[i] << " ";


			}
			else
				cout << 0;

			

		}
		cout << endl;

	}







	return 0;
}
/*
11 5
html
..head
....title
..body
....h1
....p #subtitle
....div #main
......h2
......p #one
......div
........p #two
p
#subtitle
h3
div p
div div p


15 7
html
..head
....title
..body
....h1
....p #subtitle
....div #main
......h2
......p #one
......diV #maiN
........p #three
........div #Subtitle
..........p #Three
..........div #Main
............p #two
p
#subtitle
h3
Div p
div div p
div div div p
div div div div p
*/
