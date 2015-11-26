#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

typedef pair < int, int > pii;
typedef map < pii, vector < pii > > CoordMap;

CoordMap coords;
map < pii, bool > visited;

void dfs(pii p) {
    visited[p] = true;
    for (pii v : coords[p]) {
        if (!visited[v])
            dfs(v);
    }
}

int main() {
    int n;
    int s = -1;
    scanf("%d", &n);

    int x, y;
    for (int i = 0; i < n; i++) {
        bool f = false;
        scanf("%d %d", &x, &y);
        pii p = make_pair(x, y);

        for (CoordMap::iterator i = coords.begin(); i != coords.end(); ++i) {
            if (i->first.first == x || i->first.second == y) {
                coords[i->first].push_back(p);
                coords[p].push_back(i->first);
                f = true;
            }
        }
        if (!f)
            coords[p];
    }

    for (CoordMap::iterator i = coords.begin(); i != coords.end(); ++i) {
        if (!visited[i->first]) {
            dfs(i->first);
            s++;
        }
    }

    printf("%d\n", s);
    return 0;
}
