#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n, m, q, x, y;
vector < int > nums[1001000][2];
bool used[1001000];

ll aux[1001000][22], total;

int main() {
	scanf("%d %d %d", &n, &m, &q);

	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		for (int j = 0; j <= m; j++)
			used[j] = false;

		for (int j = 0; j < x; j++) {
			scanf("%d", &y);
			used[y] = true;
			nums[i][0].push_back(y);
		}
		for (int j = 1; j <= m; j++)
			if (!used[j])
				nums[i][1].push_back(j);
	}

	total = 0;
	for (ll i = 1; i <= m; i++)
		total += i * i;

	int lg = log2(m) + 1;

	for (int j = 0; j <= m; j++)
		used[j] = false;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 1 << lg; j++) {
			ll val = 0;
			for (int k = 0; k < lg; k++) {
				for (ll v : nums[i+k][(j & (1 << k)) != 0])
					if (!used[v]) {
						val += v*v;
						used[v] = true;
					}

				aux[i][k+1] = max(aux[i][k+1], val);
			}

			for (int k = 0; k < lg; k++)
				for (ll v : nums[i+k][(j & (1 << k)) != 0])
					used[v] = false;
		}
	}

	for (int i = 0; i < q; i++) {
		scanf("%d %d", &x, &y);
		x--; y--;

		if (y - x + 1 > lg) printf("%lld\n", total);
		else printf("%lld\n", aux[x][y - x + 1]);
	}

	return 0;
}
