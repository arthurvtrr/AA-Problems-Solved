#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, k, x;
set < pii > nums;

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x);
        nums.insert(pii(x, i));
    }

    vector < pii > moves;
    int min_inst = (*nums.rbegin()).first - (*nums.begin()).first;
    while (k--) {
        pii x = (*nums.rbegin()), y = (*nums.begin());

        nums.erase(x); nums.erase(y);
        nums.insert(pii(x.first-1, x.second)); nums.insert(pii(y.first+1, y.second));

        if ((*nums.rbegin()).first - (*nums.begin()).first > min_inst) break;
        min_inst = (*nums.rbegin()).first - (*nums.begin()).first;
        moves.push_back(pii(x.second, y.second));
    }

    printf("%d %d\n", min_inst, moves.size());
    for (int i = 0; i < moves.size(); i++)
        printf("%d %d\n", moves[i].first, moves[i].second);

    return 0;
}
