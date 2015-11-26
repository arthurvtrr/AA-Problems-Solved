#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int toRemove[222000], aux[222000];

int main() {
    string s, s1 = "", s2 = "", s3 = "";
    cin >> s;
    int freq = 0, x;
    for (int i = 0; i < s.size()-1; i++) {
        if (s[i] == s[i+1]) freq++;
        else freq = 0;
        if (freq > 1) toRemove[i] = 1;
    }

    for (int i = 0; i < s.size(); i++)
        if (toRemove[i] == 0) s1 += s[i];
    memset(toRemove, 0, sizeof toRemove);

    for (int i = 0; i < s1.size()-1; i++)
        if (s1[i] == s1[i+1]) aux[i] = 1;

    x = s1.size()-5;
    for (int i = 0; i < x; i++)
        if (aux[i] == 1 && aux[i+2] == 1 && aux[i+4] == 1) {
            toRemove[i+2] = 1;
            i += 2;
        }

    for (int i = 0; i < s1.size(); i++)
        if (toRemove[i] == 0) s2 += s1[i];
    memset(toRemove, 0, sizeof toRemove);
    memset(aux, 0, sizeof aux);

    for (int i = 0; i < s2.size()-1; i++)
        if (s2[i] == s2[i+1]) aux[i] = 1;

    x = s2.size()-3;
    for (int i = 0; i < x; i++)
        if (aux[i] == 1 && aux[i+2] == 1)
            toRemove[i+2] = 1;

    for (int i = 0; i < s2.size(); i++)
        if (toRemove[i] == 0) s3 += s2[i];

    cout << s3 << "\n";

    return 0;
}
