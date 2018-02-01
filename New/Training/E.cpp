#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <set>

using namespace std;

int n;
long long k, x, freq[10001000];

int main() {
    scanf("%d %lld", &n, &k);

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &x);
        sum += x;
        freq[x]++;
    }

    if (sum < k) printf("-1\n");
    else {
        long long quant = n, pos = 10000000;
        while (quant < k) {
            while (freq[pos] == 0) pos--;

            if (pos % 2 == 0) freq[pos / 2] += 2 * freq[pos];
            else {
                freq[pos / 2] += freq[pos];
                freq[pos / 2 + 1] += freq[pos];
            }
            quant += freq[pos];
            freq[pos] = 0;
        }

        long long ini = 1, fim = 10000000;

        while (1) {
            while (freq[ini] == 0) ini++;

            if (quant - freq[ini] < k) break;
            else {
                quant -= freq[ini];
                freq[ini] = 0;
            }
        }

        while (1) {
            while (freq[ini] == 0) ini++;
            while (freq[fim] == 0) fim--;

            if (fim / 2 <= ini) break;

            if (fim % 2 == 0) freq[fim / 2] += 2 * freq[fim];
            else {
                freq[fim / 2] += freq[fim];
                freq[fim / 2 + 1] += freq[fim];
            }

            long long left = freq[fim];
            while (1) {
                if (freq[ini] >= left) {
                    freq[ini] -= left;
                    break;
                }
                else {
                    left -= freq[ini];
                    freq[ini] = 0;
                    while (freq[ini] == 0) ini++;
                }
            }

            freq[fim] = 0;
        }

        printf("%lld\n", ini);
    }

    return 0;
}

