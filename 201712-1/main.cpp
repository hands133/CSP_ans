#include <iostream>

using namespace std;

int array[10000];

int abs(int i){
	if(i<0)
		return -i;
	else
		return i; 
}

int main(){
	int n;
	cin >> n;	//����Ԫ�ظ��� 
	for(int i=0;i<n;i++)
		cin>>array[i];
	//ð������ 
	for(int i=0;i<n-1;i++){
		for(int j=n-2;j>=i;j--){
			if(array[j] > array[j+1]){
				int exchange = array[j];
				array[j] = array[j+1];
				array[j+1] = exchange;
			}
		}
	}
	int absvalue = array[1] - array[0];
	for(int k=1;k<n-1;k++){
		if((array[k+1] - array[k]) < absvalue)
			absvalue = array[k+1] - array[k];
	}
	cout << absvalue;
	system("pause");
	return 0;
}
