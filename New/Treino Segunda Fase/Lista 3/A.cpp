#include <bits/stdc++.h>

using namespace std;

#define ll long long

string s;
ll coefs[30], aux[3][30];

int main() {
    while (1) {
        cin >> s;
        if (s.size() == 1) break;

        memset(coefs, 0, sizeof coefs);
        memset(aux, 0, sizeof aux);

        vector < int > nums, op;
        int maxd = 0, num = 0, f;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                num *= 10;
                num += s[i] - '0';
                maxd = max(maxd, s[i] - '0');
            }
            else {
                nums.push_back(num);
                num = 0;
                if (s[i] == '=') { f = i+1; break; }
                else if (s[i] == '+') op.push_back(1);
                else op.push_back(2);
            }
        }

        int x = nums[0], ind = 0;
        while (x) {
            aux[0][ind] = x % 10;
            x /= 10;
            ind++;
        }

        for (int i = 1; i < nums.size(); i++) {
            if (op[i-1] == 1) {
                for (int j = 0; j < 30; j++) {
                    coefs[j] += aux[0][j];
                    aux[0][j] = 0;
                }

                int x = nums[i], ind = 0;
                while (x) {
                    aux[0][ind] = x % 10;
                    x /= 10;
                    ind++;
                }
            }
            else {
                int x = nums[i], ind = 0;
                while (x) {
                    aux[1][ind] = x % 10;
                    x /= 10;
                    ind++;
                }

                for (int j = 0; j < 15; j++)
                    for (int k = 0; k < 15; k++)
                        aux[2][j+k] += aux[0][j] * aux[1][k];

                for (int j = 0; j < 30; j++) {
                    aux[0][j] = aux[2][j];
                    aux[1][j] = aux[2][j] = 0;
                }
            }
        }

        for (int i = 0; i < 30; i++) {
            coefs[i] += aux[0][i];
            aux[0][i] = 0;
        }

        nums.clear(); op.clear();

        for (int i = f; i < s.size(); i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                num *= 10;
                num += s[i] - '0';
                maxd = max(maxd, s[i] - '0');
            }
            else {
                nums.push_back(num);
                num = 0;
                if (s[i] == '+') op.push_back(1);
                else op.push_back(2);
            }
        }
        nums.push_back(num);

        x = nums[0], ind = 0;
        while (x) {
            aux[0][ind] = x % 10;
            x /= 10;
            ind++;
        }

        for (int i = 1; i < nums.size(); i++) {
            if (op[i-1] == 1) {
                for (int j = 0; j < 30; j++) {
                    coefs[j] -= aux[0][j];
                    aux[0][j] = 0;
                }

                int x = nums[i], ind = 0;
                while (x) {
                    aux[0][ind] = x % 10;
                    x /= 10;
                    ind++;
                }
            }
            else {
                int x = nums[i], ind = 0;
                while (x) {
                    aux[1][ind] = x % 10;
                    x /= 10;
                    ind++;
                }

                for (int j = 0; j < 15; j++)
                    for (int k = 0; k < 15; k++)
                        aux[2][j+k] += aux[0][j] * aux[1][k];

                for (int j = 0; j < 30; j++) {
                    aux[0][j] = aux[2][j];
                    aux[1][j] = aux[2][j] = 0;
                }
            }
        }

        for (int i = 0; i < 30; i++) {
            coefs[i] -= aux[0][i];
            aux[0][i] = 0;
        }

        int fdif = -1;
        for (int i = 0; i < 30; i++)
            if (coefs[i] != 0) {
                fdif = i;
                break;
            }

        if (fdif == -1) printf("%d+\n", max(2, maxd+1));
        else {
            set < int > divs;
            int x = abs(coefs[fdif]);
            for (int i = 1; i <= (int)sqrt(x) + 1; i++)
                if (x % i == 0) {
                    divs.insert(x / i);
                    divs.insert(i);
                }

            vector < int > ans;
            for (int v : divs) {
                if (v < max(2, maxd+1)) continue;

                for (int i = 0; i < 30; i++)
                    aux[0][i] = coefs[i];

                bool valid = true;
                for (int i = 0; i < 29; i++) {
                    aux[0][i+1] += aux[0][i] / v;
                    aux[0][i] %= v;
                }

                for (int i = 0; i < 30; i++)
                    if (aux[0][i] != 0)
                        valid = false;

                if (valid) ans.push_back(v);
            }

            for (int i = 0; i < ans.size(); i++) {
                if (i) printf(" ");
                printf("%d", ans[i]);
            }

            if (ans.empty()) printf("*");
            printf("\n");
        }
    }
    return 0;
}
