#include <stdio.h>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int bit[210000];
map < int, int > appear, ind;
vector < int > used, ord;

struct oper {
    int x;
    int y;
} opers[110000];

void update(int pos, int x, int n) {
    while (pos <= n) {
        bit[pos] += x;
        pos += pos & -pos;
    }
}

int query(int pos) {
    int sum = 0;
    while (pos) {
        sum += bit[pos];
        pos -= pos & -pos;
    }
    return sum;
}

int main() {
    int n, c = 1;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &opers[i].x, &opers[i].y);
        if (!appear.count(opers[i].x)) appear[opers[i].x]++;
        if (!appear.count(opers[i].y)) appear[opers[i].y]++;
    }

    long long sol = 0;

    used.push_back(0);
    ord.push_back(0);
    for (map < int, int >::iterator it = appear.begin(); it != appear.end(); it++) {
        used.push_back(it->first);
        ord.push_back(it->first);
        ind[it->first] = c++;
    }

    for (int i = 0; i < n; i++)
        swap(used[ind[opers[i].x]], used[ind[opers[i].y]]);

    for (int i = 1; i < used.size(); i++) {
        sol += query(c) - query(ind[used[i]]);
        sol += abs(used[i] - ord[i]) - 1;
        sol -= abs(ind[used[i]] - i) - 1;
        update(ind[used[i]], 1, c);
    }

    printf("%I64d\n", sol);

    return 0;
}
