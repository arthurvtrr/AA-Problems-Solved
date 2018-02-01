#include <bits/stdc++.h>

using namespace std;

int k, n;
string words[2550];
bool rep, mis[2550][5050];
int quant[2550], cnt[2550][30];
vector < int > test;

void insere(int x) {
    for (int el : test)
        if (el == x)
            return;
    test.push_back(x);
}

int main() {
    scanf("%d %d", &k, &n);
    for (int i = 0; i < k; i++) {
        cin >> words[i];
        for (char c : words[i]) {
            cnt[i][c - 'a']++;
            if (cnt[i][c - 'a'] > 1) rep = true;
        }
    }

    for (int i = 0; i < 30; i++) {
        bool v = true;
        for (int j = 0; j < k; j++)
            if (cnt[j][i] != cnt[0][i])
                v = false;
        if (!v) {
            printf("-1\n");
            exit(0);
        }
    }

    string aux = words[0];

    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++) {
            swap(aux[i], aux[j]);

            if (i == 0 && j == 1) {
                bool valid = true;
                for (int a = 0; a < k; a++) {
                    for (int b = 0; b < n; b++)
                        if (aux[b] != words[a][b]) {
                            mis[a][b] = true;
                            quant[a]++;
                        }

                    if (rep && quant[a] != 0 && quant[a] != 2) valid = false;
                    else if (!rep && quant[a] != 2) valid = false;
                }

                if (valid) {
                    cout << aux << endl;
                    exit(0);
                }
            }
            else {
                insere(i); insere(j);

                bool valid = true;
                for (int a = 0; a < k; a++) {
                    for (int v : test) {
                        if (mis[a][v]) {
                            mis[a][v] = false;
                            quant[a]--;
                        }

                        if (aux[v] != words[a][v]) {
                            mis[a][v] = true;
                            quant[a]++;
                        }
                    }

                    if (rep && quant[a] != 0 && quant[a] != 2) valid = false;
                    else if (!rep && quant[a] != 2) valid = false;
                }

                if (valid) {
                    cout << aux << endl;
                    exit(0);
                }

                test.clear();
            }

            insere(i); insere(j);
            swap(aux[i], aux[j]);
        }

    printf("-1\n");
    return 0;
}
