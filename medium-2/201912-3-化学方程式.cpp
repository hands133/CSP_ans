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

//���ض��ַ��ָ��ַ���
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

//<����> == <����> | <����> <����>
int Digits(string &str, int start)
{//����˺�����������⵽str[start]Ϊ����
	//��str��start��ʼ��ȡһ�����ַ��أ����������ִ�str��ɾ��
	string snum;
	int tstart = start;
	while (isDigit(str[start]))
	{
		snum += str[start];
		start++;
	}
	str.erase(tstart, start - tstart);
	//cout << "��ȡ���� " << snum << ", ʣ���ַ��� " << str << "\n";
	return stoi(snum);
}
//<ϵ��> == <����> | ��
//<Ԫ��> == <��д��ĸ> | <��д��ĸ> <Сд��ĸ>
string element(string& str)
{//����˺�����������⵽str[start]Ϊ��д��ĸ
	//��str��0��ʼ��ȡһ��Ԫ�ط��أ�������Ԫ����str��ɾ��
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
	//cout << "��ȡԪ�� " << ele << ", ʣ���ַ��� " << str << "\n";
	return ele;

}
//<��> == <Ԫ��> | "("<��ѧʽ>")"
void term(string &str, map<string, int>& map, int times = 1)
{//����˺�����������⵽str[start]Ϊ��д��ĸ����str[start]Ϊ������
	//cout << "����(�� + ϵ��) " << str << " ����Ϊ " << times << "\n";
	int start = 0;
	if (str[start] == '(')
	{//������������ţ������Ѱ�Ҷ�Ӧ�������ţ�Ȼ����ȡ���������ݣ�����̽�������ź������
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
					{//��������ź��������֣�����ȡ���֡���ӱ����ٽ������ҷָ�
						int ttimes = Digits(str, i + 1);
						string left = str.substr(start + 1, i - start - 1);
						string right = str.substr(i + 1);
						term(left, map, ttimes * times);
						term(right,map, times);
					}
					else
					{//��������ź���û�����֣���ֱ�ӽ������ҷָ�
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
	{//���������д��ĸ���ͽ���Ԫ��ת����֮��̽��Ԫ��֮�������
		string ele = element(str);
		if (isDigit(str[start]))
		{//���Ԫ�غ������֣�����ȡ���֡����㱶���󽫶�ӦԪ�������map���ٴ���ʣ�����
			int ttimes = Digits(str, start);
			map[ele] += ttimes * times;
			//cout << "Ԫ�� " << ele << "�������Ϊ " << ttimes << "\n";
			//cout << "���key-value�� " << ele << "----" << ttimes * times << "\n";
			term(str, map, times);
		}
		else
		{//���Ԫ�غ�û�����֣����Լ̳������ı�������ӦԪ�������map���ٴ���ʣ�����
			map[ele] += times;
			//cout << "���key-value�� " << ele << "--" << times << "\n";
			term(str, map, times);
		}

		

	}


}
//<��ѧʽ> == <��> <ϵ��> |<��ѧʽ> <��> <ϵ��>
void formula(string &str, map<string, int> &map)
{
	if (isDigit(str[0]))
	{//������ȡ��ѧʽǰ������
		int times = Digits(str, 0);
		term(str, map, times);
	}
	else//��ѧʽǰû������
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
		{//����Ⱥ���ߵĸ�Ԫ������
			formula(arr1[i], le);
		}
		for (int i = 0; i < arr2.size(); i++)
		{//����Ⱥ��ұߵĸ�Ԫ������
			formula(arr2[i], re);
		}
		map<string, int>::iterator it;
		bool flag = true;
		for (it = le.begin(); it != le.end(); it++)
		{//����Ϊ��׼���ҽ���ƥ��
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
		if (flag && re.size() == 0)//ƥ����ȷ�����ұ�û��ʣ��Ԫ��
			cout << "Y" << endl;
		else
			cout << "N" << endl;
	}
	
	return 0;
}
