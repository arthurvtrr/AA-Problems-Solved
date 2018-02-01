#include <iostream>

using namespace std;

int t, x, y, quant[100100];
string s;

int main() {
    scanf("%d", &t);
    while (t--) {
        cin >> s;
        scanf("%d %d", &x, &y);
        int quanta = 0, quantb = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'a') quanta++;
            else quantb++;
        }

        for (int i = 0; i < min(quanta, quantb)+1; i++)
            quant[i] = 0;

        int t = quanta < quantb, maxi = max(quanta, quantb);
        while (maxi) {
            if (quant[0] == (t? y : x)) break;
            for (int i = 0; i < min(quanta, quantb)+1; i++) {
                quant[i]++;
                maxi--;
                if (maxi == 0) break;
            }
        }
        quant[min(quanta, quantb)] += maxi;

        string ans = "";
        for (int i = 0; i < min(quanta, quantb); i++) {
            for (int j = 0; j < quant[i]; j++)
                ans += t? 'b' : 'a';
            ans += t? 'a' : 'b';
        }

        while (quant[min(quanta, quantb)]) {
            for (int i = 0; i < min(quant[min(quanta, quantb)], t? y : x); i++)
                ans += t? 'b' : 'a';
            quant[min(quanta, quantb)] -= min(quant[min(quanta, quantb)], t? y : x);
            if (quant[min(quanta, quantb)]) ans += '*';
        }

        cout << ans << endl;
    }

    return 0;
}
