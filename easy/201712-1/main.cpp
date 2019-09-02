#include <iostream>

using namespace std;

int array[10000];

int abs(int i){
	if(i<0)
		return -i;
	else
		return i; 
}

// 最小差值，给定 n 个数字，找出其中差的绝对值最小的两个数，输出差的绝对值
// 输入要求：2 <= n <= 1000
// 每个数字都是不超过 10000 的正整数

int main(){
	int n;
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> array[i];
	// 对数组进行排序
	for(int i = 0; i < n - 1; i++){
		for(int j = n - 2; j >= i; j--){
			if(array[j] > array[j + 1]){
				int exchange = array[j];
				array[j] = array[j + 1];
				array[j + 1] = exchange;
			}
		}
	}
	int absvalue = array[1] - array[0];
	for(int k=1;k<n-1;k++){
		if((array[k+1] - array[k]) < absvalue)
			absvalue = array[k+1] - array[k];
	}
	cout << absvalue;
	return 0;
}
