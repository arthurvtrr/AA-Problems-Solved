#include <bits/stdc++.h>

using namespace std;

#define ll long long

int t;
ll n;
vector < int > aux;

int main() {
    for (int i = 100; i < 1000; i++)
        for (int j = i; j < 1000; j++) {
            int num = i*j;
            string s = "";
            while (num) {
                s += (num % 10) + '0';
                num /= 10;
            }
            if (s.size() != 6) continue;

            bool p = true;
            for (int k = 0; k < 3; k++)
                if (s[k] != s[5-k])
                    p = false;

            if (p) aux.push_back(i*j);
        }

    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        int ans = 0;
        for (int v : aux)
            if (v < n)
                ans = max(ans, v);
        printf("%d\n", ans);
    }
    return 0;
}

