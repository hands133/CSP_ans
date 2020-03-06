#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<sstream>
#include<stack>
using namespace std;
struct Json {
	map<string, string> m1;
	map<string, Json*> m2;
};

Json* get(string& str, int& index)
{//str[0] = '{'
	Json* a = new Json();
	index++;
	int key = 1, finish = 0, start = 0, end = 0;
	string keys, values;
	int len = str.length();
	while (index < len)
	{
		switch (str[index])
		{
		case ' ':
		{
			++index;
			break;
		}
		case '"':
		{
			if (key && !finish)//刚开始读取key
			{
				start = ++index;
				finish = 1;
			}
			else if (key && finish)//读取key结束
			{
				end = index - 1;
				++index;
				finish = 0;
				//key = 0;
				keys = str.substr(start, end - start + 1);
			}
			else if (!key && !finish)//刚开始读取string型的value
			{
				start = ++index;
				finish = 1;
			}
			else if (!key && finish)//读取string型的value结束
			{
				end = index - 1;
				++index;
				finish = 0;
				//key = 1;
				values = str.substr(start, end - start + 1);
				a->m1[keys] = values;
			}
			break;
		}
		case ':':
		{
			key = (key + 1) % 2;
			++index;
			break;
		}
		case ',':
		{
			key = 1;
			finish = 0;
			++index;
			break;
		}
		case '\\':
		{
			str.erase(index, 1);
			++index;
			--len;
			break;
		}
		case '{'://开始嵌套 
		{
			Json* b = get(str, index);
			a->m2[keys] = b;
			break;
		}
		case '}'://该对象的处理结束，返回 
		{
			++index;
			return a;
		}
		default:
		{
			++index;
		}
		}
	}

	return a;//这里应该到不了这一句的吧 
}
int main()
{
	int n, m;
	cin >> n >> m;
	cin.get();

	string file;
	for (int i = 0; i < n; i++)
	{
		string str;
		getline(cin, str);
		file += str;
	}
	vector<string> query(m);
	for (int i = 0; i < m; i++)
	{
		cin >> query[i];
	}


	int index = 0;
	Json* a = get(file, index);

	
	for (int i = 0; i < m; i++)
	{
		string str = query[i];
		if (str.find('.') == -1)
		{
			if (a->m1.count(str) == 1)
				cout << "STRING " << a->m1[str] << endl;
			else if (a->m2.count(str) == 1)
				cout << "OBJECT" << endl;
			else
				cout << "NOTEXIST" << endl;
		}
		else
		{
			vector<string> ceng;
			int last = 0, index = 0;
			while ((index = str.find('.', index)) < str.length())
			{
				ceng.push_back(str.substr(last, index - last));
				++index;
				last = index;
			}
			ceng.push_back(str.substr(last));
			int size = ceng.size();
			Json* t = a;
			bool find = true;
			for (int k = 0; k < size - 1; k++)
			{
				if (t->m2.count(ceng[k]) == 1)
					t = t->m2[ceng[k]];
				else
					find = false;

			}
			if (!find)
			{
				cout << "NOTEXIST" << endl;
				continue;
			}
			if (t->m1.count(ceng[size - 1]) == 1)
				cout << "STRING " << t->m1[ceng[size - 1]] << endl;
			else if (t->m2.count(ceng[size - 1]) == 1)
				cout << "OBJECT" << endl;
			else
				cout << "NOTEXIST" << endl;
		}


		
	}



	return 0;
}
/*
10 5
{
"firstName": "John",
"lastName": "Smith",
"address": {
"streetAddress": "2ndStreet",
"city": "NewYork",
"state": "NY"
},
"esc\\aped": "\"hello\""
}
firstName
address
address.city
address.postal
esc\aped



35 6
{
"firstName": "John",
"lastName": "Smith",
"education": {
"junior" : {
"one": "seven",
"two": "three",
"three":"one",
"time":{
"start": "2017",
"end": "2020"
}
},
"senior" :{
"one": "seven",
"time":{
"start": "2017",
"end": "2020"
}
},
"university":{
"one": "seven",
"time":{
"start": "2017",
"end": "2020"
}
},
},
"address": {
"streetAddress": "2ndStreet",
"city": "NewYork",
"state": "NY"
},
"esc\\aped": "\"hello\""
}
firstName
address
education.junior
education.junior.time
address.postal
esc\aped
*/
