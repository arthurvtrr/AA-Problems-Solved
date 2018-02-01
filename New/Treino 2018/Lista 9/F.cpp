#include <bits/stdc++.h>

using namespace std;

int x;

int main() {
    scanf("%d", &x);

    string ans = "";
    int lst = 0;
    while (x) {
        if (x & 1) { ans += '1'; x--; }
        else {
            if (x/2 + 2 < x) {
                ans += '[';
                lst++;
                x = x/2;
            }
            else {
                for (int i = 0; i < x; i++)
                    ans += '1';
                break;
            }
        }
    }
    for (int i = 0; i < lst; i++)
        ans += ']';

    cout << ans << endl;

    return 0;
}
