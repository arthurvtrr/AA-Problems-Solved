#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, l, r, x, problems[20], sum = 0, sum1 = 0, sol = 0;

    scanf("%d %d %d %d", &n, &l, &r, &x);

    for (int i = 0; i < n; i++) {
        scanf("%d", &problems[i]);
        sum += problems[i];
    }

    if (sum >= l && sum <= r && abs(problems[0] - problems[n-1]) >= x) sol++;

    sort(problems, problems+n);

    for (int i = 1; i < n; i++) {

    }

    return 0;
}
