///Binary Indexed Tree / Fenwick Tree
///Range Queries and Range Updates
///1-indexed

#define MN 100100

int bit1[MN], bit2[MN];

void update(int bit[], int idx, int delta) {
    for(; idx < MN; idx += (idx & -idx)) bit[idx] += delta;
}

void update(int left, int right, int delta) {
    update(bit1, left, delta);
    update(bit1, right + 1, -delta);

    update(bit2, left, delta * (left-1));
    update(bit2, right + 1, -delta * right);
}

int query(int bit[], int idx) {
    int sum  = 0;
    for(; idx > 0; idx -= (idx & -idx)) sum += bit[idx];
    return sum;
}

int query(int idx) {
    return query(bit1, idx) * idx - query(bit2, idx);
}

int query(int left, int right) {
    return query(right) - query(left - 1);
}
