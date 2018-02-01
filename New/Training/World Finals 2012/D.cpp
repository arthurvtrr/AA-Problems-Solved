#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define state vector < ll >

int n, lps[330000];
string s;

void computeLPS(string pat) {
    lps[0] = 0;
    int i = 1, len = 0;
    while (i < pat.size()) {
        if (pat[i] == pat[len]) lps[i++] = ++len;
        else if (len != 0) len = lps[len-1];
        else lps[i++] = 0;
    }
}

ll KMPSearch(string pat, string txt, int f = 0) {
    int i = 0, j = 0;
    ll ret = 0;
    while (i < txt.size()) {
        if (pat[j] == txt[i]) {
            j++; i++;
        }

        if (j == pat.size()) {
            if (!f) ret++;
            else if (i-j < f && i-1 >= f) ret++;

            j = lps[j-1];
        }
        else if (i < txt.size() && pat[j] != txt[i]) {
            if (j != 0) j = lps[j-1];
            else i++;
        }
    }
    return ret;
}

string fib[30];

int main() {
    fib[0] = "0"; fib[1] = "1";
    for (int i = 2; i < 27; i++)
        fib[i] = fib[i-1] + fib[i-2];

    int t = 1;
    while (scanf("%d", &n) != EOF) {
        cin >> s;
        computeLPS(s);
        int x = 0;
        while (fib[x].size() < s.size()) x++;

        if (x > n) printf("Case %d: 0\n", t++);
        else if (x == n) printf("Case %d: %lld\n", t++, KMPSearch(s, fib[x]));
        else {
            ll conc[2][2];
            conc[0][0] = KMPSearch(s, fib[x] + fib[x], fib[x].size());
            conc[0][1] = KMPSearch(s, fib[x] + fib[x+1], fib[x].size());
            conc[1][0] = KMPSearch(s, fib[x+1] + fib[x], fib[x+1].size());
            conc[1][1] = KMPSearch(s, fib[x+1] + fib[x+1], fib[x+1].size());

            vector < state > aux;
            aux.push_back(state({KMPSearch(s, fib[x]), 0, 0}));
            aux.push_back(state({KMPSearch(s, fib[x+1]), 1, 1}));

            int atual = x+1;
            while (atual != n) {
                int siz = aux.size();
                aux.push_back(state({aux[siz-1][0] + aux[siz-2][0] + conc[aux[siz-1][2]][aux[siz-2][1]], aux[siz-1][1], aux[siz-2][2]}));
                atual++;
            }
            printf("Case %d: %lld\n", t++, aux.back()[0]);
        }
    }

    return 0;
}
