#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n;
string s;
vector < int > nextD, nextR;
bool blocked[200200];

int main() {
    scanf("%d", &n);
    cin >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'D') nextD.push_back(i);
        else nextR.push_back(i);
    }

    int posd = 0, posr = 0, ind = 0;

    while (posd < nextD.size() && posr < nextR.size()) {
        if (!blocked[ind]) {
            if (s[ind] == 'D') {
                blocked[nextR[posr]] = true;
                posr++;
            }
            else {
                blocked[nextD[posd]] = true;
                posd++;
            }
        }

        ind++;
        ind %= n;
    }

    if (posd >= nextD.size()) printf("R\n");
    else printf("D\n");

    return 0;
}
