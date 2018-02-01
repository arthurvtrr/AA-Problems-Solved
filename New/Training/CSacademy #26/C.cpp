#include <bits/stdc++.h>

using namespace std;

int n, l, r, nums[100100];

int main() {
    scanf("%d %d %d", &n, &l, &r);

    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    long long ans = 0;
    int ini = 0, fim = 0;
    set < int > aux;

    while (ini < n) {
        while (!aux.count(nums[fim]) && fim < n) {
            aux.insert(nums[fim]);
            fim++;
        }

        int x = fim - ini - l + 1;
        ans += max(0, min(x, r-l+1));
        aux.erase(nums[ini]);
        ini++;
        fim = max(fim, ini);
    }

    printf("%lld\n", ans);

    return 0;
}

