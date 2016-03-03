#include <stdio.h>
#include <vector>

using namespace std;

struct edge {
    int f;
    int t;
};

vector < edge > edges;
vector < edge > excluded;

bool cont(edge x) {
    for (edge e : excluded)
        if (e.f == x.f && e.t == x.t)
            return true;
    return false;
}

int main() {
    int k, n;
    scanf("%d", &k);

    if (k % 2 == 0) printf("NO\n");
    else {
        if (k == 1) printf("YES\n2 1\n1 2\n");
        else {
            printf("YES\n");
            n = 2 + 2 * (k+1);
            edges.push_back((edge) {1, 2});

            for (int i = 3; i < 4+k; i++)
                for (int j = i+1; j < 4+k; j++)
                    edges.push_back((edge) {i, j});

            for (int i = 4+k; i < 5+2*k; i++)
                for (int j = i+1; j < 5+2*k; j++)
                    edges.push_back((edge) {i, j});

            for (int i = 3; i < 2 + k; i += 2) {
                excluded.push_back((edge) {i, i+1});
                edges.push_back((edge) {2, i});
                edges.push_back((edge) {2, i+1});
            }
            for (int i = 4+k; i < 2*k + 3; i += 2) {
                excluded.push_back((edge) {i, i+1});
                edges.push_back((edge) {1, i});
                edges.push_back((edge) {1, i+1});
            }

            printf("%d %d\n", n, edges.size() - excluded.size());
            for (edge e : edges)
                if (!cont(e))
                    printf("%d %d\n", e.f, e.t);
        }
    }

    return 0;
}
