#include <bits/stdc++.h>

using namespace std;

int t, n, app[44][44];
bool prime[44];
vector < int > primes;

int main() {
    for (int i = 2; i < 44; i++)
        prime[i] = true;
    for (int i = 2; i < 44; i++)
        if (prime[i]) {
            primes.push_back(i);
            for (int j = 2*i; j < 44; j += i)
                prime[j] = false;
        }

    for (int i = 2; i < 44; i++) {
        int aux = i;
        for (int v : primes) {
            while (aux % v == 0) {
                app[i][v]++;
                aux /= v;
            }
        }
        if (aux != 1) app[i][aux]++;

        for (int j = 0; j < 44; j++)
            app[i][j] = max(app[i][j], app[i-1][j]);
    }

    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        long long ans = 1;
        for (int i = 1; i < 44; i++)
            for (int j = 0; j < app[n][i]; j++)
                ans *= i;
        printf("%lld\n", ans);
    }
    return 0;
}
