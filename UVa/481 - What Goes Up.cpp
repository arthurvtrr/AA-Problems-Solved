#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

map < int, int > pred;
int nums[1000100], aux[1000100], pos[1000100];

int find_pos(int x, int len) {
    int ini = 0, fim = len;
    while (ini < fim) {
        int meio = (ini + fim) / 2;

        if (aux[meio] == x) return meio;
        else if (aux[meio] < x) ini = meio+1;
        else fim = meio;
    }
    return ini;
}

int main() {
    int n, cont = 0, siz = 0, fim = 0;

    while (scanf("%d", &n) != EOF) {
        if (n == -10) break;
        nums[cont++] = n;
    }

    for (int i = 0; i < cont; i++) {
        int index = find_pos(nums[i], siz);

        aux[index] = nums[i];
        pos[index] = i;
        pred[i] = index? pos[index-1] : -1;

        if (index + 1 > siz) {
            siz = index + 1;
            fim = i;
        }
    }

    vector < int > sol;

    int p = fim;
    while (p != -1) {
        sol.push_back(nums[p]);
        p = pred[p];
    }

    printf("%d\n-\n", siz);
    for (int i = siz-1; i >= 0; i--)
        printf("%d\n", sol[i]);

    return 0;
}
