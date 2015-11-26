#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>

using namespace std;

bool primo[2000020];
vector < int > primos;
int hiperprimos[2000020];

void sieve(int n) {
    memset(primo, true, sizeof primo);
    primo[0] = false;
    primo[1] = false;
    for (long long i = 2; i <= n+1; i++)
        if (primo[i]) {
            for (long long j = i*i; j <= n+1; j += i)
                primo[j] = false;
            primos.push_back(i);
        }
}

int div(int n) {
    int i = 0, pf = primos[i];
    int total = 1;
    while (n != 1 && pf*pf <= n) {
        int quant = 0;
        while (n % pf == 0) {
            n /= pf;
            quant++;
        }
        total *= quant + 1;
        pf = primos[++i];
    }

    if (n != 1) total *= 2;

    return total;
}

int main() {
    int n;
    sieve(2000000);
    for (int i = 2; i < 2000001; i++) {
        if (primo[div(i)]) hiperprimos[i]++;
        hiperprimos[i] += hiperprimos[i-1];
    }

    while (scanf("%d", &n) != EOF)
        printf("%d\n", hiperprimos[n]);
    return 0;
}
