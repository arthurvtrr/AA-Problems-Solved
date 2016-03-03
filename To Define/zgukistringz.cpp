#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int occursa[30], occursb[30], occursc[30], aux[30];
string a, b, c;
int numb, numc, sum, subb, subc;

int main() {
    cin >> a >> b >> c;

    for (char l : a) occursa[l - 'a']++;
    for (char l : b) occursb[l - 'a']++;
    for (char l : c) occursc[l - 'a']++;

    numb = a.size();
    for (int i = 0; i < 26; i++)
        if (occursb[i]) numb = min(numb, occursa[i] / occursb[i]);

    for (int i = numb; i >= 0; i--) {
        for (int j = 0; j < 26; j++) aux[j] = occursa[j] - (occursb[j] * i);

        numc = a.size();
        for (int j = 0; j < 26; j++)
            if (occursc[j]) numc = min(numc, aux[j] / occursc[j]);

        if (i + numc > sum) {
            sum = i + numc;
            subb = i;
            subc = numc;
        }
    }

    for (int i = 0; i < subb; i++)
        cout << b;
    for (int i = 0; i < subc; i++)
        cout << c;
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < occursa[i] - (occursb[i] * subb) - (occursc[i] * subc); j++) {
            char l = i + 'a';
            cout << l;
        }
    cout << "\n";

    return 0;
}
