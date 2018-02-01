#include <bits/stdc++.h>

using namespace std;

#define ll unsigned long long

int n;
ll nums[200200];

int main() {
    scanf("%d", &n);
    priority_queue < ll > aux;
    for (int i = 0; i < n; i++) {
        scanf("%llu", &nums[i]);
        aux.push(-nums[i]);
    }

    ll ans = 0;
    while (aux.size() != 1) {
        ll x = 0, i = 0;
        if ((int)aux.size() % 2 == 0) i++;

        for (i; i < 3; i++) {
            x += aux.top();
            aux.pop();
        }
        aux.push(x);
        ans += -x;
    }
    printf("%llu\n", ans);

    return 0;
}

