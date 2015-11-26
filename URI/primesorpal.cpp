#include <stdio.h>
#include <string>

using namespace std;

int prime[2000200];
int palindrome[2000200];

void sieve(int n) {
    for (int i = 0; i < n+1; i++)
        prime[i] = 1;

    prime[0] = 0, prime[1] = 0;
    for (int i = 0; i < n+1; i++) {
        if (prime[i])
            for (long long j = i+i; j < n+1; j += i)
                prime[j] = 0;
    }

    for (int i = 1; i < n+1; i++)
        prime[i] += prime[i-1];
}

void calc_p(int n) {
    for (int i = 0; i < n+1; i++)
        palindrome[i] = 1;

    palindrome[0] = 0;

    for (int i = 0; i < n+1; i++) {
        int digits[50], s = 0, x = i;
        while (x > 0) {
            digits[s++] = x % 10;
            x /= 10;
        }
        for (int j = 0; j < s / 2; j++)
            if (digits[j] != digits[s - j - 1])
                palindrome[i] = 0;
    }

    for (int i = 1; i < n+1; i++)
        palindrome[i] += palindrome[i-1];
}

int main() {
    sieve(2000010);
    calc_p(2000010);
    double p, q, a;
    scanf("%lf %lf", &p, &q);
    a = p/q;
    int sol = 2000010;
    while (prime[sol] > a * palindrome[sol]) sol--;

    printf("%d\n", sol);
    return 0;
}
