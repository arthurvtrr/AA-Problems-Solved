#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX 1010

struct suffix {
    int index;
    int rank[2];
} suffixes[MAX];

char s[MAX];
int n;
int Phi[MAX];
int PLCP[MAX];
int LCP[MAX];
int SA[MAX];

int cmp(struct suffix a, struct suffix b) {
    return (a.rank[0] == b.rank[0])? (a.rank[1] < b.rank[1] ?1: 0):
               (a.rank[0] < b.rank[0] ?1: 0);
}

void buildSA() {
    for (int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].rank[0] = s[i];
        suffixes[i].rank[1] = i+1 < n ? s[i + 1] : -1;
    }

    sort(suffixes, suffixes+n, cmp);

    int ind[n];

    for (int k = 4; k < 2*n; k = k*2) {
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;

        for (int i = 1; i < n; i++) {
            if (suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i-1].rank[1]) {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }

        for (int i = 0; i < n; i++) {
            int nextindex = suffixes[i].index + k/2;
            suffixes[i].rank[1] = nextindex < n ? suffixes[ind[nextindex]].rank[0]: -1;
        }

        sort(suffixes, suffixes+n, cmp);
    }

    for (int i = 0; i < n; i++)
        SA[i] = suffixes[i].index;
}

void computeLCP() {
    int i, L;
    Phi[SA[0]] = -1;
    for (i = 1; i < n; i++)
        Phi[SA[i]] = SA[i-1];
    for (i = L = 0; i < n; i++) {
        if (Phi[i] == -1) {
            PLCP[i] = 0;
            continue;
        }
        while (s[i + L] == s[Phi[i] + L]) L++;
        PLCP[i] = L;
        L = max(L-1, 0);
    }
    for (i = 0; i < n; i++)
        LCP[i] = PLCP[SA[i]];
}

int main() {
    int t;
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%s", s);
        n = strlen(s);
        buildSA();
        computeLCP();
        int sumLCP = 0;
        for (int i = 0; i < n; i++)
            sumLCP += LCP[i];
        int sol = (n+1) * n / 2 - sumLCP;
        printf("%d\n", sol);
    }
    return 0;
}
