#include <bits/stdc++.h>

using namespace std;

int n, nums[110], k;
set < pii > edges;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);
    scanf("%d", &k);

    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            edges.insert(pii(i, j));

    vector < int > lft;
    for (int i = 0; i < n; i++)
        if ()
    return 0;
}
