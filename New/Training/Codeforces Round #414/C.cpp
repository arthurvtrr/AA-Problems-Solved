#include <bits/stdc++.h>

using namespace std;

string a, b, ans;
int conta[30], contb[30];

int main() {
    cin >> a >> b;
    sort(a.begin(), a.end());
    sort(b.rbegin(), b.rend());

    int siza = a.size(), sizb = b.size();

    for (int i = 0; i < siza / 2 + (siza % 2); i++)
        conta[a[i] - 'a']++;
    for (int i = 0; i < sizb / 2; i++)
        contb[b[i] - 'a']++;

    ans = "";
    for (int i = 0; i < a.size(); i++)
        ans += "?";

    int posa = 0, posb = (int)a.size() - 1, turn = 0;

    while (posa <= posb) {
        int mina = 0, maxa = 29, minb = 0, maxb = 29;

        if (posa == posb) {
            if (turn == 0) {
                while (conta[mina] == 0) mina++;
                ans[posa] = mina + 'a';
            }
            else {
                while (contb[minb] == 0) minb++;
                ans[posa] = minb + 'a';
            }
            break;
        }

        while (conta[mina] == 0) mina++;
        while (conta[maxa] == 0) maxa--;

        while (contb[minb] == 0) minb++;
        while (contb[maxb] == 0) maxb--;

        if (turn == 0) {
            if (mina > maxb) {
                ans[posb] = maxa + 'a';
                posb--;
                conta[maxa]--;
            }
            else {
                ans[posa] = mina + 'a';
                posa++;
                conta[mina]--;
            }
        }
        else {
            if (mina > maxb) {
                ans[posb] = minb + 'a';
                posb--;
                contb[minb]--;
            }
            else {
                ans[posa] = maxb + 'a';
                posa++;
                contb[maxb]--;
            }
        }
        turn = 1 - turn;
    }

    cout << ans << endl;
    return 0;
}

