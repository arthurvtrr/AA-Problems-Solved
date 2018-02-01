#include <bits/stdc++.h>

using namespace std;

int n, m;
string s, t;

int main() {
    scanf("%d %d", &n, &m);
    cin >> s;
    cin >> t;

    vector < int > best;
    for (int i = 0; i < 10000; i++) best.push_back(0);

    for (int i = 0; i < m - n + 1; i++) {
        vector < int > aux;
        for (int j = 0; j < n; j++) {
            if (s[j] != t[i+j])
                aux.push_back(j+1);
        }
        if (aux.size() < best.size()) best = aux;
    }

    printf("%d\n", best.size());
    for (int i = 0; i < best.size(); i++) {
        if (i) printf(" ");
        printf("%d", best[i]);
    }
    printf("\n");

    return 0;
}
