#include <bits/stdc++.h>

using namespace std;

int n, nums[100100];

map < int, int > cnt;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        cnt[nums[i]]++;
    }

    vector < int > a;
    for (int i = 0; i < 100100; i++)
        if (cnt[i])
            a.push_back(i);

    sort(a.begin(), a.end());
    vector < int > aux(a.size(), 0);
    for (int i = 0; i < a.size(); i++)
        aux[i] = cnt[a[i]];

    int ans = 0;
    for (int i = a.size() - 1; i >= 0; i-- ) {
        if (aux[i] > 0) {
            ans += aux[i];
            for (int j = i-1; j >= 0; j--)
                aux[j] -= aux[i];
            break;
        }
    }
    printf("%d\n", ans);

    return 0;
}
