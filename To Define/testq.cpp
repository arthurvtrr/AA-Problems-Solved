#include <bits/stdc++.h>

using namespace std;

bool isPrime(int num) {
	if (num != 2 && num % 2 == 0) return false;

	for (int i = 3; i <= sqrt(num); i += 2)
		if(num % i == 0)
			return false;

	return true;
}

int main() {
    printf("%d", isPrime(1));
    return 0;
}
