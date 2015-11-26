#include <stdio.h>
#include <string.h>

using namespace std;

int main() {
    int n;
    char room[110][110];
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%s", room[i]);

    int maximum = 0;
    for (int i = 0; i < n; i++) {
        int total = 0;
        for (int j = 0; j < n; j++)
            if (strcmp(room[j], room[i]) == 0) total++;
        if (total > maximum) maximum = total;
    }

    printf("%d\n", maximum);

    return 0;
}
