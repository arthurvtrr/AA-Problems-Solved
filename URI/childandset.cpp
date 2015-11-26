#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair < int, int > pii;

bool compare(pii a, pii b) {
    return a.second < b.second;
}

int main() {
    int sum, limit;
    scanf("%d %d", &sum, &limit);
    pii nums[110000];

    for (int i = 1; i <= limit; i++) {
        nums[i].first = i;
        nums[i].second = i & -i;
    }

    sort(nums, nums+limit+1, compare);

    vector < int > chosen;
    for (int i = limit; i >= 1; i--) {
        if (nums[i].second <= sum) {
            sum -= nums[i].second;
            chosen.push_back(nums[i].first);
        }
    }

    if (sum != 0) printf("-1\n");
    else {
        printf("%d\n", chosen.size());
        for (int i = 0; i < chosen.size(); i++) {
            printf("%d", chosen[i]);
            if (i < chosen.size() - 1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
