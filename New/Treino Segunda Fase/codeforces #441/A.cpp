#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
    scanf("%d", &n);
    vector < int > ans;

    for (int i = 1; i < 90; i++) {
        if (n - i > 0) {
            int sum = 0, aux = n - i;
            while (aux) {
                sum += aux % 10;
                aux /= 10;
            }
            if (sum == i) ans.push_back(n - i);
        }
    }

    sort(ans.begin(), ans.end());
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++)
        printf("%d\n", ans[i]);

    return 0;
}
