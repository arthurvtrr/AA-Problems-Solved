#include <iostream>
#include <stdio.h>

using namespace std;

int cont[27];

int main() {
	string s;
	cin >> s;
	for (char c : s)
		cont[c - 'a']++;
	int ones= 0;
	for (int i : cont)
		if (i % 2 != 0)
			ones++;
	if (ones < 2) printf("First\n");
	else if (s.size() % 2 == 0) printf("Second\n");
	else printf("First\n");
	return 0;
}
