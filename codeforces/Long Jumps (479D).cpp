#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

int n, l, x, y, m = 0, k = 0;
int marks[110000];
int jumps1[220000];
int jumps2[220000];

int main()
{
    scanf("%d %d %d %d", &n, &l, &x, &y);
    for (int i = 0; i < n; i++) {
        scanf("%d", &marks[i]);
        if(marks[i] - x >= 0) {
            jumps1[m] = marks[i] - x;
            m++;
        }
        if(marks[i] + x <= l) {
            jumps1[m] = marks[i] + x;
            m++;
        }
        if(marks[i] - y >= 0) {
            jumps2[k] = marks[i] - y;
            k++;
        }
        if(marks[i] + y <= l) {
            jumps2[k] = marks[i] + y;
            k++;
        }
    }

    bool x_found = false;
    bool y_found = false;

    std::sort(jumps1, jumps1 + m);
    std::sort(jumps2, jumps2 + k);

    int j = 0;
    for (int i = 0; i < m; i++) {
        while (marks[j] < jumps1[i] && j < n-1) {
            j++;
        }
        if (marks[j] == jumps1[i]) {
            x_found = true;
        }
    }

    j = 0;
    for (int i = 0; i < k; i++) {
        while (marks[j] < jumps2[i] && j < n-1) {
            j++;
        }
        if (marks[j] == jumps2[i]) {
            y_found = true;
        }
    }

    if(x_found && y_found)
        printf("0");
    else if(x_found) {
        printf("1\n");
        printf("%d", y);
    }
    else if(y_found) {
        printf("1\n");
        printf("%d", x);
    }
    else {
        int j = 0;
        for (int i = 0; i < k; i++) {
            while (jumps1[j] < jumps2[i] && j < m-1) {
                j++;
            }
            if (jumps1[j] == jumps2[i]) {
                printf("1\n");
                printf("%d", jumps2[i]);
                exit(0);
            }
        }

        printf("2\n");
        printf("%d %d", x, y);
    }
    return 0;
}