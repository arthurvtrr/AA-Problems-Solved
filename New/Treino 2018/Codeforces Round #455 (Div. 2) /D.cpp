#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

string s;
int nxt[1001000], lst[1001000];

int main() {
    cin >> s;
    for (int i = 0; i < 1001000; i++)
        nxt[i] = i+1;
    for (int i = 0; i < 1001000; i++)
        lst[i] = i-1;

    //Compress the string, aux stores pairs of (letter, times it appear consecutively)
    vector < pii > aux;
    for (int i = 0; i < s.size(); i++) {
        int pos = i;
        while (pos+1 < s.size() && s[pos+1] == s[i]) pos++;
        pii x = pii(s[i] - 'a', pos - i + 1);
        aux.push_back(x);
        i = pos;
    }

    int ans = 0, siz = aux.size();
    while (siz > 1) {
        //indexes 0 and aux.size() + 1 are used just to represent borders
        //that's why we start at nxt[0]
        int pos = nxt[0], ult = 0;

        while (pos <= aux.size() + 1) {
            bool to_remove = false;

            if (pos <= aux.size()) {
                if (lst[pos] != 0) aux[pos-1].second--;
                if (nxt[pos] != aux.size() + 1) aux[pos-1].second--;
                if (aux[pos-1].second < 1) to_remove = true;
            }

            if (!to_remove) {
                if (lst[pos] != ult) {
                    lst[pos] = ult;
                    nxt[ult] = pos;
                }
                //merge pairs with same letter
                if (pos <= aux.size() && ult > 0 && aux[pos-1].first == aux[ult-1].first) {
                    aux[ult-1].second += aux[pos-1].second;
                    nxt[ult] = nxt[pos];
                    lst[nxt[pos]] = ult;
                    siz--;
                }
                else ult = pos;
            }
            else siz--;

            pos = nxt[pos];
        }
        ans++;
    }

    printf("%d\n", ans);
    return 0;
}
