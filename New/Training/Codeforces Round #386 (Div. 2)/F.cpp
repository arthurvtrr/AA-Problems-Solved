#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, w, k, pleas[200200], times[200200], cont[5050], sum[5050];

void update(int pos, int type) {
    int val = pos;

    while (pos <= 5000) {
        if (type == 1) {
            cont[pos]++;
            sum[pos] += val;
        }
        else {
            cont[pos]--;
            sum[pos] -= val;
        }

        pos += pos & -pos;
    }
}

int query(int pos, int type) {
    int ret = 0;
    while (pos) {
        if (type == 1) ret += cont[pos];
        else ret += sum[pos];

        pos -= pos & -pos;
    }
    return ret;
}

int bsearch(int num) {
    if (num < w)
        return query(5000, 2);

    int ini = 1, fim = 5000;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        if (query(meio, 1) <= num - w) ini = meio+1;
        else fim = meio-1;
    }

    int ret = query(5000, 2) - query(ini, 2);
    if (query(ini, 1) > num - w)
        ret += ini * (query(ini, 1) - num + w);

    return ret;
}

int main() {
    scanf("%d %d %d", &n, &w, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &pleas[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &times[i]);

    int ini = 0, fim = 0, maxi = 0, aux = 0, gain = 0;

    while (fim < n) {
        while (fim < n) {
            aux += times[fim];
            gain += pleas[fim];
            update(times[fim] / 2, 1);

            if (aux - bsearch(fim - ini + 1) > k) {
                aux -= times[fim];
                gain -= pleas[fim];
                update(times[fim] / 2, 2);
                break;
            }
            fim++;
        }

        maxi = max(maxi, gain);

        aux -= times[ini];
        gain -= pleas[ini];
        update(times[ini] / 2, 2);

        ini++;
        fim = max(fim, ini);
    }

    printf("%d\n", maxi);

    return 0;
}
