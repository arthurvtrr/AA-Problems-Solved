#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, nums[3030], m, group[3030];
bool visited[3030], used[3030];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &nums[i]);
    scanf("%d", &m);

    int atual = 0, g = 1;
    vector < pii > moves;
    for (int i = 1; i <= n; i++)
        if (!visited[i]) {
            int aux = i, cont = 0;
            visited[i] = true;
            group[i] = g;

            while (nums[aux] != i) {
                visited[nums[aux]] = true;
                group[nums[aux]] = g;
                cont++;
                aux = nums[aux];
            }
            atual += cont;
            g++;
        }

    while (atual > m) {
        int pos = 1;
        while (pos == nums[pos]) pos++;

        int mini = n, aux = pos;
        while (nums[aux] != pos) {
            mini = min(mini, nums[aux]);
            aux = nums[aux];
        }
        moves.push_back(pii(pos, mini));
        swap(nums[pos], nums[mini]);
        atual--;
    }

    int pos = 1;
    used[group[1]] = true;
    while (atual < m) {
        while (used[group[pos]]) pos++;
        moves.push_back(pii(1, pos));
        used[group[pos]] = true;
        atual++; pos++;
    }

    printf("%d\n", moves.size());
    for (int i = 0; i < moves.size(); i++) {
        if (i) printf(" ");
        printf("%d %d", moves[i].first, moves[i].second);
    }
    printf("\n");

    return 0;
}
