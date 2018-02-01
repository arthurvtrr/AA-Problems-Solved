#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <string>

using namespace std;

int n, ti;
string s;

int main() {
    scanf("%d", &n);

    int y = 0;

    bool possible = true;

    for (int i = 0; i < n; i++) {
        scanf("%d", &ti);
        cin >> s;

        if (y == 0 && s != "South") possible = false;
        else if (y == 20000 && s != "North") possible = false;
        else if (s == "North") {
            if (y - ti < 0) possible = false;
            else y -= ti;
        }
        else if (s == "South") {
            if (y + ti > 20000) possible = false;
            else y += ti;
        }
    }

    if (y != 0) possible = false;

    if (possible) printf("YES\n");
    else printf("NO\n");

    return 0;
}

