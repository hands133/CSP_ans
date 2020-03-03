#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<fstream>
#include<cmath>
namespace mine {
	std::fstream cin("f:\\\in.txt");
}
using namespace std;
//using mine::cin;
//错误，得分80
vector<int> getpoint(string& str)
{//从str中找寻'.'出现的所有位置并返回
	vector<int> point;
	int index = 0;
	while ((index = str.find('.', index)) < str.length())
	{
		point.push_back(index);
		index++;
	}
	return point;

}
struct IP {
	string strip = "";//标准ip的字符串存储
	unsigned int numip = 0;//标准ip的无符号存储
	int len = 0;//前缀长度
	IP() {}
	IP(string ip, int l) :strip(ip), len(l)
	{
		numip = 0;
		int index = 0, last = -1, power = 24;
		while ((index = ip.find('.', index)) < ip.length())
		{
			numip += stoi(ip.substr(last + 1, index - last - 1)) * pow(2, power);
			power -= 8;
			last = index;
			index++;
		}
	}
	void ini(string ip, int l) 
	{
		numip = 0;
		strip = ip;
		len = l;
		int index = 0, last = -1, power = 24;
		while ((index = ip.find('.', index)) < ip.length())
		{
			numip += stoi(ip.substr(last + 1, index - last - 1)) * pow(2, power);
			power -= 8;
			last = index;
			index++;
		}
	}

	bool operator < (const IP& a) const
	{
		if (numip == a.numip)
			return len < a.len;
		return numip < a.numip;
	}
};


int main()
{


	int n;
	cin >> n;
	cin.get();//清除缓存中残留的结束符，不然影响下面的getline函数
	set<IP> ipref_set;
	for (int i = 0; i < n; i++)
	{
		string str;
		getline(cin, str);
		int p = str.find('/');
		IP ipref;
		if (p == -1)
		{//省略长度型
			vector<int> point = getpoint(str);
			string ip;
			int len;
			if (point.size() == 0)
			{
				ip = str + ".0.0.0";
				ipref.ini(ip, 8);
				
			}
			else if (point.size() == 1)
			{
				ip = str + ".0.0";
				ipref.ini(ip, 16);

			}
			else if (point.size() == 2)
			{
				ip = str + ".0";
				ipref.ini(ip, 24);

			}
			else if (point.size() == 3)
			{
				ip = str;
				ipref.ini(ip, 32);
			}
		}
		else
		{
			vector<int> point = getpoint(str);
			string ip;
			int len = stoi(str.substr(p + 1));
			str.erase(p);
			if (point.size() == 0)
			{//省略后缀型
				ip = str + ".0.0.0";
				ipref.ini(ip, len);

			}
			else if (point.size() == 1)
			{//省略后缀型
				ip = str + ".0.0";
				ipref.ini(ip, len);

			}
			else if (point.size() == 2)
			{//省略后缀型
				ip = str + ".0";
				ipref.ini(ip, len);

			}
			else if (point.size() == 3)
			{//标准型
				ip = str;
				ipref.ini(ip, len);
			}


		}

		ipref_set.insert(ipref);//插入set集中
	}

	//cin.close();//使用文件输入时的语句

	for (auto it = ipref_set.begin(); it != prev(ipref_set.end());)
	{
		IP cur = *(it++), nex = *(it--);
		if (cur.len > nex.len)
		{//前者的前缀长度大于后者的，判断是否可从小到大合并
			unsigned int curn = cur.numip >> (32 - nex.len);
			unsigned int nexn = nex.numip >> (32 - nex.len);
			if (curn == nexn)
			{//可删除前者
				it = ipref_set.erase(it);
			}
			else
				it++;
		}
		else if (cur.len < nex.len)
		{//后者的前缀长度大于前者的，判断是否可从小到大合并
			unsigned int curn = cur.numip >> (32 - cur.len);
			unsigned int nexn = nex.numip >> (32 - cur.len);
			if (curn == nexn)
			{//可删除后者
				it = ipref_set.erase(++it);
				it--;
			}
			else
				it++;
		}
		else
		{//前缀长度相等，判断是否可同级合并
			unsigned int curn = cur.numip >> (32 - cur.len);
			unsigned int nexn = nex.numip >> (32 - nex.len);
			if (curn == (nexn - 1))
			{//可同级合并
				it = ipref_set.erase(++it);//先删除后者
				it--;//指向前者
				ipref_set.insert(IP(it->strip, it->len - 1));//根据it指向构造IP插入
				ipref_set.erase(it--);//删除前者，并将it指向新插入的元素
				//(it->len)--;//这里之前我居然想直接修改，set里的元素配置好了显然是不能改的
				          //否则就破坏其组织结构了

				if (it != ipref_set.begin())
					it--;
			}
			else
				it++;
		}


	}


	for (auto it = ipref_set.begin(); it != ipref_set.end(); it++)
		cout << it->strip << "/" << it->len << endl;


	//cout << "check point\n";



	return 0;
}
