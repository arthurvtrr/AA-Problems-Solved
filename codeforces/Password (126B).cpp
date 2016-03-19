#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

#define N 1001000

int lens[N], cont[N];
string s;

void Zfunction() {
    int n = s.size();
    int L = 0, R = 0;

    for (int i = 1; i < n; i++) {
        if (i > R) {
            L = R = i;

            while (R < n && s[R-L] == s[R]) {
                R++;
                cont[R-L]++;
            }
            lens[i] = R-L;
            R--;
        }
        else {
            if (lens[i-L] < R-i+1)
                lens[i] = lens[i-L];
            else {
                L = i;
                while (R < n && s[R-L] == s[R]) {
                    R++;
                    cont[R-L]++;
                }
                lens[i] = R-L;
                R--;
            }
        }
    }
}

int main() {
    cin >> s;
    Zfunction();

    int siz = 0;
    for (int i = s.size() - 1; i >= 0; i--)
        if (lens[i] == s.size() - i)
            if (cont[lens[i]] > 1)
                siz = max(siz, lens[i]);

    if (siz == 0)
        printf("Just a legend");
    else
        for (int i = 0; i < siz; i++)
            printf("%c", s[i]);

    printf("\n");

    return 0;
}
