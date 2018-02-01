#include <bits/stdc++.h>

using namespace std;

string s;
int n, quant[5500], siz[5050][5050], ans[5500];
long long hashs[5050], inv[5050];
bool palindrome[5050][5050];

#define p 31
#define MOD 1000000007
#define ll long long

ll fastPow(ll base, ll exp) {
	if (exp <= 0) return 1;

	ll result;
	result = fastPow(base, exp / 2);
	result *= result;
	result %= MOD;

	if (exp % 2 != 0) result *= base;
	return result % MOD;
}

ll extended_euclid(ll a, ll b, ll &x, ll &y) {
	ll xx = y = 0;
	ll yy = x = 1;
	while (b) {
		ll q = a/b;
		ll t = b; b = a%b; a = t;
		t = xx; xx = x-q*xx; x = t;
		t = yy; yy = y-q*yy; y = t;
	}
	return a;
}

ll mod_inverse(ll a, ll m) {
	ll x, y;
	ll d = extended_euclid(a, m, x, y);
	if (d > 1) return -1;
	return ((x % m) + m) % m;
}

void calcHash() {
	for (int i = 0; i < n; i++) {
		hashs[i] = s[i] * fastPow(p, i);
		hashs[i] %= MOD;
		hashs[i] += hashs[i-1];
		hashs[i] %= MOD;
	}

	for (int i = 0; i < n; i++) {
		inv[i] = fastPow(p, i);
		inv[i] = mod_inverse(inv[i], MOD);
	}
}

bool matchs(int l, int r, int l1, int r1) {
	if (r - l != r1 - l1) return false;
	ll a = (((((hashs[r] - hashs[l-1]) % MOD) + MOD) % MOD) * inv[l]) % MOD;
	ll b = (((((hashs[r1] - hashs[l1-1]) % MOD) + MOD) % MOD) * inv[l1]) % MOD;
	return a == b;
}

void dfs(int ini, int fim) {
    if (ini == fim) {
        siz[ini][fim] = 1;
        quant[1]++;
        return;
    }

    int meio = (ini + fim + 1) / 2;

    if (siz[ini][meio-1] == -1) dfs(ini, meio-1);
    if (siz[(ini + fim) / 2 + 1][fim] == -1) dfs((ini + fim) / 2 + 1, fim);

    if (matchs(ini, meio-1, (ini + fim) / 2 + 1, fim) && siz[ini][meio-1] > 0) siz[ini][fim] = siz[ini][meio-1] + 1;
    else siz[ini][fim] = palindrome[ini][fim];

    quant[siz[ini][fim]]++;
}

int main() {
    cin >> s;
    n = s.size();

    for (int i = 0; i < 5050; i++)
        for (int j = 0; j < 5050; j++)
            palindrome[i][j] = false;

    for (int i = 0; i < n; i++) {
        int ini = i, fim = i;
        while (ini >= 0 && fim < n) {
            if (s[ini] != s[fim]) break;

            palindrome[ini][fim] = true;
            ini--; fim++;
        }
    }

    for (int i = 1; i < n; i++) {
        int ini = i-1, fim = i;
        while (ini >= 0 && fim < n) {
            if (s[ini] != s[fim]) break;

            palindrome[ini][fim] = true;
            ini--; fim++;
        }
    }

    calcHash();
    memset(siz, -1, sizeof siz);

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            if (siz[i][j] == -1)
                dfs(i, j);

    int sum = 0;
    for (int i = 5049; i > 0; i--) {
        sum += quant[i];
        ans[i] = sum;
    }

    for (int i = 1; i <= s.size(); i++) {
        if (i > 1) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");

    return 0;
}

