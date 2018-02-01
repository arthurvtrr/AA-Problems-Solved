#include <bits/stdc++.h>

using namespace std;

int n, bef[1010], after[1010];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &bef[i], &after[i]);

    int type = 0;
    for (int i = 0; i < n; i++)
        if (bef[i] != after[i]) type = 1;

    if (type == 1) printf("rated\n");
    else {
        bool unr = false;
        for (int i = 0; i < n-1; i++)
            if (bef[i] < bef[i+1])
                unr = true;

        if (unr) printf("unrated\n");
        else printf("maybe\n");
    }
    return 0;
}
