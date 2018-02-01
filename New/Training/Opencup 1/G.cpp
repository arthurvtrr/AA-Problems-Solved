#include <bits/stdc++.h>

using namespace std;

int main() {
    int count_ = 0;
    printf("150\n");
    for(int i=0; i<150; i++) {
        int nxt = i, c = 0;
        for(int j=0;j<150;j++) {
            if(j == nxt) {
                printf("O");
                count_++;
                nxt += ++c;
            }
            else printf(".");
        } puts("");
    }
    //printf("%d\n", count_);
    return 0;
}
