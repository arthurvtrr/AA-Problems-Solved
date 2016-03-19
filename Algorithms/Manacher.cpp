#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

#define N 2000020

int n, lens[N];
string s;

void manacher() {
    int m = 2*n + 1;
    int C = -1, R = 0;

    for (int i = 0; i < m; i++) {
        int mirror = 2*C-i;
        int diff = R - i;

        if(diff > 0)
            lens[i] = min(lens[mirror], diff);

        while (i + lens[i] < m && i - lens[i] > 0) {
            if ((i + lens[i] + 1) % 2 == 0)
                lens[i]++;
            else if (s[(i + lens[i] + 1)/2] == s[(i - lens[i] - 1)/2])
                lens[i]++;
            else
                break;
        }

        if (i + lens[i] > R) {
            C = i;
            R = i + lens[i];
        }
    }
}
