#include <bits/stdc++.h>

using namespace std;

string s;

int main() {
    while (cin >> s) {
        int pont[2] = {0, 0}, atual = 0, t = -1, fim = -1;
        for (int i = 0; i < 10; i++) {
            pont[atual] += s[i] == '1';
            if (pont[atual] > pont[1 - atual] + 5 - i / 2 - 1 + (i % 2 == 0)) {
                t = atual; fim = i;
                break;
            }
            else if (pont[1 - atual] > pont[atual] + 5 - i / 2 - 1) {
                t = 1 - atual; fim = i;
                break;
            }
            atual = 1 - atual;
        }
        if (fim != -1) {
            printf("TEAM-%c %d\n", 'A' + t, fim+1);
        }
        else {
            fim = -1;
            for (int i = 10; i < 20; i += 2) {
                pont[0] += s[i] == '1';
                pont[1] += s[i+1] == '1';
                if (pont[0] != pont[1]) {
                    fim = i+2;
                    break;
                }
            }
            if (fim == -1) printf("TIE\n");
            else if (pont[0] > pont[1]) printf("TEAM-A %d\n", fim);
            else printf("TEAM-B %d\n", fim);
        }
    }
    return 0;
}
