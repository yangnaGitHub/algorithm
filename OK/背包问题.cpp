#include<iostream>
#include<vector>
#include <iomanip>

using namespace std;

int package(int limit, int* weights, int* values, int count){
	int row = count + 1;
	int col = limit + 1;
	vector<vector<int>> maxvalue(row, vector<int>(col));

#ifdef PACKAGE_0
	for(int index = 0; index < row; index++)
		maxvalue[index][0] = 0;
	for(int index = 0; index < col; index++)
		maxvalue[0][index] = 0;

	/*
     价值:10  40  30  50
     重量:5   4   6   3
	 i代表加入背包的是前i件物品,j表示背包的承重
	 假如我们放进背包:f[i][j] = f[i - 1][j - weight[i]] + value[i]
	 假如我们不放进背包:f[i][j] = f[i - 1][j]
     limit=0 limit=1 limit=2 limit=3                         limit=4 limit=5 limit=6 limit=7 limit=8 limit=9 limit=10
     0       0       0       0                               0       0       0       0       0       0       0
     0       0       0       0                               0       10      10      10      10      10      10
     0       0       0       0                               40      40      40      40      40      50      50
     0       0       0       0                               40      40      40      40      40      50      70max([2][10], [2][10-w[2]=4]+v[2])
     0       0       0       50max([3][3], [3][3-w[3]]+v[3]) 50      50      50      90      90      90      90max([3][10], [3][10-w[3]=7]+v[3])
	 当前的值 = 上一行的值中(列数-当前重量的值+当前重量的价值, 同一列的值)
    */
	for(int xindex = 1; xindex < col; xindex++){
		for(int yindex = 1; yindex < row; yindex++){
			int w_index = yindex - 1;
			if(xindex < weights[w_index]){
				maxvalue[yindex][xindex] = maxvalue[w_index][xindex];
			}else{
				maxvalue[yindex][xindex] = ((maxvalue[w_index][xindex] > (maxvalue[w_index][xindex - weights[w_index]] + values[w_index])) ? maxvalue[w_index][xindex] : (maxvalue[w_index][xindex - weights[w_index]] + values[w_index]));
			}
		}
	}
	/*
	//另一种方法
	for(int xindex = 1; xindex < row; xindex++){
		for(int yindex = col-1; yindex >= 1; yindex--){
			int w_index = xindex - 1;
			if (weight[w_index] <= j) {
				maxvalue[yindex] = (maxvalue[yindex] > (maxvalue[yindex - weights[w_index] + values[w_index])) ? maxvalue[yindex] : (maxvalue[yindex - weights[w_index]] + values[w_index]);
			}
		}
	}
	*/
#endif
    

#ifdef PACKAGE_1
	//完全背包问题与01背包问题的区别在于每一件物品的数量都有无限个,而01背包每件物品数量只有一个
	//https://www.cnblogs.com/Kalix/p/7622102.html
	//https://www.cnblogs.com/fengziwei/p/7750849.html
#endif

#ifdef PACKAGE_2
	//多重背包中每个物品的个数都是给定的,可能不是一个但也绝对不是无限个
#endif

	//打印setw的使用(占位符)
	for(int yindex = 0; yindex < row; yindex++){
		for(int xindex = 0; xindex < col; xindex++)
			cout << setw(2) << maxvalue[yindex][xindex] << " ";
		cout << endl;
	}

	return 0;
}

int main(){
	int limit = 10;
	int values[] = {10, 40, 30, 50};
	int weights[] = {5, 4, 6, 3};
    int count = sizeof(values) / sizeof(values[0]);
	package(limit, weights, values, count);
	return 0;
}