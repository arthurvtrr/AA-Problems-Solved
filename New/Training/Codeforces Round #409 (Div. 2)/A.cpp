#include <bits/stdc++.h>

using namespace std;

string s;

int main() {
    cin >> s;
    int ans = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == 'V') s[i] = 'K';
        else s[i] = 'V';

        int cont = 0;
        for (int j = 0; j < (int)s.size() -1; j++)
            if (s[j] == 'V' && s[j+1] == 'K')
                cont++;
        ans = max(ans, cont);

        if (s[i] == 'V') s[i] = 'K';
        else s[i] = 'V';
    }

    int cont = 0;
    for (int j = 0; j < (int)s.size() -1; j++)
        if (s[j] == 'V' && s[j+1] == 'K')
            cont++;
    ans = max(ans, cont);

    printf("%d\n", ans);

    return 0;
}
