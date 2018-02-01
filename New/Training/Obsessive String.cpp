#include <bits/stdc++.h>

using namespace std;

string s, a, b;
int lens[200200];

void Zfunction() {
    int n = s.size();
    int L = 0, R = 0;

    for (int i = 1; i < n; i++) {
        if (i > R) {
            L = R = i;
            while (R < n && s[R-L] == s[R]) R++;
            lens[i] = R-L;
            R--;
        }
        else {
            if (lens[i-L] < R-i+1)
                lens[i] = lens[i-L];
            else {
                L = i;
                while (R < n && s[R-L] == s[R]) R++;
                lens[i] = R-L;
                R--;
            }
        }
    }
}

#define ll long long
#define MOD 1000000007

ll dp[200200][2][2];
int nxt[200200];

ll solve(int ind, int fim, int valid) {
    if (dp[ind][fim][valid] != -1)
        return dp[ind][fim][valid];

    if (ind == s.size()) {
        if (valid) return 1;
        return 0;
    }

    ll ret = solve(ind+1, fim, valid);
    if (fim && ind+1 != s.size()) ret += solve(ind+1, false, valid);
    else if (!fim && nxt[ind] != s.size()) ret += solve(nxt[ind], true, true);

    return dp[ind][fim][valid] = ret % MOD;
}

int main() {
    cin >> a >> b;
    if (a.size() < b.size()) printf("0\n");
    else {
        s = b;
        s += '$';
        s += a;
        Zfunction();

        int last = s.size();
        for (int i = s.size()-1; i > b.size(); i--) {
            if (lens[i] == b.size())
                last = i + b.size() - 1;
            nxt[i] = last;
        }

        for (int i = 0; i < 200200; i++)
            dp[i][0][0] = dp[i][0][1] = dp[i][1][0] = dp[i][1][1] = -1;

        printf("%lld\n", solve(b.size()+1, 0, 0));
    }

    return 0;
}
