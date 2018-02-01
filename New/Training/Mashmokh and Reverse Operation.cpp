#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pll pair < ll, ll >

int n, m, q, nums[2001000], cop[2001000];
pll sum[30];
vector < ll > invs[30][2];
bool inv;

void mSort(int a, int b, int c, int siz) {
    int ini = a, mid = b+1, aux = 0;
    int auxV[c-a+1];

    int ind = invs[siz+1][inv].size();
    ll inv1 = invs[siz][inv][2*ind] + invs[siz][inv][2*ind+1];

    while (ini <= b && mid <= c) {
        if (nums[ini] <= nums[mid]) {
            auxV[aux] = nums[ini];
            ini++;
        }
        else {
            auxV[aux] = nums[mid];
            mid++; inv1 += b - ini + 1;
        }
        aux++;
    }

    invs[siz+1][inv].push_back(inv1);

    while (ini <= b) auxV[aux++] = nums[ini++];
    while (mid <= c) auxV[aux++] = nums[mid++];

    for (int i = a; i <= c; i++)
        nums[i] = auxV[i-a];
}

void mergeSort(int ini, int fim, int siz) {
    if (ini < fim) {
        int meio = (ini + fim) / 2;
        mergeSort(ini, meio, siz-1);
        mergeSort(meio+1, fim, siz-1);
        mSort(ini, meio, fim, siz-1);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 1 << n; i++) {
        scanf("%d", &nums[i]);
        cop[(1 << n) - i - 1] = nums[i];
    }

    inv = false;
    for (int i = 0; i < 1 << n; i++) invs[0][0].push_back(0);
    mergeSort(0, (1 << n)-1, n);

    inv = true;
    for (int i = 0; i < 1 << n; i++) nums[i] = cop[i];
    for (int i = 0; i < 1 << n; i++) invs[0][1].push_back(0);
    mergeSort(0, (1 << n)-1, n);

    for (int i = 1; i <= n; i++) {
        ll a = 0, b = 0;
        for (int j = 0; j < invs[i][0].size(); j++) {
            a += invs[i][0][j];
            b += invs[i][1][j];
        }
        sum[i] = pll(a, b);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &q);
        if (q) {
            for (int j = q; j > 0; j--)
                swap(sum[j].first, sum[j].second);

            for (int j = q+1; j <= n; j++) {
                sum[j].first += sum[q].first - sum[q].second;
                sum[j].second += sum[q].second - sum[q].first;
            }
        }
        printf("%lld\n", sum[n].first);
    }

    return 0;
}
