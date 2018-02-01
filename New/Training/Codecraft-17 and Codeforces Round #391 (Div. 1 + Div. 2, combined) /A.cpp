#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <string>

using namespace std;

string s;
int cont[300];

int main() {
    cin >> s;
    for (int i = 0; i < s.size(); i++)
        cont[s[i] - 'A']++;

    int sol = 10000000;
    sol = min(sol, cont[1]);
    sol = min(sol, cont['a' - 'A'] / 2);
    sol = min(sol, cont['b' - 'A']);
    sol = min(sol, cont['l' - 'A']);
    sol = min(sol, cont['s' - 'A']);
    sol = min(sol, cont['r' - 'A']);
    sol = min(sol, cont['u' - 'A'] / 2);

    printf("%d\n", sol);
    return 0;
}
