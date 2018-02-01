#include <bits/stdc++.h>

using namespace std;

#define N 120020

int m, t, nxt[30], s[N];
map < string, int > ind;
bool equals[30][30];
string x;

int lens[N];

void Zfunction() {
    int n = m + t + 1;
    int L = 0, R = 0;

    for (int i = 1; i < n; i++) {
        if (i > R) {
            L = R = i;
            while (R < n && equals[s[R-L]][s[R]]) R++;
            lens[i] = R-L;
            R--;
        }
        else {
            if (lens[i-L] < R-i+1) lens[i] = lens[i-L];
            else {
                L = i;
                while (R < n && equals[s[R-L]][s[R]]) R++;
                lens[i] = R-L;
                R--;
            }
        }
    }
}

int main() {
    int aux = 0;
    for (char c = 'A'; c <= 'G'; c++) {
        string a = "", b;
        a += c;
        equals[aux][aux] = true;
        ind[a] = aux++;
        b = a; b += 'b';
        equals[aux][aux] = true;
        ind[b] = aux++;
        b = a; b += '#';
        equals[aux][aux] = true;
        ind[b] = aux++;
    }

    equals[ind["A#"]][ind["Bb"]] = equals[ind["Bb"]][ind["A#"]] = true;
    equals[ind["B"]][ind["Cb"]] = equals[ind["Cb"]][ind["B"]] = true;
    equals[ind["B#"]][ind["C"]] = equals[ind["C"]][ind["B#"]] = true;
    equals[ind["C#"]][ind["Db"]] = equals[ind["Db"]][ind["C#"]] = true;
    equals[ind["D#"]][ind["Eb"]] = equals[ind["Eb"]][ind["D#"]] = true;
    equals[ind["E"]][ind["Fb"]] = equals[ind["Fb"]][ind["E"]] = true;
    equals[ind["E#"]][ind["F"]] = equals[ind["F"]][ind["E#"]] = true;
    equals[ind["F#"]][ind["Gb"]] = equals[ind["Gb"]][ind["F#"]] = true;
    equals[ind["G#"]][ind["Ab"]] = equals[ind["Ab"]][ind["G#"]] = true;

    nxt[ind["A"]] = ind["A#"]; nxt[ind["A#"]] = nxt[ind["Bb"]] = ind["B"];
    nxt[ind["B"]] = ind["C"]; nxt[ind["B#"]] = ind["C#"]; nxt[ind["Cb"]] = ind["C"];
    nxt[ind["C"]] = ind["C#"]; nxt[ind["C#"]] = nxt[ind["Db"]] = ind["D"];
    nxt[ind["D"]] = ind["D#"]; nxt[ind["D#"]] = nxt[ind["Eb"]] = ind["E"];
    nxt[ind["E"]] = ind["F"]; nxt[ind["E#"]] = ind["F#"]; nxt[ind["Fb"]] = ind["F"];
    nxt[ind["F"]] = ind["F#"]; nxt[ind["F#"]] = nxt[ind["Gb"]] = ind["G"];
    nxt[ind["G"]] = ind["G#"]; nxt[ind["G#"]] = nxt[ind["Ab"]] = ind["A"];

    while (1) {
        memset(s, 0, sizeof s);

        scanf("%d %d", &m, &t);
        if (m + t == 0) break;

        s[t] = 29;
        for (int i = 0; i < m; i++) {
            cin >> x;
            s[i+t+1] = ind[x];
        }
        for (int i = 0; i < t; i++) {
            cin >> x;
            s[i] = ind[x];
        }

        bool valid = false;

        for (int i = 0; i < 12; i++) {
            memset(lens, 0, sizeof lens);
            Zfunction();

            for (int j = 0; j < N; j++)
                if (lens[j] == t)
                    valid = true;
            for (int j = 0; j < t; j++)
                s[j] = nxt[s[j]];
        }

        if (valid) printf("S\n");
        else printf("N\n");
    }

    return 0;
}
