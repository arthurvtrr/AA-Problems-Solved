#include <bits/stdc++.h>

using namespace std;

int t, n, m, s[50050], d[50050];
char typ[50050];
vector < int > posEC[50050], posDM[50050];

int cnt[50050], dp[50050];

int w(int a, int b) {
    int ret = 0, aux = 0;
    for (int i = 1; i <= n; i++)
        cnt[i] = 0;
    for (int i = a; i <= b; i++)
        for (int v : posEC[i]) {
            cnt[v]++;
            if (cnt[v] == 2) aux++;
        }

    ret = aux; aux = 0;

    for (int i = 1; i <= n; i++)
        cnt[i] = 0;
    for (int i = a; i <= b; i++)
        for (int v : posDM[i]) {
            cnt[v]++;
            if (cnt[v] == 2) aux++;
        }

    ret = max(ret, aux);
    //printf("%d %d %d\n", a, b, ret);
    return ret;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        for (int i = 0; i < 50050; i++) {
            posEC[i].clear(); posDM[i].clear();
        }

        scanf("%d %d", &m, &n);
        for (int i = 1; i <= n; i++)
            scanf(" %c", &typ[i]);
        for (int i = 1; i <= n; i++)
            scanf("%d", &s[i]);
        for (int i = 1; i <= n; i++)
            scanf("%d", &d[i]);

        for (int i = 1; i <= n; i++) {
            if (s[i] < d[i] && typ[i] != 'E' && typ[i] != 'C') {
                posDM[s[i]].push_back(i);
                posDM[d[i]].push_back(i);
            }
            else if (s[i] < d[i]) {
                posEC[s[i]].push_back(i);
                posEC[d[i]].push_back(i);
            }
        }

        memset(dp, 0, sizeof dp);

        vector<pair<int, int> > v; // start pos, best-k
        v.push_back(make_pair(0, 0));

        for (int x=1; x <= m; x++) {
            // Find the value of dp[x]
            int k = (--lower_bound(v.begin(), v.end(), make_pair(x+1, 0)))->second;
            dp[x] = dp[k] + w(k, x);
            //printf("%d %d\n", x, k);

            // Update the segments
            for (int i = v.size()-1; i >= 0; i--) {
                int y = v[i].first, oldk = v[i].second;
                // Case 1
                if (y > x && dp[x] + w(x, y) > dp[oldk] + w(oldk, y))
                    v.pop_back();
                // Case 2
                else {
                    int lo = x+1, hi = m;
                    while(lo <= hi) {
                        int mid = (lo+hi)/2;
                        if (dp[x] + w(x, mid) > dp[oldk] + w(oldk, mid))
                            hi = mid-1;
                        else
                            lo = mid+1;
                    }
                    if (lo != m+1) v.push_back(make_pair(lo, x));
                    break;
                }
            }
            if (v.size() == 0)
                v.push_back(make_pair(0, x));
        }

        //for (int i = 1; i <= m; i++)
        //    printf("%d ", dp[i]);
        //printf("\n");

        int aux = 1;
        for (int i = 1; i <= n; i++) {
            if (i > 1) printf(" ");

            while (aux <= m && dp[aux] < i) aux++;
            if (aux > m) printf("-1");
            else printf("%d", aux);
        }
        printf("\n");
    }
    return 0;
}

/*
1
10 2
E D
3 8
9 10
*/
