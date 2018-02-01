#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll a, b, k;

bool is_prime(ll x) {
    int sqr = sqrt(x);
    for (int i = 2; i <= sqr; i++)
        if (x % i == 0)
            return false;
    return true;
}

bool prime[100100];
vector < ll > primes;

void gen_primes(int N) {
    for (int i = 2; i < 100100; i++)
        prime[i] = true;
    for (int i = 2; i <= N; i++)
        if (prime[i]) {
            for (int j = 2*i; j <= N; j += i)
                prime[j] = false;
            primes.push_back(i);
        }
}

ll ans;

ll solve(ll val, int ind, int sign) {
    while (ind < primes.size()) {
        ll new_v = val * primes[ind];
        if (new_v <= 2000000000) {
            ans += sign * (b / new_v - (a-1) / new_v);
            solve(new_v, ind+1, -sign);
        }
        ind++;
    }
}

int main() {
    scanf("%lld %lld %lld", &a, &b, &k);

    if (!is_prime(k)) printf("0\n");
    else {
        int sqr = sqrt(b);
        if (k > sqr) printf("%d\n", k >= a && k <= b);
        else {
            gen_primes(k-1);

            ans = b / k - (a-1) / k;
            solve(k, 0, -1);
            printf("%lld\n", ans);
        }
    }

    return 0;
}
