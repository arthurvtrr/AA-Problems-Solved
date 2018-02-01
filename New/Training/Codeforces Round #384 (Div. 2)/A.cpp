#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <string>

using namespace std;

int n, a, b;
string s;

int main() {
    scanf("%d %d %d", &n, &a, &b);
    cin >> s;

    if (s[a-1] == s[b-1]) printf("0\n");
    else printf("1\n");

    return 0;
}
