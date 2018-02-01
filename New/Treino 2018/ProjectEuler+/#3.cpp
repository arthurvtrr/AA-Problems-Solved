#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define N 1000100

int t;
ll n;
bool prime[N];
vector < int > primes;

int main() {
    for (int i = 2; i < N; i++)
        prime[i] = true;
    for (int i = 2; i < N; i++)
        if (prime[i]) {
            primes.push_back(i);
            for (int j = 2*i; j < N; j += i)
                prime[j] = false;
        }

    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        ll ans = 1, aux = n;
        for (int i = 0; i < primes.size(); i++)
            while (aux % primes[i] == 0) {
                ans = primes[i];
                aux /= primes[i];
            }

        printf("%lld\n", max(ans, aux));
    }
    return 0;
}
