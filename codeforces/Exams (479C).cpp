#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

int n;
struct days {
    int a;
    int b;
} exams[5500];

bool compare(days x, days y) {
    if (x.a == y.a)
        return x.b < y.b;
    return x.a < y.a;
}

int findDay() {
    int day = 1;
    int tomake = 0;
    while (tomake < n) {
        if (day == exams[tomake].b)
            tomake++;
        else if (day == exams[tomake].a)
            tomake++;
        else
            day++;
    }
    printf("%d", day);
}

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &exams[i].a, &exams[i].b);
    }

    sort(exams, exams+n, compare);

    findDay();

    return 0;
}