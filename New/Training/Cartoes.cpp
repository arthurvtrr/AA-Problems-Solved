#include <bits/stdc++.h>
#define INF 1000000001
using namespace std;

long long int cache[10001][10001] = {};

long long int solve(int*,int,int,int);

int n,cartoes[10001];

int main(){
    while(scanf("%d",&n) != EOF){
        for(int i = 0 ; i < n ; i++){
            scanf("%d",&cartoes[i]);
        }
        int first = 0 ,last = n - 1;
		cache[first][last] = solve(cartoes,first,last,0);
        cout << cache[first][last] << endl;
		memset(cache, 0, sizeof(cache[0][0]) * 10001 * 10001);
	 }
    return 0;
}

long long int solve(int *cartoes,int first,int last,int ctrl){
	long long int x,y;
	if(first > last) return 0;

	if(cache[first + 1][last] != 0) x = cache[first + 1][last];
	else cache[first + 1][last] = x = solve(cartoes,first + 1,last,ctrl + 1);

	if(cache[first][last - 1] != 0) x = cache[first][last - 1];
	else cache[first][last - 1] = y = solve(cartoes,first,last - 1,ctrl + 1);

	if(ctrl % 2 != 0) return min(x,y);

	else return max(x + cartoes[first],y + cartoes[last]);
}
