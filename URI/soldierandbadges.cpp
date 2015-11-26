#include <bits/stdc++.h>

using namespace std;

int n, badges[3300], cnt[9100000], needed = 0;

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &badges[i]);
        cnt[badges[i]]++;
    }

    for (int i = 0; i < 9010000; i++) {
        if (cnt[i] > 1) {
            needed += cnt[i] - 1;
            cnt[i+1] += cnt[i] - 1;
        }
    }

    printf("%d\n", needed);

    return 0;
}
