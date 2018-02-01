#include <bits/stdc++.h>

using namespace std;

int n, nums[100100], initial[100100];
vector < int > moves;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    bool possible = true;

    for (int i = 0; i < n-1; i++)
        if (nums[i] > 0 && nums[i] == nums[i+1])
            possible = false;

    for (int i = 0; i < n; i++)
        if (nums[i] == 3) {
            int l = 0, r = 0;
            while (i-l-1 >= 0 && initial[i-l-1] == 0 && l < 2) l++;
            while (i+r+1 < n && initial[i+r+1] == 0 && r < 2) r++;

            if (l > 0 && r > 1) {
                moves.push_back(i-1);
                moves.push_back(i+2);
                moves.push_back(i+1);
                moves.push_back(i);
            }
            else if (l > 1 && r > 0) {
                moves.push_back(i+1);
                moves.push_back(i-2);
                moves.push_back(i-1);
                moves.push_back(i);
            }
            else {
                possible = false;
                break;
            }

            initial[i] = 3;
        }

    for (int i = 0; i < n; i++)
        if (nums[i] == 2) {
            int l = 0, r = 0;
            while (i-l-1 >= 0 && initial[i-l-1] == 0 && l < 2) l++;
            while (i+r+1 < n && initial[i+r+1] == 0 && r < 2) r++;

            if (l > 0) {
                moves.push_back(i-1);
                moves.push_back(i);
            }
            else if (r > 0) {
                moves.push_back(i+1);
                moves.push_back(i);
            }
            else {
                possible = false;
                break;
            }

            initial[i] = 2;
        }

    for (int i = 0; i < n; i++)
        if (nums[i] == 1)
            moves.push_back(i);

    if (!possible) printf("-1\n");
    else {
        printf("%d\n", moves.size());
        for (int i = 0; i < moves.size(); i++) {
            if (i) printf(" ");
            printf("%d", moves[i] + 1);
        }
        printf("\n");
    }

    return 0;
}

