#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

int n, k, temp[200200];

int main() {
    scanf("%d %d", &n, &k);
    int cont = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &temp[i]);
        if (temp[i] < 0) cont++;
    }

    if (cont > k) printf("-1\n");
    else {
        int changes = 0, type = 1;
        for (int i = 1; i <= n; i++) {
            if (temp[i] < 0 && type == 1) {
                type = 0;
                changes++;
            }
            else if (temp[i] >= 0 && type == 0) {
                type = 1;
                changes++;
            }
        }

        int dist = 0, ini = 1;
        vector < int > dists;

        while (temp[ini] >= 0 && ini <= n) ini++;

        for (int i = ini; i <= n; i++) {
            if (temp[i] < 0 && dist > 0) {
                dists.push_back(dist);
                dist = 0;
            }
            else if (temp[i] >= 0) dist++;
        }

        sort(dists.begin(), dists.end());

        int left = k - cont;
        for (int i = 0; i < dists.size(); i++)
            if (dists[i] <= left) {
                left -= dists[i];
                changes -= 2;
            }

        int a = 0, ind = n;
        while (temp[ind] >= 0 && ind >= 1) {
            a++;
            ind--;
        }

        if (a > 0 && a <= left)
            changes--;

        printf("%d\n", max(0, changes));
    }

    return 0;
}

