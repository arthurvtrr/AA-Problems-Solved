#include <bits/stdc++.h>

using namespace std;

typedef struct item * pitem;
struct item {
    int prior, value, cnt, acum;
    bool rev;
    pitem l, r;

    item(int v) {
        prior = rand(); value = v; cnt = 1;
        l = r = NULL;
        rev = false; acum = 0;
    }
};

int cnt (pitem it) {
    return it ? it->cnt : 0;
}

void upd_cnt (pitem it) {
    if (it)
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void push (pitem it) {
    if (it && it->rev) {
        it->rev = false;
        swap (it->l, it->r);
        if (it->l)  it->l->rev ^= true;
        if (it->r)  it->r->rev ^= true;
    }
    if (it && it->acum) {
        if (it->l) it->l->acum += it->acum;
        if (it->r) it->r->acum += it->acum;
        it->value += it->acum;
        it->value %= 26;
        it->acum = 0;
    }
}

void merge (pitem & t, pitem l, pitem r) {
    push (l);
    push (r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd_cnt (t);
}

void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t)
        return void( l = r = 0 );
    push (t);
    int cur_key = add + cnt(t->l);
    if (key <= cur_key)
        split (t->l, l, t->l, key, add),  r = t;
    else
        split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    upd_cnt (t);
}

void reverse (pitem t, int l, int r) {
    pitem t1, t2, t3;
    split (t, t1, t2, l);
    split (t2, t2, t3, r-l+1);
    t2->rev ^= true;
    merge (t, t1, t2);
    merge (t, t, t3);
}

void output (pitem t) {
    if (!t)  return;
    push (t);
    output (t->l);
    printf ("%c", t->value + 'a');
    output (t->r);
}

void increase(pitem t, int l, int r) {
    pitem t1, t2, t3;
    split (t, t1, t2, l);
    split (t2, t2, t3, r-l+1);
    t2->acum++;
    merge (t, t1, t2);
    merge (t, t, t3);
}

void change(pitem t, int i, int j, int k, int l) {
    pitem t1, t2, t3, t4, t5;
    split (t, t1, t2, i);
    split (t2, t2, t3, j-i+1);
    split (t3, t3, t4, k-j-1);
    split (t4, t4, t5, l-k+1);
    merge(t, t1, t4);
    merge(t, t, t3);
    merge(t, t, t2);
    merge(t, t, t5);
}

int t, n, a, b, c, d;
string s;

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        cin >> s >> n;
        pitem root = NULL;

        for (int i = 0; i < s.size(); i++)
            merge(root, root, new item(s[i] - 'a'));

        for (int i = 0; i < n; i++) {
            scanf("%d %d %d %d", &a, &b, &c, &d);
            change(root, a-1, b-1, c-1, d-1);
            reverse(root, a-1, a-1+d-c);
            reverse(root, a-1+d-b, d-1);
            increase(root, a-1, a-1+d-c);
            increase(root, a-1+d-b, d-1);
        }
        output(root);
        printf("\n");
    }

    return 0;
}
