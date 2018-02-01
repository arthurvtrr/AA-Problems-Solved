#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int rec1[4], rec2[4];

        for (int i = 0; i < 4; i++)
            scanf("%d", &rec1[i]);
        for (int i = 0; i < 4; i++)
            scanf("%d", &rec2[i]);

        bool overlap = true;
        if (rec1[0] >= rec2[2] || rec1[1] >= rec2[3] || rec1[2] <= rec2[0] || rec1[3] <= rec2[1])
            overlap = false;

        if (!overlap) printf("No Overlap\n");
        else printf("%d %d %d %d\n", max(rec1[0], rec2[0]), max(rec1[1], rec2[1]), min(rec1[2], rec2[2]), min(rec1[3], rec2[3]));

        if (t > 0) printf("\n");
    }
    return 0;
}
