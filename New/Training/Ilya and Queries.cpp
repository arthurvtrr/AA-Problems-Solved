#include <bits/stdc++.h>

using namespace std;

string s;
int m, x, y, acum[100100];

int main() {
    cin >> s;

    for (int i = 0; i < (int)s.size() - 1; i++) {
        acum[i+1] = s[i] == s[i+1];
        acum[i+1] += acum[i];
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        printf("%d\n", acum[y-1] - acum[x-1]);
    }

    return 0;
}
