#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int x;
    while (scanf("%d", &x) != EOF) {
        int freq[] = {0, 0, 0, 0, 0};
        bool comp = true;
        freq[0] += x;
        for (int i = 1; i < 5; i++) {
            scanf("%d", &x);
            freq[i] += x;
        }
        for (int i = 0; i < 5; i++) {
            scanf("%d", &x);
            freq[i] += x;
        }
        for (int i = 0; i < 5; i++)
            if (freq[i] != 1) comp = false;
        if (comp) printf("Y\n");
        else printf("N\n");
    }
    return 0;
}
