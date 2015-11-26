#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {
    int k;
    string s;
    map < char, int > found;
    scanf("%d", &k);
    cin >> s;

    for (char c : s)
        found[c] = 1;

    if (found.size() < k) printf("NO\n");
    else {
        printf("YES\n");
        vector < string > subs;
        string sub = s.substr(0,1);
        found[s[0]] = 0;
        for (int i = 1; i < s.size(); i++) {
            if (!found.count(s[i]) || found[s[i]] == 0)
                sub += s[i];
            else {
                if (k > 1) {
                    subs.push_back(sub);
                    sub = "";
                    sub += s[i];
                    k--;
                    found[s[i]] = 0;
                }
                else {
                    sub += s.substr(i, s.size());
                    subs.push_back(sub);
                    sub = "";
                    break;
                }
            }
        }
        subs.push_back(sub);

        for (string s1 : subs)
            if (s1.size() > 0)
                cout << s1 << endl;
    }

    return 0;
}
