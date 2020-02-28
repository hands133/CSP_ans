#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<string>
#include<sstream>
using namespace std;


//运行超时，得分20
typedef struct Poisiton {
	int m = 0, n = 0;
	Poisiton() {}
	Poisiton(int m, int n) :m(m), n(n) {}

}Poisition;
struct Commodity {
	int type = 0;
	int id = 0;
	int score = 0;
	Commodity() {}
	Commodity(int t, int i, int s = 0) :type(t), id(i), score(s) {}
	bool equals(const Commodity& com) const
	{
		return (type == com.type && id == com.id);
	}
	bool operator< (const Commodity& c2) const
	{
		if (type != c2.type)
			return type < c2.type;
		else
			return id < c2.id;
	}
};
void shanchu(map<int, set<Commodity>, greater<int>>& tmap, int type)
{//从商品的分数序列中删除某一类商品
	for (auto tmap_it = tmap.begin(); tmap_it != tmap.end(); tmap_it++)
	{
		auto& score_list = (*tmap_it).second;
		for (auto score_it = (*tmap_it).second.begin(); score_it != score_list.end();)
		{
			auto& tcom = (*score_it);
			if (tcom.type == type)
				score_it = score_list.erase(score_it);
			else
				score_it++;
		}
	}
}
int main() {
	int m, n;
	cin >> m >> n;

	map<Commodity, int> amap;//商品序号到分数的映射
	map<int, set<Commodity>, greater<int>> map;//所有商品按分数排列的存储

	
	for (int i = 0; i < n; i++)
	{//读取商品的数据
		int id, sco;
		cin >> id >> sco;
		
		for (int j = 0; j < m; j++)
		{
			Commodity tcom(j, id, sco);
			map[sco].insert(tcom);
			amap.insert(pair<Commodity, int>(tcom, sco));
			
		}
	}



	int op_num;
	cin >> op_num;
	cin.get();
	vector<string> oper(op_num);
	for (int s = 0; s < op_num; s++)
	{
		getline(cin, oper[s]);
	}
	for (int s = 0; s < op_num; s++)
	{
		stringstream sstr(oper[s]);
		int ope;
		sstr >> ope;

		switch (ope)
		{
		case 1://添加商品
		{
			int typ, com, sco;
			sstr >> typ >> com >> sco;
			Commodity tcom(typ, com, sco);
			map[sco].insert(tcom);
			amap.insert(pair<Commodity, int>(tcom, sco));
			break;
		}

		case 2://删除商品
		{
			int typ, com;
			sstr >> typ >> com;
			Commodity tcom(typ, com);
			int sco = amap[tcom];
			map[sco].erase(tcom);
			amap.erase(tcom);
			break;
		}

		case 3://查询k个得分最高的商品并输出
		{
			auto tmap = map;//临时处理
			vector<int> ks(m);//每类商品的最多选择数
			queue<int> wd;//待删除的某些类商品，用于删除
			queue<int> wdt;//待删除的某些类商品副本
			int k;
			sstr >> k;
			for (int i = 0; i < m; i++)
				sstr >> ks[i];
			for (int i = 0; i < ks.size(); i++)
				if (ks[i] == 0)
					wd.push(i);

			vector<vector<int>> sel(m);//最终的答案储存在这里

			for (auto tmap_it = tmap.begin(); tmap_it != tmap.end() && k > 0 && wdt.size() != m;)
			{//从最高分开始查询
				auto& score_set = (*tmap_it).second;
				while (score_set.size() == 0)//如果该分没有商品，则删除
				{
					tmap_it = tmap.erase(tmap_it);
					score_set = (*tmap_it).second;
				}
				if (score_set.size() == 0)
					break;


				for (auto score_it = score_set.begin(); score_it != score_set.end() && k > 0 && wdt.size() != m; score_it++)
				{//该分的每个物品
					auto& tcom = (*score_it);
					if (ks[tcom.type] > 0)
					{//如果该商品所属的类可选择
						ks[tcom.type]--;
						sel[tcom.type].push_back(tcom.id);
						k--;
						if (ks[tcom.type] == 0)
						{//从tmap中删除对应类的商品(先暂存在wd中，等待后续删除)
							wd.push(tcom.type);
							wdt.push(tcom.type);
							if (wdt.size() == m)
								break;
						}
					}
				}
				if (wdt.size() == m)
					break;
				while (!wd.empty())//对不可选择的商品进行从tmap删除的操作
				{
					int wdnum = wd.front();
					wd.pop();
					shanchu(tmap, wdnum);
				}

				tmap_it++;
			}
				
			
			for (int i = 0; i < sel.size(); i++)
			{
				if (sel[i].size() == 0)
				{
					cout << -1 << endl;
					continue;
				}
				for (int j = 0; j < sel[i].size(); j++)
					cout << sel[i][j] << " ";
				cout << endl;
			}
				

			break;
		}


		}




	}


	

}

/*
2 3
1 3
2 2
3 1
8
3 100 1 1
1 0 4 3
1 0 5 1
3 10 2 2
3 10 1 1
2 0 1
3 2 1 1
3 1 1 1



5 6
1 3
2 2
3 1
4 3
5 2
6 1
8
3 100 1 1
1 0 7 3
1 0 6 1
3 10 2 2
3 10 1 1
2 0 1
3 2 1 1
3 1 1 1

*/
