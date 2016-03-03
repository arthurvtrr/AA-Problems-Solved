#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>

using namespace std;

int main() {
    string x;

    cin >> x;

    int result = 0;
    for (int i = x.size()-1; i >= 0; i--) {
        if (x[i] == '4') result += pow(2, x.size() - i - 1);
        if (x[i] == '7') result += pow(2, x.size() - i);
    }

    printf("%d\n", result);
    return 0;
}
