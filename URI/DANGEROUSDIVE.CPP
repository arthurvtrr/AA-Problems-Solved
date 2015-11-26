#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, r, x;
    bool returned[11000];
    while(scanf("%d %d", &n, &r) != EOF) {
        for (int i = 0; i < 11000; i++)
            returned[i] = false;
        for (int i = 0; i < r; i++) {
            scanf("%d", &x);
            returned[x] = true;
        }
        vector < int > died;
        for (int i = 1; i <= n; i++)
            if (!returned[i])
                died.push_back(i);
        if (died.size() == 0) printf("*\n");
        else {
            for (int i = 0; i < died.size(); i++)
                printf("%d ", died[i]);
            printf("\n");
        }
    }
    return 0;
}
