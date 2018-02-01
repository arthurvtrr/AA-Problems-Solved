#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, nums[100100], acum[2][200200];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &nums[i]);

    for (int i = 0; i < 2; i++)
        for (int j = 1; j <= n; j++) {
            acum[i][j] = (nums[j] == i+1);
            acum[i][j] += acum[i][j-1];
        }
    for (int i = n+1; i < 200200; i++) {
        acum[0][i] = acum[0][i-1];
        acum[1][i] = acum[1][i-1];
    }

    vector < pii > ways;
    for (int i = 1; i <= n; i++) {
        int pos = 1, a = 0, b = 0, last = 0;

        while (pos <= n) {
            int ini = i, fim = 2*i - 1;
            while (ini <= fim) {
                int mid = (ini + fim) / 2;

                if (acum[0][pos+mid-1] - acum[0][pos-1] >= i || acum[1][pos+mid-1] - acum[1][pos-1] >= i) fim = mid-1;
                else ini = mid+1;
            }

            if (acum[0][pos+ini-1] - acum[0][pos-1] == i) { a++; last = 1; }
            else { b++; last = 2; }
            pos += ini;
        }

        if (pos != n+1) continue;
        if (a > b && last == 1) ways.push_back(pii(a, i));
        else if (a < b && last == 2) ways.push_back(pii(b, i));
    }

    sort(ways.begin(), ways.end());

    printf("%d\n", ways.size());
    for (int i = 0; i < ways.size(); i++)
        printf("%d %d\n", ways[i].first, ways[i].second);

    return 0;
}
