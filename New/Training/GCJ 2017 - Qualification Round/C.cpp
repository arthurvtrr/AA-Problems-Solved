#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pll pair < ll, ll >

int t;
ll n, k;

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        cin >> n >> k;

        map < ll, ll > cont;
        vector < pll > inter;

        long long left = k;

        inter.push_back(pll(n, 1));

        while (!inter.empty()) {
            for (int i = inter.size() - 1; i >= 0; i--) {
                left -= inter[i].second;
                if (left <= 0) {
                    if (inter[i].first % 2 == 0)
                        printf("Case #%d: %lld %lld\n", tc+1, inter[i].first / 2, inter[i].first / 2 - 1);
                    else
                        printf("Case #%d: %lld %lld\n", tc+1, inter[i].first / 2, inter[i].first / 2);

                    inter.clear();
                    break;
                }
            }

            while (!inter.empty()) {
                pll x = inter.back();
                inter.pop_back();
                if (x.first % 2 == 0) {
                    cont[x.first / 2 - 1] += x.second;
                    cont[x.first / 2] += x.second;
                }
                else {
                    cont[x.first / 2] += 2 * x.second;
                }
            }

            for (map < ll, ll >::iterator it = cont.begin(); it != cont.end(); it++)
                if (it->first > 0)
                    inter.push_back(pll(it->first, it->second));

            cont.clear();
        }
    }

    return 0;
}

