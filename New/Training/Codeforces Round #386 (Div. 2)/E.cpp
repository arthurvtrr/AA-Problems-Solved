#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <map>

using namespace std;

int n, m, cards[400200];
bool used[400200], exchanged[200200];
map < int, int > quant;

int main() {
    scanf("%d %d", &n, &m);

    int odd = 0, even = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &cards[i]);
        if (cards[i] % 2 == 0) even++;
        else odd++;
        quant[cards[i]]++;
        if (cards[i] <= n) used[cards[i]] = true;
    }

    int cont = 0, nextodd = 1, nexteven = 2;

    for (int i = 0; i < n; i++) {
        while (used[nextodd])
            nextodd += 2;
        while (used[nexteven])
            nexteven += 2;

        if (quant[cards[i]] > 1) {
            if (odd > even) {
                if (nexteven > m) cont = 10000000;
                else {
                    if (cards[i] % 2 != 0) {
                        even++;
                        odd--;
                    }
                    quant[cards[i]]--;
                    cards[i] = nexteven;
                    used[nexteven] = true;
                    cont++;
                }
            }
            else if (even > odd) {
                if (nextodd > m) cont = 10000000;
                else {
                    if (cards[i] % 2 == 0) {
                        even--;
                        odd++;
                    }
                    quant[cards[i]]--;
                    cards[i] = nextodd;
                    used[nextodd] = true;
                    cont++;
                }
            }
            else {
                if (cards[i] % 2 == 0 && nexteven <= m) {
                    quant[cards[i]]--;
                    cards[i] = nexteven;
                    used[nexteven] = true;
                    cont++;
                }
                else if (cards[i] % 2 != 0 && nextodd <= m){
                    quant[cards[i]]--;
                    cards[i] = nextodd;
                    used[nextodd] = true;
                    cont++;
                }
                else {
                    if (nexteven <= m) {
                        if (cards[i] % 2 != 0) {
                            even++;
                            odd--;
                        }
                        quant[cards[i]]--;
                        cards[i] = nexteven;
                        used[nexteven] = true;
                        cont++;
                    }
                    else if (nextodd <= m) {
                        if (cards[i] % 2 == 0) {
                            even--;
                            odd++;
                        }
                        quant[cards[i]]--;
                        cards[i] = nextodd;
                        used[nextodd] = true;
                        cont++;
                    }
                    else cont = 10000000;
                }
            }
            exchanged[i] = true;
        }
    }

    for (int i = 0; i < n; i++) {
        while (used[nextodd])
            nextodd += 2;
        while (used[nexteven])
            nexteven += 2;

        if (!exchanged[i]) {
            if (odd > even && cards[i] % 2 != 0) {
                if (nexteven > m) cont = 10000000;
                else {
                    cards[i] = nexteven;
                    used[nexteven] = true;
                    even++;
                    odd--;
                    cont++;
                }
            }
            else if (even > odd && cards[i] % 2 == 0) {
                if (nextodd > m) cont = 10000000;
                else {
                    cards[i] = nextodd;
                    used[nextodd] = true;
                    odd++;
                    even--;
                    cont++;
                }
            }
        }
    }

    if (cont >= 10000000) printf("-1\n");
    else {
        printf("%d\n", cont);
        for (int i = 0; i < n; i++) {
            if (i > 0) printf(" ");
            printf("%d", cards[i]);
        }
        printf("\n");
    }

    return 0;
}

