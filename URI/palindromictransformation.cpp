#include <stdio.h>
#include <algorithm>

using namespace std;

int dif(char a, char b) {
    return min(abs(a-b), min(a,b)+26-max(a,b));
}

int main() {
    int n, p;
    char word[110000];
    scanf("%d %d", &n, &p);
    scanf("%s", word);

    int total = 0, l = 0, r = 0, half = ceil(1.0*n/2);

    for (int i = 0; i < half - (n % 2 == 0? 0 : 1); i++) {
        total += dif(word[i], word[n-i-1]);
        if (word[i] != word[n-i-1] && p <= half) {
            if (i < p-1 && l == 0) l = p-i-1;
            else if (i > p-1) r = i+1-p;
        }
    }
    total += 2*min(l,r) + max(l,r);
    l = 0, r = 0;

    for (int i = half; i < n; i++)
        if (word[i] != word[n-i-1] && p > half) {
            if (i < p-1 && l == 0) l = p-i-1;
            else if (i > p-1) r = i+1-p;
        }
    total += 2*min(l,r) + max(l,r);

    printf("%d\n", total);
    return 0;
}
