#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string cpf = "";
long long nat_part[2], frac_part[2];

void check_string(string s, int num) {
    int cont = 0, after_point = 0;
    bool point_found = false;

    for (int i = 0; i < s.size(); i++) {
        if (num == 0 && cont < 11 && isdigit(s[i])) {
            cpf += s[i];
            cont++;
        }
        else if (s[i] == '.')
            point_found = true;
        else if (isdigit(s[i]) && !point_found) {
            nat_part[num] *= 10;
            nat_part[num] += s[i] - '0';
        }
        else if (isdigit(s[i]) && after_point < 2) {
            frac_part[num] *= 10;
            frac_part[num] += s[i] - '0';
            after_point++;
        }
    }
}

int main() {
    string a, b;
    cin >> a >> b;

    check_string(a, 0);
    check_string(b, 1);

    cout << "cpf " << cpf << endl;

    long double sol = nat_part[0] + nat_part[1];
    sol += 0.01 * frac_part[0] + 0.01 * frac_part[1];

    printf("%.2Lf\n", sol);

    return 0;
}

