#include <bits/stdc++.h>

using namespace std;

int n;
long long first[77], last[77];
char s[77];

int main() {
    int t = 1;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < 77; i++)
            first[i] = last[i] = 0;

        for (int i = 0; i < n; i++) {
            scanf("%s", s);
            for (int j = 0; j < n; j++) {
                if (j < 60 && (s[j] == '1' || i == j)) first[i] |= 1LL << j;
                else if (j >= 60 && (s[j] == '1' || i == j)) last[i] |= 1LL << (j-60);
            }
        }

        long long x, y;
        vector < int > ans = {0, 0, 0, 0, 0, 0, 0};
        for (int a = 0; a < n; a++) {
            x = first[a], y = last[a];
            if (__builtin_popcountll(x) + __builtin_popcountll(y) == n && ans.size() > 1) ans = {a};

            for (int b = a+1; b < n; b++) {
                x = first[a] | first[b], y = last[a] | last[b];
                if (__builtin_popcountll(x) + __builtin_popcountll(y) == n && ans.size() > 2) ans = {a, b};

                for (int c = b+1; c < n; c++) {
                    x = first[a] | first[b] | first[c], y = last[a] | last[b] | last[c];
                    if (__builtin_popcountll(x) + __builtin_popcountll(y) == n && ans.size() > 3) ans = {a, b, c};

                    for (int d = c+1; d < n; d++) {
                        x = first[a] | first[b] | first[c] | first[d], y = last[a] | last[b] | last[c] | last[d];
                        if (__builtin_popcountll(x) + __builtin_popcountll(y) == n && ans.size() > 4) ans = {a, b, c, d};

                        for (int e = d+1; e < n; e++) {
                            x = first[a] | first[b] | first[c] | first[d] | first[e], y = last[a] | last[b] | last[c] | last[d] | last[e];
                            if (__builtin_popcountll(x) + __builtin_popcountll(y) == n && ans.size() > 5) ans = {a, b, c, d, e};
                        }
                    }
                }
            }
        }

        printf("Case %d: %d", t++, ans.size());
        for (int v : ans)
            printf(" %d", v+1);
        printf("\n");
    }

    return 0;
}
