#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <string>

using namespace std;

int n;
string s;

int main() {
    scanf("%d", &n);
    cin >> s;

    string sol = "";

    if (n % 2 != 0) {
        for (int i = n - 2; i >= 0; i -= 2)
            sol += s[i];
        for (int i = 0; i < n; i += 2)
            sol += s[i];
    }
    else {
        for (int i = n - 2; i >= 0; i -= 2)
            sol += s[i];
        for (int i = 1; i < n; i += 2)
            sol += s[i];
    }

    cout << sol << endl;
    return 0;
}

