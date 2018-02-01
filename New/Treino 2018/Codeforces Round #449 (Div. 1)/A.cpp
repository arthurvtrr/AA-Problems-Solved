#include <bits/stdc++.h>

using namespace std;

#define ll long long

string ini = "What are you doing at the end of the world? Are you busy? Will you save us?";
string a = "What are you doing while sending .";
string b = ".? Are you busy? Will you send .";
string c = ".?";
string ans = "";

int q;
ll n, k, siz[100100];

int main() {
    siz[0] = ini.size();
    for (int i = 1; i < 100100; i++) {
        if (siz[i-1] >= 1000000000000000000LL) siz[i] = siz[i-1];
        else siz[i] = 2*siz[i-1] + a.size() + b.size() + c.size();
    }

    scanf("%d", &q);
    for (int qq = 0; qq < q; qq++) {
        scanf("%lld %lld", &n, &k);
        if (siz[n] < k) ans += '.';
        else {
            for (int i = n; i >= 0; i--) {
                if (i == 0) {
                    ans += ini[k-1];
                    break;
                }

                if (k <= a.size()) { ans += (a[k-1] == '.'? '"' : a[k-1]); break; }
                k -= a.size();
                if (k <= siz[i-1]) continue;
                k -= siz[i-1];
                if (k <= b.size()) { ans += (b[k-1] == '.'? '"' : b[k-1]); break; }
                k -= b.size();
                if (k <= siz[i-1]) continue;
                k -= siz[i-1];
                ans += (c[k-1] == '.'? '"' : c[k-1]);
                break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}

