#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int nums[2200];

struct pal {
    int siz = 0;
    int num = 0;
} L[2200][2200];

bool cmp(pal a, pal b) {
    if (a.num > b.num)
        return true;
    if (a.num < b.num)
        return false;
    return a.siz > b.siz;
}

pal maxp(pal a, pal b) {
    if (a.num > b.num)
        return a;
    if (a.num < b.num)
        return b;
    if (a.siz > b.siz)
        return a;
    return b;
}

vector < pal > palis;

int lps(char *str) {
    int n = strlen(str);
    palis.clear();

    for (int i = 0; i < n; i++) {
        L[i][i].siz = 1;
        L[i][i].num = nums[i]? 1 : 0;
        palis.push_back(L[i][i]);
    }

    for (int cl = 2; cl <= n; cl++) {
        for (int i = 1; i <= n - cl + 1; i++) {
            int j = i + cl - 1;
            if (str[i] == str[j]) {
                L[i][j].siz = 2 + L[i+1][j-1].siz;
                L[i][j].num = nums[i]? 1 : 0;
                L[i][j].num += nums[j]? 1 : 0;
                L[i][j].num += L[i+1][j-1].num;
            }
            L[i][j] = maxp(L[i][j], maxp(L[i+1][j], L[i][j-1]));
            palis.push_back(L[i][j]);
        }
    }

    sort(palis.begin(), palis.end(), cmp);
    return palis[0].siz;
}

int main() {
    char s[2200];
    int n, x;
    while (scanf("%s", s) != EOF) {
        for (int i = 0; i < 2200; i++) nums[i] = 0;

        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            nums[x-1]++;
        }

        int sol = lps(s);
        printf("%d\n", sol);
    }
    return 0;
}
