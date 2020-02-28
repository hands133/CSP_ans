#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;

//运行错误，得分20

//一个块(block)包含4字节(8个字符)
struct Disk {
	int i;//硬盘的序号
	//int block_num;//硬盘包含的块数目
	//int stripe_num;//硬盘包含的条带数目
	vector<string> block;//每一块的数据

	//Disk(){}
	void initial(int i, string &str)
	{
		this->i = i;
		int nums = str.length() / 8;
		string ablock;
		for (int k = 0; k < nums; k++)
		{
			ablock = str.substr(k * 8, 8);
			block.push_back(ablock);
		}
	}
};

int find(vector<Disk> &d, int seq)
{
	for (int i = 0; i < d.size(); i++)
	{
		if (seq == d[i].i)
			return i;

	}
	return -1;
}
int main()
{
	int n, s, l;//理论硬盘数目、条带大小(块)、现存硬盘数目
	cin >> n >> s >> l;
	n--;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!理论硬盘数目为n+1

	int ti;
	string ta;
	vector<Disk> disk(l);
	for (int i = 0; i < l; i++)
	{
		cin >> ti >> ta;
		disk[i].initial(ti, ta);
	}
	int k = disk[0].block.size() / s;//一个硬盘对应条带数目

	
	int m;
	cin >> m;
	vector<int> seq(m);
	for (int i = 0; i < m; i++)
		cin >> seq[i];
	for (int i = 0; i < m; i++)
	{
		int k = seq[i] / (s * n);//该块对应的条带号
		int check = (n + 1) - k % (n + 1) - 1;//该条带号的校验条带所在的硬盘的号
		int current = (check + 1 + seq[i] % (s * n) / s) % (n + 1);//序号为seq[i]的块所在的硬盘的号
		int seqs = seq[i] % s + k * s;//该块所在的硬盘对应的存储序号
		
		
		int flag = find(disk, current);
		if (flag == -1)//如果不存在，则计算 
		{
			if (l == n)
			{
				long long int yh = stoll(disk[0].block[seqs], 0, 16);
				for (int j = 1; j < disk.size(); j++)
				{
					yh ^= stoll(disk[j].block[seqs], 0, 16);
				}
				cout << setw(8) << setfill('0') << uppercase << hex << yh << endl;
			}
			else
				cout << "-" << endl;
			
		}
		else//如果该盘(current)存在
		{
			cout << disk[flag].block[seqs] << endl;
		}
	}



	return 0;
}
/*
2 1 2
0 000102030405060710111213141516172021222324252627
1 000102030405060710111213141516172021222324252627


3 2 2
0 000102030405060710111213141516172021222324252627
1 A0A1A2A3A4A5A6A7B0B1B2B3B4B5B6B7C0C1C2C3C4C5C6C7



*/
