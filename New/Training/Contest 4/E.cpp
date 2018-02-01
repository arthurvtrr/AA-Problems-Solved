#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int t, n, nums[200200], ind[200200];
pii group[200200];

set < int > aux;
map < int, int > value;

int seg[800800];

void update(int id, int ini, int fim, int pos, int val) {
    if (ini == fim) {
        seg[id] = val;
        return;
    }
    int meio = (ini + fim) / 2;

    if (pos <= meio) update(2*id, ini, meio, pos, val);
    else update(2*id+1, meio+1, fim, pos, val);

    seg[id] = max(seg[2*id], seg[2*id+1]);
}

int query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return seg[id];

    int meio = (ini + fim) / 2;

	return max(query(2*id, ini, meio, start, end), query(2*id+1, meio+1, fim, start, end));
}

int main() {
    scanf("%d", &t);

    for (int tc = 0; tc < t; tc++) {
        aux.clear();
        value.clear();

        for (int i = 0; i < 200200; i++) {
            nums[i] = ind[i] = 0;
            group[i] = pii(0, 0);
        }
        for (int i = 0; i < 800800; i++)
            seg[i] = 0;

        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);

        for (int i = 0; i < n; i++)
            aux.insert(nums[i]);

        int cnt = 1;
        for (set < int >::iterator it = aux.begin(); it != aux.end(); it++)
            value[*it] = cnt++;

        for (int i = 0; i < n; i++)
            nums[i] = value[nums[i]];

        int ini = 0, siz = 1, g = 1;

        ind[0] = 1;
        for (int i = 1; i <= n; i++) {
            if (nums[i] <= nums[i-1]) {
                group[g] = pii(ini, siz);
                g++;
                ini = i;
                siz = 1;
            }
            else siz++;

            ind[i] = g;
        }

        int ans = 0;

        for (int i = n-1; i >= 0; i--) {
            int a = group[ind[i]].first, b = group[ind[i]].second;
            int x = query(1, 1, n, nums[i], nums[i]);
            if (b - i + a > x)
                update(1, 1, n, nums[i], b - i + a);

            ans = max(ans, i - a + 1 + query(1, 1, n, nums[i]+1, 200100));
        }

        printf("%d\n", ans);
    }

    return 0;
}

