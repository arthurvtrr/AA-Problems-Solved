#include <stdio.h>
#include <algorithm>

using namespace std;

struct inst {
    bool appear[1100];
    vector < int > cont;
    int num = 0;
} insts[1100];

bool cmp(inst x, inst y) {
    return x.num > y.num;
}

int main() {
    int n, m, x, y;

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        for (int j = x; j <= y; j += x) {
            insts[j].appear[i] = true;
            insts[j].num++;
            insts[j].cont.push_back(i);
        }
    }

    int sol = 0;
    while (m--) {
        sort(insts, insts+1100, cmp);
        sol += insts[0].num;
        insts[0].num = 0;
        for (int enemy : insts[0].cont) {
            for (int j = 1; j < 1100; j++) {
                if (insts[j].appear[enemy]) {
                    insts[j].num--;
                    insts[j].appear[enemy] = false;
                }
            }
        }
    }

    printf("%d\n", sol);
    return 0;
}
