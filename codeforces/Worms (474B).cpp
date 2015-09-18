#include <stdio.h>

int worms[100000];
int labels[100000];
int n, m, k, i, j;
int sum = 0;

void showPiles() {
    for(i=0;i<m;i++) {
        int l = 0, r = n, m;
        int found = 0;
        while (l < r) {
            m = (l+r)/2;
            if (worms[m] < labels[i]) {
                l = m+1;
            }
            else if (worms[m] > labels[i]) {
                r = m;
            }
            else {
                printf("%d\n", m+1);
                found = 1;
                break;
            }

        }
    if (found == 0)
        printf("%d\n", r+1);
    }
}

int main()
{
    scanf("%d", &n);
    for (i=0;i<n;i++) {
        scanf("%d", &k);
        sum += k;
        worms[i] = sum;
    }

    scanf("%d", &m);
    for (j=0;j<m;j++) {
        scanf("%d", &k);
        labels[j] = k;
    }

    showPiles();

    return 0;
}