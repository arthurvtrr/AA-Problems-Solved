#include <bits/stdc++.h>

using namespace std;

int h1, a1, c1, h2, a2;

int main() {
    scanf("%d %d %d %d %d", &h1, &a1, &c1, &h2, &a2);
    vector < string > ans;
    while (h2 > 0) {
        if (h2 <= a1) { ans.push_back("STRIKE"); break; }

        if (h1 <= a2) { ans.push_back("HEAL"); h1 += c1; }
        else { ans.push_back("STRIKE"); h2 -= a1; }
        h1 -= a2;
    }
    printf("%d\n", ans.size());
    for (string s : ans)
        cout << s << endl;
    return 0;
}
