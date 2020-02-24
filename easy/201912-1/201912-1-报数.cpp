#include<iostream>
using namespace std;

//判断数字中是否包含7 
bool contain(int data)
{
	string sk = to_string(data);
	for (int i = 0; i < sk.size(); i++)
	{
		if (sk[i] == '7')
		    return true;
	}
	return false;
}

int main()
{
	int k;
	cin >> k;
	int per[5] = {0, 0, 0, 0};
	
	int nums = 1;
	for (int i = 0; i < k; i++)
	{
		//如果该计数值是7的倍数或者包含数字7 
		if ( nums % 7 == 0 || contain(nums))
		{
			per[nums % 4]++;
			i--;
		}
		nums++;
	}
	
	cout << per[1] << endl;
	cout << per[2] << endl;
	cout << per[3] << endl;
	cout << per[0] << endl;
	
	
	
	return 0;
}
