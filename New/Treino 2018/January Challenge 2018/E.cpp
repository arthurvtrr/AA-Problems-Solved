#include <bits/stdc++.h>

using namespace std;

#define ll long long

int t, x, n, ans[1001000];
vector < int > nums;
set < int > aux;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &x, &n);

        for (int i = 0; i <= n; i++)
            ans[i] = 0;
        nums.clear();
        aux.clear();

        ll total = 0;
        for (int i = n; i >= 1; i--) {
            if (i == x) continue;
            nums.push_back(i);
            total += i;
        }

        if (total % 2) { printf("impossible\n"); continue; }

        ll first = 0;
        while (!nums.empty() && first < total) {
            first += nums.back();
            total -= nums.back();
            aux.insert(nums.back());
            nums.pop_back();
        }

        ans[x] = 2;

        if (nums.empty()) printf("impossible\n");
        else {
            ll y = (first - total) / 2;
            bool v = false;

            if (first == total) v = true;
            else if (aux.count(y)) {
                v = true;
                nums.push_back(y);
            }
            else if (y-1 != 1 && aux.count(y-1) && aux.count(1)) {
                v = true;
                nums.push_back(y-1);
                nums.push_back(1);
            }
            else if (*aux.rbegin() != y+1) {
                v = true;
                nums.pop_back();
                nums.push_back(y+1);
                nums.push_back(*aux.rbegin());
            }

            if (!v) printf("impossible\n");
            else {
                for (int v : nums)
                    ans[v] = 1;
                for (int i = 1; i <= n; i++)
                    printf("%d", ans[i]);
                printf("\n");
            }
        }
    }
    return 0;
}
