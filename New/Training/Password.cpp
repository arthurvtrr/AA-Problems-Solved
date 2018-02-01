#include <bits/stdc++.h>

using namespace std;

#define N 2002000

string s;
int lens[N];

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
    cin >> s;
    string aux = "$";
    aux += s;
    s += aux;

    Zfunction();

    vector < int > fim;

    int mid = 0;
    for (int i = aux.size() + 1; i < s.size(); i++)
        if (lens[i] > 0) {
            if (i + lens[i] == s.size()) {
                fim.push_back(lens[i]);
                mid = max(mid, lens[i]-1);
            }
            else
                mid = max(mid, lens[i]);
        }

    int siz = fim.size();
    if (siz == 0 || fim[siz-1] > mid) printf("Just a legend\n");
    else {
        int pos = 0;
        while (fim[pos] > mid) pos++;

        for (int i = 0; i < fim[pos]; i++)
            printf("%c", s[i]);
        printf("\n");
    }

    return 0;
}
