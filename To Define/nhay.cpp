#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

string needle, haystack;
int reset[5000050], l;
vector < int > appears;

void preprocess() {
    int i = 0, j = -1;
    reset[0] = -1;
    while (i < l) {
        while (j >= 0 && needle[i] != needle[j])
            j = reset[j];
        reset[++i] = ++j;
    }
}

void searchSol() {
    int i = 0, j = 0;
    while (i < haystack.size()) {
        while (j >= 0 && haystack[i] != needle[j])
            j = reset[j];
        i++; j++;

        if (j == l) {
            appears.push_back(i-l);
            j = reset[j];
        }
    }
}

int main() {
    while (scanf("%d", &l) != EOF) {
        memset(reset, 0, sizeof reset);
        appears.clear();

        cin >> needle;
        cin >> haystack;

        preprocess();
        searchSol();

        sort(appears.begin(), appears.end());
        for (int pos : appears)
            printf("%d\n", pos);
        printf("\n");
    }
    return 0;
}
