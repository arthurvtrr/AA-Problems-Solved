#include <bits/stdc++.h>

using namespace std;

long long a, b, c;

int main() {
    scanf("%lld %lld %lld", &a, &b, &c);

    used[1] = 1;
    long long last = 1, ind = 1;
    while (1) {
        long long x = (a * last + last % b) % c;

    }
    return 0;
}
