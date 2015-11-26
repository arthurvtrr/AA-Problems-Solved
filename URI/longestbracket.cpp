#include <stdio.h>
#include <string>
#include <stack>
#include <iostream>
#include <string.h>

using namespace std;

int main() {
    string s;
    cin >> s;
    int x = s.size();
    int d[x], c[x];
    memset(d, -1, 4*x);
    memset(c, -1, 4*x);
    stack < int > open;

    for (int i = 0; i < x; i++) {
        if (s[i] == '(')
            open.push(i);

        if (s[i] == ')' && open.empty()) {
            d[i] = -1;
            c[i] = -1;
        }
        else if (s[i] == ')') {
            d[i] = open.top();
            open.pop();

            if (s[d[i] - 1] == ')' && c[d[i] - 1] != -1)
                c[i] = c[d[i] - 1];
            else
                c[i] = d[i];
        }
    }

    int r = 0, times = 1;

    for (int i = 0; i < x; i++) {
        if (c[i] != -1 && i - c[i] + 1 > r) {
            r = i - c[i] + 1;
            times = 1;
        }
        else if (c[i] != -1 && i - c[i] + 1 == r)
            times++;
    }

    printf("%d %d\n", r, times);

    return 0;
}
