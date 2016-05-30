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

            while (R < n && s[R-L] == s[R])
                R++;
            lens[i] = R-L;
            R--;
        }
        else {
            if (lens[i-L] < R-i+1)
                lens[i] = lens[i-L];
            else {
                L = i;
                while (R < n && s[R-L] == s[R])
                    R++;
                lens[i] = R-L;
                R--;
            }
        }
    }
}

int main() {
    while (1) {
        for (int i = 0; i < N; i++) lens[i] = 0;

        cin >> s;

        if (s.size() == 1 && s[0] == '.') break;

        Zfunction();

        int sol = 1;
        for (int i = 1; i < s.size(); i++) {
            bool possible = true;
            for (int j = i; j < s.size(); j += i)
                if (lens[j] < i) possible = false;

            if (possible) {
                sol = s.size() / i;
                break;
            }
        }

        printf("%d\n", sol);
    }
    return 0;
}

