#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll d, h, b;
string l;
vector < int > valid, lim;
ll dp[65][2][2];

ll solve(int id, bool lib, bool f) {
    if (dp[id][lib][f] != -1) return dp[id][lib][f];
    if (id == lim.size()) return f;

    ll ret = 0;
    for (int v : valid)
        if (lib || v <= lim[id])
            ret += solve(id+1, lib || (v < lim[id]), f || (v > 0));

    if (!f && valid[0] != 0)
        ret += solve(id+1, lib || (0 < lim[id]), f);

    return dp[id][lib][f] = ret;
}

int main() {
    while (1) {
        scanf("%lld %lld %lld", &d, &h, &b);
        cin >> l;
        if (d == -1) break;

        valid.clear();
        for (int i = 0; i < l.size(); i++)
            if (l[i] == 'S')
                valid.push_back(i);

        lim.clear();
        ll aux = h;
        while (aux) {
            lim.push_back(aux % b);
            aux /= b;
        }
        reverse(lim.begin(), lim.end());

        memset(dp, -1, sizeof dp);
        ll tot = solve(0, 0, 0);

        lim.clear();
        aux = d-1;
        while (aux) {
            lim.push_back(aux % b);
            aux /= b;
        }
        if (lim.empty()) lim.push_back(0);
        reverse(lim.begin(), lim.end());

        memset(dp, -1, sizeof dp);
        printf("%lld\n", tot - solve(0, 0, 0));
    }

    return 0;
}
