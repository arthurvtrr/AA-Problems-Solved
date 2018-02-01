#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define MOD 1000000007
#define pii pair < int, int >

map < pii, ll > dp;
int n, m, k;
bool app[200200];

void solve(pii state) {
    int siz = state.first, val = state.second;
    printf("%d\n", siz);

    if (siz == 1) return;

    solve(pii(siz/2, val));
    solve(pii(siz - siz/2, val));
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    solve(pii(n, m));

    return 0;
}

