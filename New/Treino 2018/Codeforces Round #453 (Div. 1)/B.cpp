#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n;

int main() {
    scanf("%d", &n);

    vector < int > a, b;
    a.push_back(1); b.push_back(1);
    for (int k = 0; k < n; k++) {
        int x = k % 3;
        a.push_back(x-1);
    }

    for (int k = 0; k < n-1; k++) {
        if (k % 2 == 0) b.push_back(0);
        else b.push_back(a[k+1]);
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    printf("%d\n", n);
    for (int k = 0; k < a.size(); k++) {
        if (k) printf(" ");
        printf("%d", a[k]);
    }
    printf("\n");

    printf("%d\n", n-1);
    for (int k = 0; k < b.size(); k++) {
        if (k) printf(" ");
        printf("%d", b[k]);
    }
    printf("\n");

    return 0;
}
