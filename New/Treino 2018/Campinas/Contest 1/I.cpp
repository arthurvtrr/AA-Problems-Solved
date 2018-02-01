#include <bits/stdc++.h>

using namespace std;

string s;
int perm[5050], inv[5050], ans[5050];

bool prime[1001000];
vector < int > primes;

int main() {
    getline(cin, s);
    vector < int > nums;
    int aux = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            nums.push_back(aux);
            aux = 0;
        }
        else {
            aux *= 10;
            aux += s[i] - '0';
        }
    }
    nums.push_back(aux);

    bool valid = true;

    for (int i = 0; i < nums.size(); i++) {
        int lft = nums[i];
        bool f = false;
        for (int j = 1; j <= nums.size(); j++) {
            if (lft == 0 && perm[j] == 0) {
                perm[j] = i+1;
                f = true;
                break;
            }
            if (perm[j] == 0) lft--;
        }
        if (!f) valid = false;
    }

    if (!valid) {
        for (int i = 2; i < 1001000; i++)
            prime[i] = true;
        for (int i = 2; i < 1001000; i++)
            if (prime[i]) {
                primes.push_back(i);
                for (int j = 2*i; j < 1001000; j += i)
                    prime[j] = false;
            }

        for (int i = 0; i < nums.size(); i++) {
            if (i) printf(" ");
            printf("%d", primes[i]);
        }
        printf("\n");
        return 0;
    }

    for (int i = 1; i <= nums.size(); i++)
        inv[perm[i]] = i;

    for (int i = 1; i <= nums.size(); i++) {
        int x = 0;
        for (int j = 1; j < i; j++)
            if (inv[j] > inv[i])
                x++;
        ans[inv[i]] = x;
    }

    for (int i = 0; i < nums.size(); i++) {
        if (i) printf(" ");
        printf("%d", ans[i+1]);
    }
    printf("\n");

    return 0;
}
