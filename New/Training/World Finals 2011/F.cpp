#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define EPS 1e-9

int n, c, m;
ll dp[100100];

struct mac {
    ll d, p, r, g;
} macs[100100];

bool cmp(mac a, mac b) {
    return a.d < b.d;
}

struct item {
    ll key, b;
    int prior, cnt;
    item *l, *r;
    item() {}
    item(ll key, ll b, int prior) : key(key), b(b), prior(prior), l(NULL), r(NULL) { }
};
typedef item *pitem;

int cnt(pitem t) {
    return t ? t->cnt : 0;
}

void upd_cnt(pitem t) {
    if (t) t->cnt = 1 + cnt(t->l) + cnt(t->r);
}

void split(pitem t, ll key, pitem &l, pitem &r) {
    if (!t) l = r = NULL;
    else if (key < t->key) split(t->l, key, l, t->l), r = t;
    else split(t->r, key, t->r, r), l = t;
    upd_cnt(t);
}

void insert(pitem &t, pitem it) {
    if (!t) t = it;
    else if (it->prior > t->prior) split(t, it->key, it->l, it->r), t = it;
    else insert(it->key < t->key ? t->l : t->r, it);
    upd_cnt(t);
}

void merge(pitem &t, pitem l, pitem r) {
    if (!l || !r) t = l ? l : r;
    else if (l->prior > r->prior) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    upd_cnt(t);
}

void erase(pitem &t, ll key) {
    if (t->key == key) merge(t, t->l, t->r);
    else erase(key < t->key ? t->l : t->r, key);
    upd_cnt(t);
}

pitem kth(pitem t, int k, int sum = 0) {
    int pos = sum + cnt(t->l);
    if (k < pos) return kth(t->l, k, sum);
    if (k > pos) return kth(t->r, k, sum + cnt(t->l) + 1);
    return t;
}

pitem root;

ll query(ll pos) {
    if (cnt(root) == 1) return root->key * pos + root->b;

    int ini = 0, fim = cnt(root) - 2;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        pitem a = kth(root, meio), b = kth(root, meio+1);
        double inter = (a->b - b->b + 0.0) / (b->key - a->key);
        if (pos + EPS < inter) fim = meio-1;
        else ini = meio+1;
    }
    pitem aux = kth(root, ini);
    return aux->key * pos + aux->b;
}

void addLine(ll m, ll n) {
    pitem t1, t2, t3, t4;
    split(root, m, t1, t2);

    t3 = kth(t1, cnt(t1)-1);
    if (t3->key == m && t3->b >= n) return;
    if (t3->key == m) erase(t1, m);

    while (cnt(t1) > 1) {
        t3 = kth(t1, cnt(t1)-1), t4 = kth(t1, cnt(t1)-2);
        double inter1 = (t3->b - t4->b + 0.0) / (t4->key - t3->key);
        double inter2 = (n - t4->b + 0.0) / (t4->key - m);
        if (inter2 < inter1) erase(t1, t3->key);
        else break;
    }

    merge(t1, t1, new item(m, n, rand()));
    int nxt = cnt(t1) + 2;
    merge(root, t1, t2);

    if (nxt > cnt(root)) return;

    while (nxt > 2) {
        t1 = kth(root, nxt-1), t2 = kth(root, nxt-2), t3 = kth(root, nxt-3);
        double inter1 = (t2->b - t3->b + 0.0) / (t3->key - t2->key);
        double inter2 = (t1->b - t3->b + 0.0) / (t3->key - t1->key);

        if (inter2 < inter1) erase(root, t2->key);
        else break;
        nxt--;
    }
}

int main() {
    srand(time(NULL));

    int t = 1;
    while (1) {
        scanf("%d %d %d", &n, &c, &m);
        if (n + c + m == 0) break;

        for (int i = 0; i < n; i++)
            scanf("%lld %lld %lld %lld", &macs[i].d, &macs[i].p, &macs[i].r, &macs[i].g);

        sort(macs, macs+n, cmp);
        macs[n] = (mac) {m+1, 0, 0, 0};

        root = new item(0, c, rand());

        for (int i = 0; i <= n; i++) {
            dp[i] = query(macs[i].d);
            if (i == n || dp[i] < macs[i].p) continue;

            addLine(macs[i].g, dp[i] + macs[i].r - macs[i].d*macs[i].g - macs[i].g - macs[i].p);
        }

        printf("Case %d: %lld\n", t++, dp[n]);
    }

    return 0;
}

/*
6 10 20
6 12 1 3
1 9 1 2
3 2 1 2
8 20 5 4
4 11 7 4
2 10 9 1
*/
