#include <bits/stdc++.h>

using namespace std;
#define ll long long

ll r = 0;

void update(ll a[], int pos, int val, int MAX) {
    while(pos <= MAX) {
        a[pos] += val;
        pos += (pos & -pos);
    }
}
ll read(ll a[], int pos) {
    ll sum = 0;
    while(pos) {
        sum += a[pos];
        pos -= (pos & -pos);
    }
    return sum;
}

int main() {
    int t, n;
    string s;

    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        r = 0;
        map < string , int > correctpos;
        scanf("%d", &n);
        string yoda[n+10];
        for (int j = 0; j < n; j++)
            cin >> yoda[j];

        for (int k = 1; k <= n; k++) {
            cin >> s;
            correctpos[s] = k;
        }

        int pos[n+10];
        for (int j = 0; j < n; j++)
            pos[j] = correctpos[yoda[j]];

        ll seg[n+10];
        memset(seg, 0, sizeof seg);
        for (int j = n-1; j >= 0; j--) {
            r += read(seg, pos[j]);
            update(seg, pos[j], 1, n+10);
        }

        printf("%lld\n", r);
    }
    return 0;
}
