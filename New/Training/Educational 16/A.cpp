#include <bits/stdc++.h>

using namespace std;

string s;

int main() {
    cin >> s;
    if (s == "a8" || s == "a1" || s == "h8" || s == "h1") printf("3\n");
    else if (s[0] == 'a' || s[0] == 'h' || s[1] == '1' || s[1] == '8') printf("5\n");
    else printf("8\n");

    return 0;
}
