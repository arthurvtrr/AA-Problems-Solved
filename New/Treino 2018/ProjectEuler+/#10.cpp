#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define N 1000100

int t, n;
ll sum[N];
bool prime[N];

int main() {
    for (int i = 2; i < N; i++)
        prime[i] = true;
    for (int i = 2; i < N; i++)
        if (prime[i]) {
            for (int j = 2*i; j < N; j += i)
                prime[j] = false;
        }

    for (int i = 1; i < N; i++) {
        if (prime[i]) sum[i] = i;
        sum[i] += sum[i-1];
    }

    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%lld\n", sum[n]);
    }
    return 0;
}

