#include <bits/stdc++.h>

using namespace std;

int n, nums[100100];
bool prime[100100], found[100100];

int main() {
    for (int i = 2; i < 100100; i++)
        prime[i] = true;

    for (int i = 2; i < 100100; i++)
        if (prime[i])
            for (int j = 2*i; j < 100100; j += i)
                prime[j] = false;

    vector < int > divs;

    scanf("%d", &n);
    for (int i = 2; i <= n + 1; i++) {
        int sqr = sqrt(i);
        divs.clear();

        for (int j = 2; j <= sqr + 1; j++) {
            if (i % j == 0) {
                if (prime[j]) divs.push_back(j);
                if (prime[i / j]) divs.push_back(i / j);
            }
        }

        for (int v : divs)
            found[nums[v]] = true;
        for (int j = 1; j < 100100; j++)
            if (!found[j]) {
                nums[i] = j;
                break;
            }
        for (int v : divs)
            found[nums[v]] = false;
    }

    set < int > siz;
    for (int i = 2; i <= n+1; i++)
        siz.insert(nums[i]);

    printf("%d\n", siz.size());
    for (int i = 2; i <= n+1; i++) {
        if (i > 2) printf(" ");
        printf("%d", nums[i]);
    }
    printf("\n");

    return 0;
}
