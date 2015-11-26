#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int n, m;
    while (1) {
        scanf("%d %d", &n, &m);
        if (n == 0 && m == 0) break;
        string sol = "";
        while (1) {
            cout << m << "\n";
            if (m % 26 == 0) sol += 'Z';
            else {
                int x = m % 26;
                sol += (x - 1) + 'A';
            }
            if (m <= 26) break;
            m /= 26;
            m -= 1;
        }
        sol.reserve();
        cout << sol << "\n";
    }
    return 0;
}
