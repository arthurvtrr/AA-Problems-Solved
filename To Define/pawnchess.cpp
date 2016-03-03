#include <stdio.h>

using namespace std;

int main() {
    char table[10][10];
    for (int i = 0; i < 8; i++)
        scanf("%s", table[i]);

    int fA = 10, lB = 10;
    for (int i = 0; i < 8; i++) {
        bool fW = false, fB = false;
        int x = 10;
        for (int j = 0; j < 8; j++) {
            if (table[j][i] == 'W') {
                if (!fW && !fB && fA > j) fA = j;
                if (!fB) fW = true;
                x = 10;
            }
            else if (table[j][i] == 'B') {
                x = 7-j;
                fB = true;
            }
        }
        if (x < lB) lB = x;
    }

    if (fA <= lB) printf("A\n");
    else printf("B\n");
    return 0;
}
