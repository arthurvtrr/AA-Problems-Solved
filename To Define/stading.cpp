#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    freopen("A-large.in", "r", stdin);
    ofstream myfile("test.out");

    int t, sm, ap, need;
    string s;

    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        ap = 0, need = 0;
        cin >> sm >> s;
        for (int j = 0; j < s.size(); j++) {
            int a = s[j] - '0';
            if (a > 0) {
                if (j <= ap) ap += a;
                else {
                    need += j - ap;
                    ap += a + (j - ap);
                }
            }
        }

        printf("Case #%d: %d\n", i+1, need);
        myfile << "Case #" << i+1 << ": " << need << "\n";
    }

    myfile.close();

    return 0;
}
