#include <bits/stdc++.h>

using namespace std;

int n, x;
set < int > put;

int main() {
    scanf("%d", &n);
    int maxi = 0;
    for (int i = 0; i < 2*n; i++) {
        scanf("%d", &x);
        if (!put.count(x)) put.insert(x);
        else put.erase(x);
        maxi = max(maxi, (int)put.size());
    }
    printf("%d\n", maxi);

    return 0;
}
