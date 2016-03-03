#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    int num7 = 0, num4 = 0;
    bool found = false;

    if (n % 7 == 0) {
        found = true;
        num7 = n / 7;
    }
    else {
        num4++;
        while (num4 * 4 <= n) {
            if ((n - 4*num4) % 7 == 0) {
                found = true;
                break;
            }
            num4++;
        }
    }

    if (!found) printf("-1\n");
    else {
        string s = "";
        if (num7 == 0) num7 = (n - 4 * num4) / 7;
        while (num4--) s += '4';
        while (num7--) s += '7';
        cout << s << "\n";
    }
    return 0;
}
