#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

#define MAX 100100

struct subset {
    int parent;
    int rank_;
} subsets[MAX];

int find_(int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find_(subsets[i].parent);
    return subsets[i].parent;
}

void union_(int x, int y) {
    int xroot = find_(x);
    int yroot = find_(y);

    if (subsets[xroot].rank_ < subsets[yroot].rank_)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank_ > subsets[yroot].rank_)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank_++;
    }
}

int n, m, x, y, z;

struct edge {
    int from;
    int to;
    int weight;
};

//Comparador para definir como as arestas serão ordenadas
//Para Maximum Spanning Tree, apenas inverter o sinal
bool comp(edge a, edge b) {
    return a.weight < b.weight;
}

vector < edge > edges;

int main() {
    //"n" é o número de vértices, "m" é o de arestas
    scanf("%d %d", &n, &m);

    //Importante setar o parent e rank inicial de cada vertice
    for (int i = 0; i < MAX; i++) {
        subsets[i].parent = i;
        subsets[i].rank_ = 1;
    }

    for (int i = 0; i < m; i++) {
        //"x" e "y" são os ids dos vértices conectados pela aresta, "z" é o peso
        scanf("%d %d %d", &x, &y, &z);
        edges.push_back((edge) {x, y, z});
    }

    sort(edges.begin(), edges.end(), comp);

    int used_edges = 0, ind = 0, cost = 0;

    while (used_edges < n-1) {
        //Encontra o root do componente de cada vertice
        int xroot = find_(edges[ind].from);
        int yroot = find_(edges[ind].to);

        //Se os dois vertices da aresta ainda não estao no mesmo componente, conecte os dois
        if (xroot != yroot) {
            union_(xroot, yroot);
            used_edges++;
            cost += edges[ind].weight;
        }

        ind++;
    }

    //Custo mínimo para conectar todos os vertices
    printf("%d\n", cost);

    return 0;
}
