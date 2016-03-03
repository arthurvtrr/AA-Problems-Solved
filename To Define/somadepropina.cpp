#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int main() {
    long long int1 = 0, int2 = 0;
    double dec1 = 0, dec2 = 0;
    string s1, s2, cpf = "00000000000";
    cin >> s1;
    cin >> s2;

    bool p1 = false, p2 = false;
    int ct = 0, ctd1 = 0, ctd2 = 0;
    for (char c : s1) {
        if (ct < 11) {
            if (isdigit(c)) {
                cpf[ct] = c;
                ct++;
            }
        }
        else {
            if (c == '.') p1 = true;
            if (isdigit(c) && !p1) {
                int1 *= 10;
                int1 += c - '0';
            }
            else if (isdigit(c) && p1 && ctd1 < 2) {
                dec1 *= 10;
                dec1 += c - '0';
                ctd1++;
            }
        }
    }

    for (char c : s2) {
        if (c == '.') p2 = true;
        if (isdigit(c) && !p2) {
            int2 *= 10;
            int2 += c - '0';
        }
        else if (isdigit(c) && p2 && ctd2 < 2) {
            dec2 *= 10;
            dec2 += c - '0';
            ctd2++;
        }
    }

    cout << "cpf " << cpf << "\n";

    long double a = int1, b = int2;
    for (int i = 0; i < ctd1; i++) dec1 *= 0.1;
    for (int i = 0; i < ctd2; i++) dec2 *= 0.1;
    a += dec1;
    b += dec2;
    long double sol = a + b;

    printf("%.2Lf\n", sol);
    return 0;
}
