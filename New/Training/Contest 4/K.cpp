#include <bits/stdc++.h>

using namespace std;

string s;

int main() {
    cin >> s;
    for (int i = 1; i <= 20; i++) {
        set < string > diff;

        for (int j = 0; j < s.size() - i + 1; j++) {
            string aux = "";
            for (int k = 0; k < i; k++)
                aux += s[j+k];
            diff.insert(aux);
        }

        if (diff.size() != (1 << i)) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}

