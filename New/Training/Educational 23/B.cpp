#include <bits/stdc++.h>

using namespace std;

int n;
long long nums[100100];
map < int, long long > cnt, use;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &nums[i]);
    sort(nums, nums+n);

    for (int i = 0; i < 3; i++)
        use[nums[i]]++;
    for (int i = 0; i < n; i++)
        cnt[nums[i]]++;

    long long ans = 1;
    for (map < int, long long >::iterator it = use.begin(); it != use.end(); it++) {
        if (it->second == 1) ans *= cnt[it->first];
        else if (it->second == 2) ans *= cnt[it->first]*(cnt[it->first]-1)/2;
        else ans *= cnt[it->first]*(cnt[it->first]-1)*(cnt[it->first]-2)/6;
    }
    printf("%lld\n", ans);

    return 0;
}

