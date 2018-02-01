#include <bits/stdc++.h>

using namespace std;

#define INF 2000000000

typedef struct item * pitem;
struct item {
    int prior, value, cnt, acum;
    pitem l, r;

    item(int v) {
        prior = rand(); value = v; cnt = 1;
        l = r = NULL; acum = 0;
    }
};

int cnt(pitem it) {
    return it ? it->cnt : 0;
}

void upd_cnt(pitem it) {
    if (it)
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void push(pitem it) {
    if (it && it->acum) {
		if (it->l) it->l->acum += it->acum;
        if (it->r) it->r->acum += it->acum;
        it->value += it->acum;
        it->acum = 0;
    }
}

void merge(pitem & t, pitem l, pitem r) {
    push(l);
    push(r);
    if (!l || !r) t = l ? l : r;
    else if (l->prior > r->prior) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    upd_cnt(t);
}

void split(pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t) return void( l = r = 0 );
    push(t);
    int cur_key = add + cnt(t->l);
    if (key <= cur_key) split(t->l, l, t->l, key, add), r = t;
    else split(t->r, t->r, r, key, add + 1 + cnt(t->l)), l = t;
    upd_cnt(t);
}

int bs(pitem t, int v){
	if (!t) return 0;
	push(t);
	if (t->value >= v) return bs(t->l, v);
	return bs(t->r, v) + 1 + cnt(t->l);
}

void update(pitem &t, int l, int r) {
    pitem t1, t2, t3, t4;
    split(t, t1, t2, bs(t, l));
    split(t2, t2, t3, bs(t2, r));
    if (t2) t2->acum++;
    merge(t, t1, new item(l));
    split(t3, t3, t4, 1);
    merge(t, t, t2);
    merge(t, t, t4);
}

int ans, n, l[300300], r[300300];

void cont(pitem t) {
	push(t);
	if (t->value < INF) ans++;

	if (t->l) cont(t->l);
	if (t->r) cont(t->r);
}

int main() {
    scanf("%d", &n);
	pitem root = NULL;
	for (int i = 0; i < 300300; i++)
		merge(root, root, new item(INF+i));

	for (int i = 0; i < n; i++) {
		scanf("%d %d", &l[i], &r[i]);
		update(root, l[i], r[i]);
	}

	ans = 0;
	cont(root);
	printf("%d\n", ans);

    return 0;
}
