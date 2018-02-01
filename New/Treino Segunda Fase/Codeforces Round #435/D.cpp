#include <bits/stdc++.h>

using namespace std;

int n, x, aux;

int main() {
    scanf("%d", &n);

    int pos0, pos1;

    string s = "";
    for (int i = 0; i < n; i++)
        s += "0";
    cout << "? " << s << "\n";
    fflush(stdout);
    scanf("%d", &aux);

    s[0] = '1';
    cout << "? " << s << "\n";
    fflush(stdout);
    scanf("%d", &x);

    if (x == aux+1) {
        pos0 = 1;
        s = "";
        for (int i = 0; i < n; i++)
            s += "1";
        cout << "? " << s << "\n";
        fflush(stdout);
        scanf("%d", &aux);

        int ini = 0, fim = n-1;
        while (ini <= fim) {
            int mid = (ini + fim) / 2;
            string cop = s;
            for (int i = 0; i <= mid; i++)
                cop[i] = '0';

            cout << "? " << cop << "\n";
            fflush(stdout);
            scanf("%d", &x);

            if (x == aux - mid - 1) ini = mid+1;
            else fim = mid-1;
        }

        pos1 = ini+1;
        printf("! %d %d\n", pos0, pos1);
        fflush(stdout);
    }
    else {
        pos1 = 1;
        s = "";
        for (int i = 0; i < n; i++)
            s += "0";
        cout << "? " << s << "\n";
        fflush(stdout);
        scanf("%d", &aux);

        int ini = 0, fim = n-1;
        while (ini <= fim) {
            int mid = (ini + fim) / 2;
            string cop = s;
            for (int i = 0; i <= mid; i++)
                cop[i] = '1';

            cout << "? " << cop << "\n";
            fflush(stdout);
            scanf("%d", &x);

            if (x == aux - mid - 1) ini = mid+1;
            else fim = mid-1;
        }

        pos0 = ini+1;
        printf("! %d %d\n", pos0, pos1);
        fflush(stdout);
    }

    return 0;
}

