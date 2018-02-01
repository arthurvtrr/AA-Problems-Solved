#include <bits/stdc++.h>
#define MN 100100
#define EPS 1e-9
using namespace std;
typedef long long ll;

struct Line {
    ll m, b;
    ll y(ll x) {return x * m + b; }
    double inter(Line other) {return 1.0*(other.b-b)/(m-other.m);}
    bool operator<(const Line &o) const {return (m == o.m) ? (b < o.b) : (m < o.m);}
    bool operator<=(const Line &o) const {return (m == o.m) ? (b <= o.b) : (m <= o.m);}
 };

typedef Line T;

int sqrtN = 300;

struct bucket {
    vector<T> elem;
};

vector<bucket> s_array(1);
int total_size;

void split(bucket &target, int bucket_idx) {
    bucket temp;
    temp.elem.assign(target.elem.begin() + sqrtN, target.elem.end());
    target.elem.resize(sqrtN);
    s_array.insert(s_array.begin() + bucket_idx + 1, temp);
}

Line at(int idx) {
    for(int i=0; i<(int)s_array.size(); i++) {
        bucket &b = s_array[i];

        if(idx < b.elem.size())
            return b.elem[idx];

        idx -= b.elem.size();
    }
}

int index(pair<int, int> pos) {
    int ret = pos.second;

    while(pos.first) {
        pos.first--;
        ret += s_array[pos.first].elem.size();
    }

    return ret;
}

void insert(T elem, int idx, int bucket_id = 0) {
    for(int i=bucket_id; i<(int)s_array.size(); i++) {
        bucket &b = s_array[i];

        if(idx <= b.elem.size()) {
            b.elem.insert(b.elem.begin() + idx, elem);
            if(b.elem.size() >= 2 * sqrtN) split(b, i);
            total_size++;
            return;
        }

        idx -= b.elem.size();
    }
}

pair<int, int> lower_bound(T elem) {
    int l = 0, r = s_array.size() - 1, m;
    while(l < r) {
        m = (l + r) / 2;
        if(s_array[m+1].elem[0] <= elem)
            l = m + 1;
        else
            r = m;
    }

    int bucket_id = l;
    l = 0, r = s_array[bucket_id].elem.size();
    while(l < r) {
        m = (l + r) / 2;
        if(s_array[bucket_id].elem[m] < elem)
            l = m + 1;
        else
            r = m;
    }

    return make_pair(bucket_id, l);
}

void ordered_insert(T elem) {
    pair<int, int> lbound = lower_bound(elem);
    insert(elem, lbound.second, lbound.first);
}

void erase(int idx) {
    //cout << "removendo " << idx << endl;
    int i;
    for(i=0; i<(int)s_array.size(); i++) {
        bucket &b = s_array[i];

        if(idx < b.elem.size())
            break;

        idx -= b.elem.size();
    }
    bucket &b = s_array[i];
    b.elem.erase(b.elem.begin() + idx);
    if(b.elem.size() == 0) s_array.erase(s_array.begin() + i);
    total_size--;
}

void ordered_erase(T elem) {
    pair<int, int> position = lower_bound(elem);
    bucket &b = s_array[position.first];

    b.elem.erase(b.elem.begin() + position.second);
    if(b.elem.size() == 0) s_array.erase(s_array.begin() + position.first);
    total_size--;
}

void insere(Line l) {
    int id = index(lower_bound(l));
    //cout << "inserindo " << l.m << " " << l.b << endl;

    printf("------- %lld %lld\n", l.m, l.b);

    if(id > 0 && id < total_size && at(id).inter(l) + EPS < at(id).inter(at(id - 1))) return;
    if(id < total_size && l.m == at(id+1).m) return;
    ordered_insert(l);

    while(id > 0 && l.m == at(id-1).m) {
            //puts("1");
        erase(id-1);
        id--;
    }


    while(id > 1 && l.inter(at(id-1)) + EPS < l.inter(at(id-2))) {
            //puts("2");
        erase(id-1);
        id--;
    }

    while(id + 2 < total_size && at(id + 2).inter(at(id + 1)) + EPS < at(id + 2).inter(l)) {
            //puts("3");
        erase(id + 1);
    }
}

ll maximum(ll x) {
  //  printf("%lld\n", x);
    int l = 0, r = total_size - 1;
    while(l < r) {
        int m = (l + r) / 2;
        if(at(m).inter(at(m + 1)) < x + EPS)
            l = m + 1;
        else r = m;
    }
   // printf("%lld %lld\n", at(l).m, at(l).b);
    return at(l).y(x);
}

struct machine {
    ll d, p, r, g;
} m[MN];

bool cmp(machine a, machine b) {
    return a.d < b.d;
}

long long dp[MN];
int n, c, d, casee;

int main() {
    while(1) {
        scanf("%d %d %d", &n, &c, &d);
        if(!n) break;
        s_array.clear();
        s_array.resize(1);
        total_size = 0 ;

        for(int i=0; i<n; i++) {
            scanf("%d %d %d %d", &m[i].d, &m[i].p, &m[i].r, &m[i].g);
        } sort(m, m + n, cmp);

        insere(Line{0, c});

        for(int i=0; i<n; i++) {
            dp[i] = maximum(m[i].d);
            //cout << "dp " << m[i].d << " vale " << dp[i] << endl;
            if(dp[i] >= m[i].p) insere(Line{m[i].g, dp[i] - m[i].p + m[i].r - m[i].g*(m[i].d + 1)});
            printf("Treap:\n");
            for (int j = 0; j < total_size; j++)
                printf("%lld %lld\n", at(j).m, at(j).b);
        }

        ll ans = c;
        printf("Case %d: %lld\n", ++casee, maximum(d+1));
    }
    return 0;
}
