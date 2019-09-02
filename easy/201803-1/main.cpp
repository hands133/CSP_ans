#include <iostream>

using namespace std;

int main(){
	// + 没跳到下一个方块游戏结束
	// + 没有跳到方块中心 1 分
	// + 跳到方块中心：
	//		- 上一次 1 分这一次 2 分
	//		- 上一次跳到方块中心，这一次得分为上一次得分 +2
	// 1 表示没有跳到中心
	// 2 表示跳到方块中心
	// 0 表示没有跳到方块上，游戏结束
	int record[30];	// 分数记录
	int perform;	// 用于输入
	int N;
	for(N = 0; N < 30; N++){
		cin >> perform;
		record[N] = perform;
		if(perform == 0)
			break;
	}
	N++;
	int present = record[0];
	int last = 0;	//记录上一次得分
	int score = 0;		//总分数
	for(int i = 0; i < N; i++){
		present = record[i];//当前分数
		if(present == 0)	//结束
			break;
		else if(present == 1){	// 没有跳到方块中心
				last = 1;
				score += last;
			}
		else{
			//跳到方块中心
			if(last == 1 || i == 0)	//第一次为方块中心或者上一次没有跳到方块中心
				last = 2;
			else
				last += 2;
			score += last;
		}
	}
	cout << score << endl;
	system("pause");
	return 0;
}
