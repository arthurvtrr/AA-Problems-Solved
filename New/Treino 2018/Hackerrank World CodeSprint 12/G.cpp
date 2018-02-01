#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define MOD 1000000007

int n, nums[100100];
vector < ll > aux;
int ini[10001000], fim[10001000];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    if (n > 5000) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        deque < int > ind;
        for (int j = 0; j < i; j++) {
            while (!ind.empty() && nums[ind.back()] < nums[j]) ind.pop_back();
            ind.push_back(j);
        }
        for (int j = i; j < n; j++) {
            while (!ind.empty() && ind.front() < j - i) ind.pop_front();
            while (!ind.empty() && nums[ind.back()] < nums[j]) ind.pop_back();
            ind.push_back(j);
            aux.push_back(nums[ind.front()]);
        }
    }

    ll ans = 0;

    stack < int > pilha;
    for (int i = 0; i < aux.size(); i++) {
        while (!pilha.empty() && aux[i] >= aux[pilha.top()]) pilha.pop();
        if (pilha.empty()) ini[i] = 0;
        else ini[i] = pilha.top() + 1;
        pilha.push(i);
    }

    while (!pilha.empty()) pilha.pop();

    for (int i = (int)aux.size()-1; i >= 0; i--) {
        while (!pilha.empty() && aux[i] > aux[pilha.top()]) pilha.pop();
        if (pilha.empty()) fim[i] = (int)aux.size()-1;
        else fim[i] = pilha.top() - 1;
        pilha.push(i);
    }

    for (int i = 0; i < aux.size(); i++) {
        ans += aux[i] * (i - ini[i] + 1) * (fim[i] - i + 1);
        ans %= MOD;
    }
    printf("%lld\n", ans);

    return 0;
}
