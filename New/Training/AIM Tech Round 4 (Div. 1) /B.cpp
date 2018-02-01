#include <bits/stdc++.h>

using namespace std;

int n, s, x, a, b, nums[50500], nxt[50500];

typedef unsigned long long ull;
ull seed = 0;
ull my_rand() {
    seed ^= ull(102938711);
    seed *= ull(109293);
    seed ^= seed >> 13;
    seed += ull(1357900102873);
    return seed;
}

int main() {
    srand(time(NULL));
    seed = rand();

    scanf("%d %d %d", &n, &s, &x);

    memset(nums, -1, sizeof nums);

    printf("? %d\n", s);
    fflush(stdout);
    scanf("%d %d", &a, &b);
    nums[s] = a;
    nxt[s] = b;

    if (a >= x) {
        printf("! %d\n", a);
        fflush(stdout);
        exit(0);
    }

    vector < int > aux;
    for (int i = 1; i <= n; i++)
        if (i != s)
            aux.push_back(i);

    int lft = 1750;
    while (lft && aux.size() > 0) {
        int pos = my_rand() % ((int)aux.size());
        printf("? %d\n", aux[pos]);
        fflush(stdout);
        scanf("%d %d", &a, &b);
        nums[aux[pos]] = a;
        nxt[aux[pos]] = b;
        aux.erase(aux.begin() + pos);
        lft--;
    }

    int maxi = s;
    for (int i = 1; i <= n; i++)
        if (nums[i] < x && nums[i] > nums[maxi])
            maxi = i;

    int atual = nxt[maxi];

    if (atual == -1) {
        printf("! -1\n");
        fflush(stdout);
        exit(0);
    }

    for (int i = 0; i < 245; i++) {
        printf("? %d\n", atual);
        fflush(stdout);
        scanf("%d %d", &a, &b);
        nums[atual] = a;
        nxt[atual] = b;

        if (a >= x) {
            printf("! %d\n", a);
            fflush(stdout);
            exit(0);
        }
        else if (b == -1) {
            printf("! -1\n");
            fflush(stdout);
            exit(0);
        }

        atual = b;
    }
    printf("! -1\n");
    fflush(stdout);

    return 0;
}

