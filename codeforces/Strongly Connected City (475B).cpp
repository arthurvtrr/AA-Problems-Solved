#include <stdio.h>

using namespace std;

int n, m;
char hor[22], ver[22];

int main()
{
    scanf("%d %d", &n, &m);
    scanf("%s", hor);
    scanf("%s", ver);

    if ((hor[0] == '<' && hor[n-1] == '>' && ver[0] == 'v' && ver[m-1] == '^') ||
        (hor[0] == '>' && hor[n-1] == '<' && ver[0] == '^' && ver[m-1] == 'v'))
        printf("YES");
    else
        printf("NO");
    return 0;
}