#include <bits/stdc++.h>

using namespace std;

string s, aux;
int m, l, r, k;

int main() {
    cin >> s;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &l, &r, &k);
        k %= r - l + 1;
        aux = s;
        for (int j = l-1; j < r; j++) {
            int newi = j+k;
            if (newi >= r)
                newi -= r - l + 1;
            s[newi] = aux[j];
        }
    }
    cout << s << endl;

    return 0;
}

