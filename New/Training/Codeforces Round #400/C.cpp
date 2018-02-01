#include <bits/stdc++.h>

using namespace std;

#define INF 100000000000000000LL

int n;
long long k, nums[100100];
map < long long, int > cont;

int main() {
    scanf("%d %lld", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &nums[i]);
        nums[i] += nums[i-1];
    }

    vector < long long > pots;
    if (k == 1) pots.push_back(1);
    else if (k == -1) {
        pots.push_back(1);
        pots.push_back(-1);
    }
    else {
        long long p = 1;
        while (1) {
            pots.push_back(p);
            p *= k;
            if (abs(p) > INF) break;
        }
    }

    long long sol = 0;
    cont[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < pots.size(); j++)
            sol += cont[nums[i] - pots[j]];

        cont[nums[i]]++;
    }

    printf("%lld\n", sol);

    return 0;
}

