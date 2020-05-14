#include<iostream>
#include<map>
#include<vector>
using namespace std;
struct position {
	
	int x = 0, y = 0;
	position(){}
	position(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

int main()
{
	int m;
	cin >> m;
	vector<position> n(m);
	for (int i = 0; i < m; i++)
	{
		cin >> n[i].x;
		cin >> n[i].y;
	}
	
	/*
	思路：将点的横纵坐标相加作为key值，将点组织为一个结构，然后以vector组织在同一个key下。
	 
	*/
	map<int, vector<position>> data;
	vector<position> temp;
	position tp;
	int num;
	vector<int> select(5, 0);
	
	
	for (int i = 0; i < m; i++)
	{
		num = n[i].x + n[i].y;
		if (data.count(num) == 0)
		{
			temp.push_back(n[i]);
			data[num] = temp;
			temp.clear();
		}
		else
		{
			data[num].push_back(n[i]);
		}
	}

	for (int i = 0; i < m; i++)
	{
		int num1 = n[i].x + n[i].y + 1;
		int num2 = n[i].x + n[i].y - 1;
		if (data.count(num1) == 0 || data.count(num2) == 0)
			continue;


		int total1 = data[num1].size();
		int total2 = data[num2].size();

		
		int essential = 0;
		int grade = 0;

		for (int j = 0; j < total1; j++)
		{
			tp = data[num1][j];
			if (tp.x == n[i].x && tp.y == (n[i].y + 1))
				essential++;
			if (tp.y == n[i].y && tp.x == (n[i].x + 1))
				essential++;
		}
		for (int j = 0; j < total2; j++)
		{
			tp = data[num2][j];
			if (tp.x == n[i].x && tp.y == (n[i].y - 1))
				essential++;
			if (tp.y == n[i].y && tp.x == (n[i].x - 1))
				essential++;
		}

		if (essential != 4)
			continue;




		num1 = n[i].x + n[i].y + 2;
		num2 = n[i].x + n[i].y - 2;
		num = n[i].x + n[i].y;
		total1 = data[num1].size();
		total2 = data[num2].size();
		int total = data[num].size();

		for (int j = 0; j < total1; j++)
		{
			tp = data[num1][j];
			if (tp.x == (n[i].x + 1) && tp.y == (n[i].y + 1))
			{
				grade++;
				break;
			}
		}
		for (int j = 0; j < total2; j++)
		{
			tp = data[num2][j];
			if (tp.x == (n[i].x - 1) && tp.y == (n[i].y - 1))
			{
				grade++;
				break;
			}
		}

		for (int j = 0; j < total; j++)
		{
			tp = data[num][j];
			if (tp.x == (n[i].x + 1) && tp.y == (n[i].y - 1))
				grade++;
			if (tp.x == (n[i].x - 1) && tp.y == (n[i].y + 1))
				grade++;
		}

		select[grade]++;

	}

	for (int i = 0; i < 5; i++)
	{
		cout << select[i] << "\n";
	}



	return 0;
}

