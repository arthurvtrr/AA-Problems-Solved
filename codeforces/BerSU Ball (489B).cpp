#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

int n, m;
int boys[110], girls[110], *MIN, *MAX;

using namespace std;

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &boys[i]);
    }
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &girls[i]);
    }

    std::sort(boys, boys+n);
    std::sort(girls, girls+m);

    if (n>m) {
        MAX = boys;
        MIN = girls;
    } else {
        MAX = girls;
        MIN = boys;
    }

    int pairs = 0;
    int index = 0;
    for(int i = 0; i < min(n,m); i++) {
        if (abs(MIN[i] - MAX[index]) <= 1 and index < max(n,m)) {
            pairs += 1;
            index += 1;
        }
        else {
            while (MIN[i] > MAX[index] and index < max(n,m)) {
                index += 1;
                if (abs(MIN[i] - MAX[index]) <= 1 and index < max(n,m)) {
                    pairs += 1;
                    index += 1;
                    break;
                    }
            }
        }
    }

    printf("%d", pairs);
    return 0;
}