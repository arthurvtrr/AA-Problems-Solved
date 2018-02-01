#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <string>

using namespace std;

int n;
string s;

bool ignored[110];

int main() {
    scanf("%d", &n);
    cin >> s;

    for (int i = 0; i < n - 2; i++) {
        if (s[i] == 'o' && s[i+1] == 'g' && s[i+2] == 'o') {
            s[i] = s[i+1] = s[i+2] = '*';
            i += 3;
            while (i+1 < n && s[i] == 'g' && s[i+1] == 'o') {
                ignored[i] = ignored[i+1] = true;
                i += 2;
            }
            i--;
        }
    }

    for (int i = 0; i < n; i++)
        if (!ignored[i])
            printf("%c", s[i]);
    printf("\n");
    return 0;
}
