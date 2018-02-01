#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

int n, q, x, y, k;
vector < int > bids[200200];

struct node {
    int id;
    int v;
    bool blocked = false;
} seg[800800];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id].id = ini;
        if (bids[ini].size() == 0) seg[id].v = 0;
        else seg[id].v = bids[ini][0];
        return;
    }
    if (fim - ini == 1) {
        seg[id].id = seg[id].v = 0;

        if (bids[ini].size() == 0 && bids[fim].size() > 0) {
            seg[id].id = fim;
            seg[id].v = bids[fim][0];
        }
        else if (bids[ini].size() > 0 && bids[fim].size() == 0) {
            seg[id].id = ini;
            seg[id].v = bids[ini][0];
        }
        else if (bids[ini].size() > 0 && bids[fim].size() > 0) {
            if (bids[ini][bids[ini].size()-1] > bids[fim][bids[fim].size()-1]) {
                seg[id].id = ini;
                int v = 0;

                for (int i = 0; i < bids[ini].size(); i++) {
                    v = bids[ini][i];
                    if (v > bids[fim][bids[fim].size()-1])
                        break;
                }
                seg[id].v = v;
            }
            else {
                seg[id].id = fim;
                int v = 0;

                for (int i = 0; i < bids[fim].size(); i++) {
                    v = bids[fim][i];
                    if (v > bids[ini][bids[ini].size()-1])
                        break;
                }
                seg[id].v = v;
            }
        }

        return;
    }

    int meio = (ini + fim) / 2;

    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);

    if (seg[2*id].v > seg[2*id+1].v) {
        seg[id].id = seg[2*id].id;
        seg[id].v = seg[2*id].v;
    }
    else {
        seg[id].id = seg[2*id+1].id;
        seg[id].v = seg[2*id+1].v;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        bids[x].push_back(y);
    }

    build(1, 1, n);
    printf("%d %d\n", seg[1].id, seg[1].v);

    vector < int > rem;

    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            scanf("%d", &x);
            rem.push_back(x);
        }

        for (int j = 0; j < k; j++)
       //     update(1, 1, n, rem[j], true);
        printf("%d %d\n", seg[1].id, seg[1].v);

        for (int j = 0; j < k; j++)
        //    update(1, 1, n, rem[j], false);

        rem.clear();
    }

    return 0;
}

