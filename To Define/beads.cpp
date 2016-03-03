#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

#define MAX 20020
char s[MAX];
int n;
int RA[MAX], tempRA[MAX];
int SA[MAX], tempSA[MAX];
int freq[MAX];

void countingSort(int k) {
    int sum = 0, maxi = max(300, n);
    memset(freq, 0, sizeof freq);
    for (int i = 0; i < n; i++)
        freq[i + k < n ? RA[i + k] : 0]++;
    for (int i = 0; i < maxi; i++) {
        int t = freq[i];
        freq[i] = sum;
        sum += t;
    }
    for (int i = 0; i < n; i++)
        tempSA[freq[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
    for (int i = 0; i < n; i++)
        SA[i] = tempSA[i];
}

void constructSA() {
    int r;
    for (int i = 0; i < n; i++)
        RA[i] = s[i];
    for (int i = 0; i < n; i++)
        SA[i] = i;
    for (int k = 1; k < n; k <<= 1) {
        countingSort(k);
        countingSort(0);
        tempRA[SA[0]] = r = 0;
        for (int i = 1; i < n; i++) {
            if (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k])
                tempRA[SA[i]] = r;
            else
                tempRA[SA[i]] = ++r;
        }
        for (int i = 0; i < n; i++)
            RA[i] = tempRA[i];
        if (RA[SA[n-1]] == n-1)
            break;
    }
}

int main() {
    int t;
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%s", s);
        char s1[20020];
        strcpy(s1, s);
        strcat(s, s1);
        strcat(s, "$");
        n = strlen(s);
        constructSA();
        for (int i = 0; i < n; i++)
            printf("%d - %d\n", SA[i], RA[i]);
        for (int i = 0; i < n; i++)
            if (SA[i] < n / 2) {
                printf("%d\n", SA[i] + 1);
                break;
            }
    }
    return 0;
}

