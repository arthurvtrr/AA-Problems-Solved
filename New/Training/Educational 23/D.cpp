#include <bits/stdc++.h>

using namespace std;

int n, nums[1001000];
vector < int > pos[1001000];

struct inv {
    int l, r;
    inv(int l, int r): l(l), r(r) {}
    bool operator <(inv other) const {
        return r < other.r;
    }
};

set < inv > aux;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i]);
        pos[nums[i]].push_back(i);
    }

    long long ans = 0;
    aux.insert(inv(-1, -1));
    aux.insert(inv(10000000, 10000000));

    for (int i = 1; i < 1001000; i++) {
        for (int j = 0; j < pos[i].size(); j++) {
            inv x = *(aux.lower_bound(inv(0, pos[i][j]))), y = *(--aux.lower_bound(inv(0, pos[i][j])));
            int a = (y.l == -1? 1 : y.r+1), b = (x.l == 10000000? n : x.l-1);

            if (j == 0) ans -= (pos[i][j] - a + 1LL) * (b - pos[i][j] + 1LL) * i;
            else ans -= min(pos[i][j] - a + 1LL, pos[i][j] - pos[i][j-1] + 0LL) * (b - pos[i][j] + 1LL) * i;
        }

        for (int j = 0; j < pos[i].size(); j++) {
            inv newi = inv(pos[i][j], pos[i][j]);
            inv x = *(aux.lower_bound(inv(0, pos[i][j]-1)));

            if (x.r == pos[i][j]-1) {
                aux.erase(x);
                newi = inv(x.l, x.r+1);
            }

            x = *(aux.lower_bound(inv(0, pos[i][j]+1)));

            if (x.l == pos[i][j]+1) {
                aux.erase(x);
                newi = inv(newi.l, x.r);
            }

            aux.insert(newi);
        }

        for (int j = 0; j < pos[i].size(); j++) {
            inv x = *(aux.lower_bound(inv(0, pos[i][j])));

            if (j == 0) ans += (pos[i][j] - x.l + 1LL) * (x.r - pos[i][j] + 1LL) * i;
            else ans += min(pos[i][j] - x.l + 1LL, pos[i][j] - pos[i][j-1] + 0LL) * (x.r - pos[i][j] + 1LL) * i;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
