#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n;
ll nums[110];
bool prime[1001000];
vector < ll > primes;

int main() {
    for (int i = 2; i < 1001000; i++)
        prime[i] = true;
    for (int i = 2; i < 1001000; i++)
        if (prime[i]) {
            primes.push_back(i);
            for (int j = 2*i; j < 1001000; j += i)
                prime[j] = false;
        }

    scanf("%d", &n);

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &nums[i]);
        ans += nums[i];

        vector < ll > fac;
        for (int j = 0; j < primes.size(); j++) {
            while (nums[i] % primes[j] == 0) {
                fac.push_back(primes[j]);
                nums[i] /= primes[j];
            }
        }
        if (nums[i] != 1) fac.push_back(nums[i]);

        if (!fac.empty()) {
            sort(fac.begin(), fac.end(), greater<ll>());
            ll aux = 1;
            for (int j = 0; j < fac.size(); j++) {
                ans += aux;
                aux *= fac[j];
            }
        }
    }
    printf("%lld\n", ans);

    return 0;
}
