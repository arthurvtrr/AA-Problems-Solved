#include <bits/stdc++.h>

using namespace std;

int tst, contA[300], contB[300];
string s, t;

int main() {
    scanf("%d", &tst);
    while (tst--) {
        cin >> s >> t;
        memset(contA, 0, sizeof contA);
        memset(contB, 0, sizeof contB);

        for (int i = 0; i < s.size(); i++)
            contA[s[i]]++;
        for (int i = 0; i < t.size(); i++)
            contB[t[i]]++;

        int maxi = 0, ot = 0;
        for (int i = 0; i < 300; i++) {
            if (contA[i] > 0 && contB[i] == 0)
                maxi = max(maxi, contA[i]);
            else if (contA[i] == 0 && contB[i] > 0)
                ot = max(ot, contB[i]);
        }

        if (maxi > 1) printf("A\n");
        else if (maxi == 1 && ot == 0) printf("A\n");
        else printf("B\n");
    }

    return 0;
}
