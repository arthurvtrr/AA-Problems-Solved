#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <map>

using namespace std;

int n, k, x, y;

struct coord {
    int x;
    bool in;
    int id;
};

bool cmp(coord a, coord b) {
    if (a.x == b.x)
        return a.in > b.in;
    return a.x < b.x;
}

vector < coord > nums;

int main() {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        nums.push_back((coord) {x, true, i+1});
        nums.push_back((coord) {y, false, i+1});
    }

    sort(nums.begin(), nums.end(), cmp);

    int sol = 0, quant = 0, pos = -1;

    map < int, int > ind;
    vector < int > events;
    vector < bool > valid;

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i].in) {
            events.push_back(nums[i].x);
            valid.push_back(true);
            ind[nums[i].id] = (int)events.size() - 1;
        }
        else {
            valid[ind[nums[i].id]] = false;
        }

        if (quant == k)
            sol = max(sol, nums[i].x - events[pos] + 1);

        if (!nums[i].in && ind[nums[i].id] <= pos)
            quant--;

        while (pos < (int)events.size()-1 && quant < k) {
            pos++;
            if (valid[pos]) quant++;
        }
    }

    quant = 0, pos = -1;
    ind.clear(); events.clear(); valid.clear();

    vector < int > used;

    for (int i = 0; i < nums.size(); i++) {
        if (quant == k && nums[i].x - events[pos] + 1 == sol) {
            for (map < int, int >::iterator it = ind.begin(); it != ind.end(); it++)
                if (valid[it->second] && it->second <= pos)
                    used.push_back(it->first);

            break;
        }

        if (nums[i].in) {
            events.push_back(nums[i].x);
            valid.push_back(true);
            ind[nums[i].id] = (int)events.size() - 1;
        }
        else {
            valid[ind[nums[i].id]] = false;
        }

        if (!nums[i].in && ind[nums[i].id] <= pos)
            quant--;

        while (pos < (int)events.size()-1 && quant < k) {
            pos++;
            if (valid[pos]) quant++;
        }
    }

    printf("%d\n", sol);

    if (used.empty())
        for (int i = 1; i <= k; i++)
            used.push_back(i);

    for (int i = 0; i < used.size(); i++) {
        if (i > 0) printf(" ");
        printf("%d", used[i]);
    }
    printf("\n");

    return 0;
}
