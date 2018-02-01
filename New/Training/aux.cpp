#pragma GCC optimize('Ofast')
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2000100;
int tree[maxn<<2], lazy[maxn<<2];
void push(int id, int l, int r){
    if(lazy[id]){
        tree[id] += lazy[id];
        if(l != r){
            lazy[id<<1] += lazy[id];
            lazy[(id<<1)|1] += lazy[id];
        }
        lazy[id] = 0;
    }
}
void update(int id, int l, int r, int x, int y, int v){
    push(id, l, r);
    if(l > y || r < x) return;
    if(x <= l && r <= y){
        lazy[id] += v;
        push(id, l, r);
        return;
    }
    int mid = (l+r)>>1;
    update(id<<1, l, mid, x, y, v);
    update((id<<1)|1, mid + 1, r, x, y, v);
    tree[id] = min(tree[id<<1], tree[(id<<1)|1]);
}
int query(int id, int l, int r, int x, int y){
    push(id, l, r);
    if(l > y || r < x) return maxn;
    if(x <= l && r <= y) return tree[id];
    int mid = (l + r)>>1;
    return min(query(id<<1, l, mid, x, y), query((id<<1)|1, mid+1, r, x, y));
}
struct event{
    int l, x, y, add;
};
bool cmp(event left, event right){
    return left.l < right.l;
}
const int maxsz = 100100;
int x[maxsz], y[maxsz], n;
bool theta;
bool valid(int distance){
    printf("dist %d\n", distance);
    vector<event> events;
    for(int e = 0; e < n; e++){
        events.push_back((event){max(x[e] - distance, 0), max(y[e] - distance, 0), min(y[e] + distance, maxn), 1});
        events.push_back((event){min(x[e] + distance + 1, maxn), max(y[e] - distance, 0), min(y[e] + distance, maxn), 0});
    }
	int ptr = 0, lower = maxn/2 - distance, upper = maxn/2 + distance;
    sort(events.begin(), events.end(), cmp);
	bool empty = true, change = false;
	for(int e = 0; e < maxn; e++){
		change = false;
		while(ptr < 2*n && events[ptr].l == e){
			if(events[ptr].add) update(1, 0, maxn, events[ptr].x, events[ptr].y, 1);
			else update(1, 0, maxn, events[ptr].x, events[ptr].y, -1);
			change = true;
			empty = false;
			ptr++;
		}
		if(empty || change || (ptr == 2*n)){
			if(lower <= e && e <= upper){
				if(query(1, 0, maxn, lower, upper) == 0){
					while(ptr < 2*n){
						if(events[ptr].add) update(1, 0, maxn, events[ptr].x, events[ptr].y, 1);
						else update(1, 0, maxn, events[ptr].x, events[ptr].y, -1);
						ptr++;
					}
					return true;
				}
			}
		}
	}
	while(ptr < 2*n){
		if(events[ptr].add) update(1, 0, maxn, events[ptr].x, events[ptr].y, 1);
		else update(1, 0, maxn, events[ptr].x, events[ptr].y, -1);
		ptr++;
	}
    return false;
}
int main(){
    for(int cc = 1; scanf("%d", &n), n != -1; cc++){
        printf("Case %d: ", cc);
        for(int e = 0; e < n; e++)
            scanf("%d %d", x + e, y + e);
        for(int e = 0; e < n; e++)
            x[e] += maxn/2, y[e] += maxn/2;
        int lo = 1, hi = maxn/2, ans = 0;
        theta = false;
        if(valid(hi)){
            printf("never\n");
            continue;
        }
        while(lo <= hi){
            int mid = (lo + hi)>>1;
            if(valid(mid)) lo = mid+1, ans = mid;
            else hi = mid-1;
            printf("%d\n", valid(mid));
        }
        if(ans >= maxn/2) printf("never\n");
        else{
            printf("%d\n", ans+1);
        }
    }
    // cerr << clock() << endl;
    return 0;
}
