#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int lens[220000];
string s, aux;

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

int main() {
    while (cin >> s) {
        aux = s;
        reverse(s.begin(), s.end());
        s += '$';
        s += aux;

        Zfunction();

        int pos = 0;
        for (int i = aux.size(); i < s.size(); i++)
            if (lens[i] >= lens[pos] && i + lens[i] == s.size())
                pos = i;

        cout << aux;
        for (int i = pos-1; i > aux.size(); i--)
            cout << s[i];
        cout << endl;
    }
    return 0;
}
