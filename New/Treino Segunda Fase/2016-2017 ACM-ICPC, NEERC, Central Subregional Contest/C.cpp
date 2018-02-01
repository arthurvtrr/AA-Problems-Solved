#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d %d", &n, &m);

    if (n < 2 || m < 2) {
        printf("0\n");
        return 0;
    }

    swap(n, m);

    vector < ii > a, b;
    if (m % 2 == 1)
        for (int j = n-1; j > 0; j -= 2)
            a.push_back(ii(m-1, j));

    for (int i = 1; i < m-(m%2); i += 2)
        for (int j = n-1; j > 1; j--)
            a.push_back(ii(i, j));

    for (int i = 1; i < m-(m%2); i++)
        a.push_back(ii(i, 1));

    if (n % 2 == 1)
        for (int j = m-1; j > 0; j -= 2)
            b.push_back(ii(j, n-1));

    for (int i = 1; i < n-(n%2); i += 2)
        for (int j = m-1; j > 1; j--)
            b.push_back(ii(j, i));

    for (int i = 1; i < n-(n%2); i++)
        b.push_back(ii(1, i));

    if (a.size() > b.size()) {
        printf("%d\n", a.size());
        for (ii v : a)
            printf("%d %d\n", v.first, v.second);
    }
    else {
        printf("%d\n", b.size());
        for (ii v : b)
            printf("%d %d\n", v.first, v.second);
    }

    return 0;
}
