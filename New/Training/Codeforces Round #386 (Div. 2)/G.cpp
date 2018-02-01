#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <deque>

using namespace std;

#define pii pair < int, int >

int n, t, k, nums[200200];
bool used[200200];
vector < int > graph[200200];
deque < pii > left[200200];

int main() {
    scanf("%d %d %d", &n, &t, &k);
    for (int i = 0; i < t; i++)
        scanf("%d", &nums[i]);

    int ind = 2, last = 1, quant = 1;

    for (int i = 0; i < t; i++) {
        bool connected = false;
        int aux = nums[i];

        while (aux) {
            if (!connected) {
                graph[last].push_back(ind);
                connected = true;
            }
            else {
                left[i+1].push_back(make_pair(last, ind));
                quant++;
            }
            ind++;
            aux--;
        }

        last = ind - nums[i];
    }

    if (quant < k) printf("-1\n");
    else {
        int a = 1;

        while (quant > k) {
            while ((left[a].size() == 0 || left[a+1].size() == 0 || used[left[a+1].back().second]) && a < n) a++;

            if (left[a].size() == 0 || left[a+1].size() == 0) {
                printf("-1\n");
                return 0;
            }
            else {
                pii x = left[a].back(), y = left[a+1].back();
                graph[x.first].push_back(x.second);
                left[a].pop_back(); left[a+1].pop_back();
                left[a+1].push_front(make_pair(x.second, y.second));
                used[y.second] = true;
                quant--;
            }
        }

        if (quant > k) printf("-1\n");
        else {
            for (int i = 1; i <= n; i++)
                while (left[i].size() > 0) {
                    pii x = left[i].back();
                    left[i].pop_back();
                    graph[x.first].push_back(x.second);
                }
        }

        printf("%d\n", n);

        for (int i = 1; i <= n; i++)
            for (int v : graph[i])
                printf("%d %d\n", i, v);
    }

    return 0;
}
