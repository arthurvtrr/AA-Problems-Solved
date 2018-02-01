#include <bits/stdc++.h>

using namespace std;

#define N 200100
#define LOGN 50

//Suffix Array + LCP

struct suffix {
    int index;
    int rank[2];
} suffixes[N];

int ind[N], suffixArr[N], lcp[N], invSuff[N];

int cmp(struct suffix a, struct suffix b) {
    if (a.rank[0] == b.rank[0])
        return a.rank[1] < b.rank[1];
    return a.rank[0] < b.rank[0];
}

void buildSuffixArray(string txt, int n) {
    for (int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i];
        suffixes[i].rank[1] = ((i+1) < n)? (txt[i + 1]): -1;
    }

    sort(suffixes, suffixes+n, cmp);

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
            suffixes[i].rank[1] = (nextindex < n)? suffixes[ind[nextindex]].rank[0]: -1;
        }

        sort(suffixes, suffixes+n, cmp);
    }

    for (int i = 0; i < n; i++)
        suffixArr[i] = suffixes[i].index;
}

void kasai(string txt, int n) {
    for (int i = 0; i < n; i++)
        invSuff[suffixArr[i]] = i;

    int k = 0;

    for (int i = 0; i < n; i++) {
        if (invSuff[i] == n-1) {
            k = 0;
            continue;
        }

        int j = suffixArr[invSuff[i]+1];

        while (i+k<n && j+k<n && txt[i+k]==txt[j+k] && txt[i+k] != ' ' && txt[j+k] != ' ')
            k++;

        lcp[invSuff[i]] = k;

        if (k > 0) k--;
    }
}

//RMQ

int rmq[N][LOGN], LOG[N];

void processRMQ() {
    for (int i = 0, ret = 0; i < N; i++)
        LOG[i] = ret += (i > 1 && !(i&(i-1)));

    for (int i = 0; i < N; i++)
        rmq[i][0] = i;

    for (int j = 1; 1 << j < N; j++)
        for (int i = 0; i + (1 << j) - 1 < N; i++)
            if (lcp[rmq[i][j - 1]] < lcp[rmq[i + (1 << (j - 1))][j - 1]])
                rmq[i][j] = rmq[i][j - 1];
            else
                rmq[i][j] = rmq[i + (1 << (j - 1))][j - 1];
}

int RMQquery(int i, int j) {
    int k = LOG[j - i + 1];
    return min(lcp[rmq[i][k]], lcp[rmq[j - (1 << k) + 1][k]]);
}
