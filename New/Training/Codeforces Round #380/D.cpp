#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

int n, a, b, k;
char nums[200200];

vector < pair < int, int > > intervals;

int main() {
    scanf("%d %d %d %d", &n, &a, &b, &k);
    scanf("%s", nums);
    nums[n] = '1';

    int ini = 0, quant = 0;

    for (int i = 0; i <= n; i++) {
        if (nums[i] == '1') {
            if (i - ini >= b) {
                quant += (i - ini) / b;
                intervals.push_back(make_pair(ini+1, i));
            }
            ini = i+1;
        }
    }

    vector < int > pos;
    int left = quant - a + 1;

    for (int i = 0; i < intervals.size(); i++) {
        int x = 1;
        while (intervals[i].first - 1 + x * b <= intervals[i].second && left > 0) {
            pos.push_back(intervals[i].first - 1 + x * b);
            left--;
            x++;
        }
    }

    printf("%d\n", pos.size());
    for (int i = 0; i < pos.size(); i++) {
        if (i > 0) printf(" ");
        printf("%d", pos[i]);
    }
    printf("\n");
    return 0;
}

