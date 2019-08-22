#include <iostream>

using namespace std;

int main(){
	//创建数组
	int record[30];
	int perform;
	int N;
	for(N=0;N<30;N++){
		cin>>perform;
		record[N] = perform;
		if(perform == 0)
			break;
	}
	N++;
	int present = record[0];
	int last = 0;	//记录上一次得分
	int score;		//总分数
	for(int i=0;i<N;i++){
		present = record[i];	//记录当前操作
		if(present == 0)	//没有跳到方块上
			break;
		else if(present == 1){
				last = 1;
				score += last;	//没有跳到方块重心
			}
		else{
			//跳到方块中心
			if(last == 1 || i == 0)
				last = 2;
			else
				last += 2;
		score += last;
		}
	}
	cout<<score;
	return 0;
}
