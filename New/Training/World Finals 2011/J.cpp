#include <bits/stdc++.h>

using namespace std;

int c, high[1010], lOdd[1010], lEven[1010];
vector < string > dp[1000100][7];
string conv[1010];
bool possible[1000100];

bool cmp(string a, string b) {
    int x = 0, y = 0, va = 0, vb = 0;
    for (int i = 0; i < a.size()-1; i++) { x *= 10; x += a[i] - '0'; }
    for (int i = 0; i < b.size()-1; i++) { y *= 10; y += b[i] - '0'; }

    if (a.back() == 'H') va = high[x];
    else if (x % 2) va = lOdd[(x-1)/2+1];
    else va = lEven[x/2];

    if (b.back() == 'H') vb = high[y];
    else if (y % 2) vb = lOdd[(y-1)/2+1];
    else vb = lEven[y/2];

    return va > vb;
}

int main() {
    for (int i = 1; i < 1010; i++) {
        string aux = "";
        int x = i;
        while (x) {
            aux += (x % 10) + '0';
            x /= 10;
        }
        reverse(aux.begin(), aux.end());
        conv[i] = aux;
    }

    int pos = 1;
    while (high[pos-1] < 1000000) {
        high[pos] += high[pos-1];
        high[pos] += pos*pos;
        pos++;
    }
    pos = 1;
    while (lOdd[pos-1] < 1000000) {
        lOdd[pos] += lOdd[pos-1];
        lOdd[pos] += (2*(pos-1)+1)*(2*(pos-1)+1);
        pos++;
    }
    pos = 1;
    while (lEven[pos-1] < 1000000) {
        lEven[pos] += lEven[pos-1];
        lEven[pos] += (2*pos)*(2*pos);
        pos++;
    }

    int x = 1000, y = 1000, z = 1000;
    while (high[x] == 0) x--;
    while (lOdd[y] == 0) y--;
    while (lEven[z] == 0) z--;

    int h = x, lo = y, le = z;
    for (int i = 1000000; i >= 0; i--) {
        while (high[h] > i) h--;
        if (high[h] == i && h > 1) dp[i][1].push_back(conv[h] + "H");

        while (lOdd[lo] > i) lo--;
        if (lOdd[lo] == i && lo > 1) dp[i][1].push_back(conv[2*(lo-1)+1] + "L");

        while (lEven[le] > i) le--;
        if (lEven[le] == i && le > 1) dp[i][1].push_back(conv[2*le] + "L");
    }

    possible[0] = true;
    for (int i = 2; i < x; i++)
        for (int j = 1000000; j >= 0; j--)
            if (j + high[i] <= 1000000 && possible[j])
                possible[j + high[i]] = true;

    for (int i = 2; i < y; i++)
        for (int j = 1000000; j >= 0; j--)
            if (j + lOdd[i] <= 1000000 && possible[j])
                possible[j + lOdd[i]] = true;

    for (int i = 2; i < z; i++)
        for (int j = 1000000; j >= 0; j--)
            if (j + lEven[i] <= 1000000 && possible[j])
                possible[j + lEven[i]] = true;

    for (int i = 2; i < 7; i++) {
        for (int j = 1000000; j >= 0; j--) {
            if (!possible[j]) continue;

            h = x, lo = y, le = z;

            while (high[h] > j) h--;
            while (lOdd[lo] > j) lo--;
            while (lEven[le] > j) le--;

            while (h > 1 || lo > 1 || le > 1) {
                int aux = max({high[h], lOdd[lo], lEven[le]});

                if (dp[j - aux][i - 1].size()) {
                    bool valid = true;
                    for (int k = 0; k < i-1; k++)
                        if (dp[j - aux][i - 1][k] == dp[aux][1][0])
                            valid = false;

                    if (valid) {
                        dp[j][i].push_back(dp[aux][1][0]);
                        for (int k = 0; k < i-1; k++)
                            dp[j][i].push_back(dp[j - aux][i - 1][k]);
                        break;
                    }
                }

                if (aux == high[h]) h--;
                else if (aux == lOdd[lo]) lo--;
                else le--;
            }
        }
    }

    for (int i = 0; i <= 1000000; i++)
        for (int j = 0; j < 7; j++)
            sort(dp[i][j].begin(), dp[i][j].end(), cmp);

    int t = 1;
    while (1) {
        scanf("%d", &c);
        if (c == 0) break;

        if (!possible[c]) printf("Case %d: impossible\n", t++);
        else {
            for (int i = 1; i < 7; i++)
                if (dp[c][i].size()) {
                    printf("Case %d:", t++);
                    for (int j = 0; j < dp[c][i].size(); j++)
                        cout << " " << dp[c][i][j];
                    printf("\n");
                    break;
                }
        }
    }

    return 0;
}

