#include <bits/stdc++.h>

using namespace std;

int t, n, k;
string s;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &k);
        cin >> s;

        int maxi = 0;
        for (int i = 0; i < n-k+1; i++) {
            int v = 1;
            for (int j = 0; j < k; j++)
                v *= s[i+j] - '0';
            maxi = max(maxi, v);
        }
        printf("%d\n", maxi);
    }
    return 0;
}
