#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pii pair < int, int >
#define N 200200

ll n;
int nums[N];
pii inv[N];

int M[N][25], LOG[N];

void process(int siz) {
    for (int i = 0; i <= siz; i++) M[i][0] = nums[i];
    for (int j = 1; (1 << j) <= siz; j++)
        for (int i = 1; i + (1 << j) - 1 <= siz; i++)
            M[i][j] = M[i][j-1] | M[i + (1 << (j-1))][j-1];
}

void init() {
    for (int i = 0, ret = 0; i < N; i++)
        LOG[i] = ret += (i > 1 && !(i & (i-1)));
}

int query(int i, int j) {
    int k = LOG[j - i + 1];
    return M[i][k] | M[j - (1 << k) + 1][k];
}

map < int, int > lst;

int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &nums[i]);

    init();
    process(n);

    ll ans = n * (n-1) / 2;

    stack < int > pilha;
    for (int i = 1; i <= n; i++) {
        while (!pilha.empty() && nums[pilha.top()] <= nums[i]) pilha.pop();
        if (pilha.empty()) inv[i].first = 1;
        else inv[i].first = pilha.top()+1;
        pilha.push(i);
    }

    while (!pilha.empty()) pilha.pop();

    for (int i = n; i > 0; i--) {
        while (!pilha.empty() && nums[pilha.top()] <= nums[i]) pilha.pop();
        if (pilha.empty()) inv[i].second = n;
        else inv[i].second = pilha.top()-1;
        pilha.push(i);
    }

    for (int i = 1; i <= n; i++) {
        if (lst.count(nums[i]))
            inv[i].first = lst[nums[i]] + 1;
        lst[nums[i]] = i;
    }

    for (ll i = 1; i <= n; i++) {
        ll a = inv[i].first, b = inv[i].second;

        if (query(inv[i].first, i) > nums[i]) {
            int ini = inv[i].first, fim = i;
            while (ini <= fim) {
                int mid = (ini + fim) / 2;
                if (query(mid, i) > nums[i]) ini = mid+1;
                else fim = mid-1;
            }
            a = fim+1;
        }
        if (query(i, inv[i].second) > nums[i]) {
            int ini = i, fim = inv[i].second;
            while (ini <= fim) {
                int mid = (ini + fim) / 2;
                if (query(i, mid) > nums[i]) fim = mid-1;
                else ini = mid+1;
            }
            b = ini-1;
        }

        ans -= (i - a + 1) * (b - i + 1) - 1;
    }

    printf("%lld\n", ans);
    return 0;
}

