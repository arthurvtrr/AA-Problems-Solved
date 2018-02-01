#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll n, k;
ll fat[5] = {0, 1, 2, 6, 24};

int main() {
    scanf("%lld %lld", &n, &k);

    ll ans = 1, aux;
    for (int i = 2; i <= k; i++) {
        vector < int > x;
        for (int j = 0; j < i; j++)
            x.push_back(j);
        do {
            bool v = true;
            for (int j = 0; j < i; j++)
                if (x[j] == j)
                    v = false;

            if (!v) continue;

            aux = 1;
            for (int j = 0; j < i; j++)
                aux *= n-j;
            aux /= fat[i];
            ans += aux;

        } while (next_permutation(x.begin(), x.end()));
    }
    printf("%lld\n", ans);

    return 0;
}
