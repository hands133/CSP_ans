#include <iostream>

using namespace std;

int main(){
	//��������
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
	int last = 0;	//��¼��һ�ε÷�
	int score;		//�ܷ���
	for(int i=0;i<N;i++){
		present = record[i];	//��¼��ǰ����
		if(present == 0)	//û������������
			break;
		else if(present == 1){
				last = 1;
				score += last;	//û��������������
			}
		else{
			//������������
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
