#include <bits/stdc++.h>

using namespace std;

int t, n, nums[110];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);

        bool valid = true;
        int nxt = 0, ini = 0, fim = n-1;
        while (ini < fim) {
            if (nums[ini] != nums[fim]) {
                valid = false;
                break;
            }
            else {
                if (nums[ini] == nxt+1) nxt++;
                else if (nums[ini] != nxt) {
                    valid = false;
                    break;
                }
                ini++; fim--;
            }
        }
        if (nums[ini] != 7) valid = false;

        if (valid) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}
