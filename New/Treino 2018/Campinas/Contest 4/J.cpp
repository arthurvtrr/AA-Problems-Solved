#include <bits/stdc++.h>

using namespace std;

bool neigh[30][30], vog[30];
char let[30];

vector < string > words;

int main() {
    freopen("javanese.in", "r", stdin);
    freopen("javanese.out", "w", stdout);

    string s;
    while (cin >> s) {
        words.push_back(s);
        for (int i = 0; i < s.size(); i++) {
            if (i) neigh[s[i] - 'A'][s[i-1] - 'A'] = true;
            if (i+1 < s.size()) neigh[s[i] - 'A'][s[i+1] - 'A'] = true;
        }
    }

    for (int a = 0; a < 26; a++)
        for (int b = a+1; b < 26; b++)
            for (int c = b+1; c < 26; c++)
                for (int d = c+1; d < 26; d++)
                    for (int e = d+1; e < 26; e++) {
                        memset(vog, false, sizeof vog);
                        vog[a] = vog[b] = vog[c] = vog[d] = vog[e] = true;

                        bool v = true;
                        for (int i = 0; i < 26; i++) {
                            if (vog[i]) {
                                for (int j = 0; j < 26; j++)
                                    if (neigh[i][j] && vog[j])
                                        v = false;
                            }
                            else {
                                for (int j = 0; j < 26; j++)
                                    if (neigh[i][j] && !vog[j])
                                        v = false;
                            }
                        }

                        if (v) {
                            let[a] = 'A', let[b] = 'E', let[c] = 'I', let[d] = 'O', let[e] = 'U';
                            char aux = 'B';
                            for (int i = 0; i < 26; i++)
                                if (!vog[i]) {
                                    while (aux == 'A' || aux == 'E' || aux == 'I' || aux == 'O' || aux == 'U') aux++;
                                    let[i] = aux++;
                                }

                            for (int i = 0; i < words.size(); i++) {
                                if (i) printf(" ");
                                for (int j = 0; j < words[i].size(); j++)
                                    printf("%c", let[words[i][j] - 'A']);
                            }
                            printf("\n");
                            return 0;
                        }
                    }

    printf("impossible\n");
    return 0;
}
