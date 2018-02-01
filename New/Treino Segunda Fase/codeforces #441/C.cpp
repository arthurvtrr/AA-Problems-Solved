#include <bits/stdc++.h>

using namespace std;

int n, m, x, y;
vector < int > words[100100];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        for (int j = 0; j < x; j++) {
            scanf("%d", &y);
            words[i].push_back(y);
        }
    }


    return 0;
}

