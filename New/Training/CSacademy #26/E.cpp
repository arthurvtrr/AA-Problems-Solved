#include <bits/stdc++.h>

using namespace std;

#define N 100100

int n, m, k;
struct sp {
    int x, y;
    int a, b;
} special[N];

int seg[4*N];

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

bool cmp1(sp a, sp b) {
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

bool cmp2(sp a, sp b) {
    if (a.x == b.x)
        return a.y > b.y;
    return a.x > b.x;
}

set < int > diff;
map < int, int > ind, cnt;

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < k; i++)
        scanf("%d %d", &special[i].x, &special[i].y);

    for (int i = 0; i < k; i++)
        diff.insert(special[i].y);

    int cont = 2;
    for (set < int >::iterator it = diff.begin(); it != diff.end(); it++)
        ind[*it] = cont++;
    for (int i = 0; i < k; i++)
        special[i].y = ind[special[i].y];

    sort(special, special+k, cmp1);

    int ans = 0;

    for (int i = 0; i < k; i++) {
        int x = query(1, 1, N, 1, special[i].y);
        update(1, 1, N, special[i].y, x+1);
        special[i].a = x+1;
        ans = max(ans, x+1);
    }

    sort(special, special+k, cmp2);

    for (int i = 0; i < 4*N; i++)
        seg[i] = 0;

    for (int i = 0; i < k; i++) {
        int x = query(1, 1, N, special[i].y, N);
        update(1, 1, N, special[i].y, x+1);
        special[i].b = x+1;
    }

    for (int i = 0; i < k; i++)
        if (special[i].a + special[i].b - 1 == ans)
            cnt[special[i].a]++;

    int sol = 0;
    for (map<int, int>::iterator it = cnt.begin(); it != cnt.end(); it++)
        if (it->second == 1)
            sol++;

    printf("%d\n", sol);

    return 0;
}

