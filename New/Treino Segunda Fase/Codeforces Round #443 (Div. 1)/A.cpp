#include <bits/stdc++.h>

using namespace std;

int n;

struct q {
    char op;
    int v;
} qs[500500];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf(" %c %d", &qs[i].op, &qs[i].v);


    return 0;
}
