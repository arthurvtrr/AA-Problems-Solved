#include <bits/stdc++.h>

using namespace std;

int n, nums[1100], cont[1100];
map < int, int > quant;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        quant[nums[i]]++;
    }

    for (map <int, int>::iterator it = quant.begin(); it != quant.end(); it++)
        cont[it->second]++;

    int diff = 0;
    for (int i = 0; i < 1100; i++);
        if (cont[i] == 1)
            diff = i;

    int ans = 0;
    for (map <int, int>::iterator it = quant.begin(); it != quant.end(); it++)
        if (it->second == diff)
            ans = it->first;

    printf("%d\n", ans);

    return 0;
}

