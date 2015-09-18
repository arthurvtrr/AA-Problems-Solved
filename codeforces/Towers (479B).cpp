#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

int n, k, s, m;
int instabilities[1100];

struct heights {
    int index;
    int height;
} towers[110];


bool compare(heights h, heights j) {
    return h.height < j.height;
}

struct operations {
    int from;
    int to;
} sequences[1100];


void findOperations() {
    for(int i = 0; i < k; i++) {
        towers[0].height += 1;
        towers[n - 1].height -= 1;
        sequences[i].from = towers[n - 1].index;
        sequences[i].to = towers[0].index;
        sort(towers, towers + n, compare);
        instabilities[i] = towers[n - 1].height - towers[0].height;
    }

    int minimun = instabilities[0];
    int index = 1;

    for(int j = 0; j < k; j++) {
        if (instabilities[j] < minimun) {
            minimun = instabilities[j];
            index = j + 1;
        }
    }

    printf("%d %d\n", minimun, index);

    for(int i = 0; i < index; i++) {
        printf("%d %d\n", sequences[i].from + 1, sequences[i].to + 1);
    }

}

int main()
{
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &towers[i].height);
        towers[i].index = i;
    }

    sort(towers, towers + n, compare);

    if (n == 1) {
        printf("0 0");
        exit(0);
    }

    int equals = 0;
    for(int i = 0; i < n; i++) {
        if (towers[i].height == towers[0].height)
            equals++;
    }

    if (equals == n) {
        printf("0 0");
    }
    else {
        findOperations();
    }

    return 0;
}