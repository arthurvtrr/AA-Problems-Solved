#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <map>

using namespace std;

#define pii pair < int, int >

//Preprocess

int n, m, p, x, y, cost[100100], stop[100100], previous[100100];
vector < int > graph[100100], path;
bool visited[100100];

void dfs(int u) {
    visited[u] = true;
    for (int v : graph[u])
        if (!visited[v]) {
            dfs(v);
            previous[v] = u;
        }
}

int dfs2(int u) {
    visited[u] = true;

    int ret = 0;
    for (int v : graph[u])
        if (!visited[v])
            ret = max(ret, cost[v] + dfs2(v));

    return ret;
}

//Aux Segtrees

struct Node {
    int sum;
    int val;
} seg[2][400400];

void build(int id, int ini, int fim, int type) {
    if (ini == fim) {
        seg[type][id].sum = cost[path[ini]];
        seg[type][id].val = cost[path[ini]] + stop[ini];
        return;
    }
    int meio = (ini + fim) / 2;

    build(2*id, ini, meio, type);
    build(2*id+1, meio+1, fim, type);

    seg[type][id].sum = seg[type][2*id].sum + seg[type][2*id+1].sum;

    if (type == 0)
        seg[type][id].val = max(seg[type][2*id].val, seg[type][2*id].sum + seg[type][2*id+1].val);
    else
        seg[type][id].val = max(seg[type][2*id].val + seg[type][2*id+1].sum, seg[type][2*id+1].val);
}

Node query(int id, int ini, int fim, int start, int end, int type) {
    if (start > fim || end < ini)
        return (Node) {0, 0};
    if (ini >= start && fim <= end)
        return seg[type][id];

    int meio = (ini + fim) / 2;

    Node left = query(2*id, ini, meio, start, meio, type);
    Node right = query(2*id+1, meio+1, fim, meio+1, end, type);
    Node ans;

    if (type == 0) {
        ans.val = max(left.val, left.sum + right.val);
        ans.sum = left.sum + right.sum;
    }
    else {
        ans.val = max(left.val + right.sum, right.val);
        ans.sum = left.sum + right.sum;
    }

	return ans;
}

//DP

map < vector < int >, pii > dp;

pii solve(int p1, int p2, int atual) {
    vector < int > ind = {p1, p2, atual};

    if (dp.count(ind))
        return dp[ind];

    pii ret;

    if (atual == 0) {
        //printf("%d %d %d : %d %d\n", p1, p2, atual, cost[path[p1]] + stop[p1], query(1, 1, (int)path.size()-1, p1+1, p2, 1).val);
        ret = {cost[path[p1]] + stop[p1], query(1, 1, (int)path.size()-1, p1+1, p2, 1).val};

        if (p1+1 != p2) {
            pii aux = solve(p1+1, p2, 1-atual);
            if (cost[path[p1]] + aux.second - aux.first > ret.first - ret.second)
                ret = make_pair(cost[path[p1]] + aux.second, aux.first);
        }
    }
    else {
       // printf("%d %d %d : %d %d\n", p1, p2, atual, cost[path[p2]] + stop[p2], query(1, 1, (int)path.size()-1, p1, p2-1, 0).val);
        ret = {cost[path[p2]] + stop[p2], query(1, 1, (int)path.size()-1, p1, p2-1, 0).val};

        if (p1+1 != p2) {
            pii aux = solve(p1, p2-1, 1-atual);
            if (cost[path[p2]] + aux.second - aux.first > ret.first - ret.second)
                ret = make_pair(cost[path[p2]] + aux.second, aux.first);
        }
    }

    return dp[ind] = ret;
}

int main() {
    while (scanf("%d %d %d", &n, &m, &p) != EOF) {

        for (int i = 0; i < 100100; i++) {
            graph[i].clear();
            visited[i] = false;
            cost[i] = stop[i] = 0;
            previous[i] = -1;
        }

        for (int i = 0; i < 400400; i++)
            seg[0][i].sum = seg[0][i].val = seg[1][i].sum = seg[1][i].val = 0;

        for (int i = 1; i <= n; i++)
            scanf("%d", &cost[i]);

        for (int i = 0; i < n-1; i++) {
            scanf("%d %d", &x, &y);
            graph[x].push_back(y);
            graph[y].push_back(x);
        }

        path.clear();
        path.push_back(-1);

        dfs(p);
        int aux = m;
        while (aux != -1) {
            path.push_back(aux);
            aux = previous[aux];
        }

        for (int i = 1; i <= n; i++)
            visited[i] = false;
        for (int i = 1; i < (int)path.size(); i++)
            visited[path[i]] = true;
        for (int i = 1; i < (int)path.size(); i++)
            stop[i] = dfs2(path[i]);

        build(1, 1, (int)path.size()-1, 0);
        build(1, 1, (int)path.size()-1, 1);

       // for (int i = 1; i < (int)path.size(); i++)
       //     printf("%d ----- %d\n", cost[path[i]], stop[i]);

        dp.clear();
        pii sol = solve(1, (int)path.size()-1, 0);
        printf("%d\n", sol.first - sol.second);
    }
    return 0;
}

/*
11 1 10
3 50 20 10 9 7 12 35 9 7 2
1 2
1 3
3 4
4 5
4 6
3 7
7 8
7 9
9 10
10 11
*/
