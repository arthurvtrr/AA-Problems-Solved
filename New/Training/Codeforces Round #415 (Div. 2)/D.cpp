#include <bits/stdc++.h>

using namespace std;

int n, k;
string s;

int main() {
    scanf("%d %d", &n, &k);

    int ini = 0, fim = n;
    while (fim - ini > 1) {
        int mid = (ini + fim) / 2;
        printf("1 %d %d\n", mid, mid+1);
        fflush(stdout);
        cin >> s;

        if (s == "TAK") fim = mid;
        else ini = mid;
    }
    int a = ini+1;

    int b, c;

    ini = 0, fim = a;
    while (fim - ini > 1) {
        int mid = (ini + fim) / 2;
        printf("1 %d %d\n", mid, mid+1);
        fflush(stdout);
        cin >> s;

        if (s == "TAK") fim = mid;
        else ini = mid;
    }
    b = ini+1;

    ini = a, fim = n+1;
    while (fim - ini > 1) {
        int mid = (ini + fim) / 2;
        printf("1 %d %d\n", mid, min(n, mid+1));
        fflush(stdout);
        cin >> s;

        if (s == "TAK") fim = mid;
        else ini = mid;
    }
    c = ini+1;

    if (b < a) printf("2 %d %d\n", a, b);
    else printf("2 %d %d\n", a, c);
    fflush(stdout);

    return 0;
}
