#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int t, n, nums[2200], used[2200];
vector < int > aux;

int find_pos(int x, bool inverted) {
    int ini = 0, fim = aux.size();
    while (ini < fim) {
        int meio = (ini + fim) / 2;

        if (aux[meio] == x) return meio;
        else if (aux[meio] < x && !inverted) ini = meio+1;
        else if (aux[meio] < x) fim = meio;
        else if (aux[meio] > x && !inverted) fim = meio;
        else if (aux[meio] > x) ini = meio+1;
    }
    return ini;
}

int main() {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);

        aux.clear();
        for (int i = n-1; i >= 0; i--) {
            int index = find_pos(nums[i], true);

            if (index == aux.size()) aux.push_back(nums[i]);
            else aux[index] = nums[i];

            used[i] = index + 1;
        }

        aux.clear();
        for (int i = n-1; i >= 0; i--) {
            int index = find_pos(nums[i], false);

            if (index == aux.size()) aux.push_back(nums[i]);
            else aux[index] = nums[i];

            used[i] += index + 1;
        }

        int sol = 0;
        for (int i = 0; i < n; i++)
            sol = max(used[i] - 1, sol);

        printf("%d\n", sol);
    }
    return 0;
}
