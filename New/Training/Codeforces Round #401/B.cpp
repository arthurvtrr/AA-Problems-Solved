#include <bits/stdc++.h>

using namespace std;

int n;
string a, b;
bool used[1010];

int main() {
    scanf("%d", &n);
    cin >> a >> b;

    int mini = 0, maxi = 0;

    for (int i = 0; i < a.size(); i++) {
        int min_l = 10, min_i = 0, max_l = 10, max_i = 0;
        for (int j = 0; j < b.size(); j++) {
            if (!used[j]) {
                if (min_l > b[j] - '0') {
                    min_l = b[j] - '0';
                    min_i = j;
                }
                if (b[j] - '0' >= a[i] - '0' && b[j] - '0' < max_l) {
                    max_l = b[j] - '0';
                    max_i = j;
                }
            }
        }
        if (max_l != 10) used[max_i] = true;
        else {
            used[min_i] = true;
            mini++;
        }
    }

    for (int i = 0; i < 1010; i++) used[i] = false;

    for (int i = 0; i < a.size(); i++) {
        int min_l = 10, min_i = 0, max_l = 10, max_i = 0;
        for (int j = 0; j < b.size(); j++) {
            if (!used[j]) {
                if (min_l > b[j] - '0') {
                    min_l = b[j] - '0';
                    min_i = j;
                }
                if (b[j] - '0' > a[i] - '0' && b[j] - '0' < max_l) {
                    max_l = b[j] - '0';
                    max_i = j;
                }
            }
        }
        if (max_l != 10) {
            used[max_i] = true;
            maxi++;
        }
        else used[min_i] = true;
    }

    printf("%d\n%d\n", mini, maxi);

    return 0;
}

