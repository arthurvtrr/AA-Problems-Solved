#include <bits/stdc++.h>

using namespace std;

int p, x, y;

set < int > nums;
vector < int > aux;

int main() {
    scanf("%d %d %d", &p, &x, &y);

    for (int i = y; i <= y + 30000; i++) {
        int a = (i / 50) % 475;
        for (int j = 0; j < 25; j++) {
            a = (a * 96 + 42) % 475;
            nums.insert(a + 26);
        }
        if (nums.count(p)) aux.push_back(i);
        nums.clear();
    }

    int ans = 100000000;
    for (int i = 0; i < aux.size(); i++) {
        int dist = 1000000000;

        if (aux[i] < x && (x - aux[i]) % 50 == 0) dist = 0;
        else if (aux[i] > x && (aux[i] - x) % 100 == 0) dist = (aux[i] - x) / 100;
        else if (aux[i] > x && (aux[i] - x) % 50 == 0) dist = (aux[i] + 50 - x) / 100;
        else if (aux[i] == x) dist = 0;

        ans = min(ans, dist);
    }
    printf("%d\n", ans);

    return 0;
}
