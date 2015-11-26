#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int fat[10];
    fat[1] = 1;
    for (int i = 2; i < 10; i++)
        fat[i] = i * fat[i-1];

    int n;
    while (scanf("%d", &n) != EOF) {
        int sol = 0;
        for (int i = 9; i >= 1; i--) {
            while (fat[i] <= n) {
                sol++;
                n -= fat[i];
            }
        }
        printf("%d\n", sol);
    }
    return 0;
}
