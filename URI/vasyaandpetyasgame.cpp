#include <stdio.h>
#include <vector>

using namespace std;

vector < int > sol;
bool prime[1100];

void sieve(int n) {
    for (int i = 0; i < 1100; i++) prime[i] = true;
    prime[0] = false;
    prime[1] = false;
    for (int i = 2; i < n+1; i++) {
        if (prime[i]) {
            sol.push_back(i);
            for (int j = i*i; j < n+1; j*=i)
                if (prime[j]) sol.push_back(j);
            for (int j = i+i; j < n+1; j+=i)
                prime[j] = false;
        }
    }

    printf("%d\n", sol.size());
    for (int i = 0; i < sol.size(); i++) {
        if (i > 0) printf(" ");
        printf("%d", sol[i]);
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);
    sieve(n);
    return 0;
}
