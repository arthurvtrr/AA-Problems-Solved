#include <bits/stdc++.h>

using namespace std;

string s;
set < char > diff;

int main() {
    getline(cin, s);
    for (int i = 0; i < s.size(); i++)
        if (s[i] >= 'a' && s[i] <= 'z')
            diff.insert(s[i]);

    printf("%d\n", diff.size());

    return 0;
}


