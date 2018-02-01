#include <bits/stdc++.h>

using namespace std;

string s;
int n, txt[500500], pat[500500], lps[500500], lst[500500], app[30];

void process() {
    int len = 0, i = 1;
    lps[0] = 0;

    while (i < n) {
        if ((lst[i] > len? -1 : lst[i]) == lst[len]) lps[i++] = ++len;
        else {
            if (len != 0) len = lps[len-1];
            else lps[i++] = 0;
        }
    }
}

int KMPSearch() {
    int ret = 0, len = s.size(), i = 0, j = 0;

    while (i < len) {
        if (lst[j] == (txt[i] > j? -1 : txt[i])) {
            j++; i++;
        }

        if (j == n) {
            ret++;
            j = lps[j-1];
        }
        else if (i < len && lst[j] != (txt[i] > j? -1 : txt[i])) {
            if (j != 0) j = lps[j-1];
            else i = i+1;
        }
    }
    return ret;
}

int main() {
    while (cin >> s) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &pat[i]);

        memset(app, -1, sizeof app);

        for (int i = 0; i < n; i++) {
            lst[i] = (app[pat[i]] == -1? -1 : i - app[pat[i]]);
            app[pat[i]] = i;
        }
        process();

        memset(app, -1, sizeof app);

        for (int i = 0; i < s.size(); i++) {
            txt[i] = (app[s[i] - 'a'] == -1? -1 : i - app[s[i] - 'a']);
            app[s[i] - 'a'] = i;
        }

        printf("%d\n", KMPSearch());
    }
    return 0;
}
