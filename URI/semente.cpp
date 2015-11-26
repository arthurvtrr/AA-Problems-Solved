#include <stdio.h>

using namespace std;

int main() {
    int f, r;
    scanf("%d %d", &f, &r);
    int dist_max = 0, ini_max, fim_max;
    int pos_ant = 0, pos_atual;
    for (int i = 0; i < r; i++) {
        scanf("%d", &pos_atual);
        if (dist_max < pos_atual - pos_ant - 1) {
            dist_max = pos_atual - pos_ant - 1;
            ini_max = pos_ant;
            fim_max = pos_atual;
        }
        pos_ant = pos_atual;
    }
    if (dist_max < f - pos_ant) {
        dist_max = f - pos_ant;
        ini_max = pos_ant;
        fim_max = f + 1;
    }

    int resposta;
    if (ini_max == 0 || fim_max == f + 1) resposta = dist_max;
    else if (dist_max % 2 != 0) resposta = dist_max / 2 + 1;
    else resposta = dist_max / 2;

    printf("%d\n", resposta);
    return 0;
}
