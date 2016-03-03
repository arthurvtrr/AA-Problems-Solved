#include <stdio.h>
#include <set>

using namespace std;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char mat[110][110];
    for (int i = 0; i < n; i++)
        scanf("%s", mat[i]);

    set < char > aux;

    long long ans = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            aux.insert(mat[j][i]);
        ans *= aux.size();
        ans %= 1000000007;
        aux.clear();
    }
    printf("%lld\n", ans);
    return 0;
}
