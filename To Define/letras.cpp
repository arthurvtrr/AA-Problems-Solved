#include <stdio.h>
#include <string.h>

using namespace std;

int main() {
    char letra;
    scanf("%c", &letra);
    char texto[1100];
    scanf(" %[^\n]", texto);
    int num_palavras = 0, num_aparicoes = 0, tem = 0;
    for (int i = 0; i < strlen(texto); i++) {
        if (texto[i] == letra) {
            tem++;
        }
        else if (texto[i] == ' ') {
            num_palavras++;
            if (tem > 0) {
                num_aparicoes++;
                tem = 0;
            }
        }
    }
    num_palavras++;
    if (tem > 0) num_aparicoes++;

    double resposta = 1.0 * num_aparicoes / num_palavras * 100.0;
    printf("%.1lf\n", resposta);
    return 0;
}
