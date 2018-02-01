#include <bits/stdc++.h>

using namespace std;

int k, ans[100100];

int main() {
    scanf("%d", &k);
    int pos = 0, aux = 0;
    while (aux < k) {
        ans[pos] = 8;
        pos++;
        aux += 7;
    }

    bool valid = true;

    if (aux - k == 1) {
        if (pos == 1) ans[pos-1] = 0;
        else ans[pos-1] = 6;
    }
    else if (aux - k == 2) ans[pos-1] = 2;
    else if (aux - k == 3) {
        if (pos == 1) ans[pos-1] = 4;
        else { ans[pos-1] = 2; ans[pos-2] = 0; }
    }
    else if (aux - k == 4) {
        if (pos == 1) ans[pos-1] = 7;
        else if (pos == 2) { ans[pos-1] = 2; ans[pos-2] = 2; }
        else { ans[pos-1] = 2; ans[pos-2] = 0; ans[pos-3] = 0; }
    }
    else if (aux - k == 5) ans[pos-1] = 1;
    else if (aux - k == 6) {
        if (pos == 1) valid = false;
        else { ans[pos-1] = 1; ans[pos-2] = 0; }
    }

    if (!valid) printf("-1\n");
    else {
        for (int i = pos-1; i >= 0; i--)
            printf("%d", ans[i]);
        printf("\n");
    }

    return 0;
}
