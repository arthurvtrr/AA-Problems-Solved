#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

#define N 1001000

int lens[N];
string s;

void Zfunction() {
    int n = s.size();
    int L = 0, R = 0;

    for (int i = 1; i < n; i++) {
        if (i > R) {
            L = R = i;
            while (R < n && s[R-L] == s[R]) R++;
            lens[i] = R-L;
            R--;
        }
        else {
            if (lens[i-L] < R-i+1)
                lens[i] = lens[i-L];
            else {
                L = i;
                while (R < n && s[R-L] == s[R]) R++;
                lens[i] = R-L;
                R--;
            }
        }
    }
}
