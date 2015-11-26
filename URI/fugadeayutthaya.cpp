#include <bits/stdc++.h>
#define pii pair<int,int>
using namespace std;

char grafo[1001][1001];
bool visited[1001][1001];
int dist[1001][1001];
int fire,person;
int t,n,m,start_x,start_y;
vector <pii> fire_pos;

int Dijkstra(int type){

   queue <pii> pq;

   if (type == 1) {
        pq.push(pii(start_x, start_y));
        dist[start_x][start_y] = 0;
   }
   else {
        for (pii f : fire_pos) {
            pq.push(pii(f.first,f.second));
            dist[f.first][f.second] = 0;
        }
   }

   while(!pq.empty()){

      int esq = pq.front().first;
      int dir = pq.front().second;

      visited[esq][dir] = true;

      if(grafo[esq][dir] == 'E'){return dist[esq][dir];}
      pq.pop();


      if(esq + 1 < n && grafo[esq + 1][dir] != '#' && !visited[esq + 1][dir]){

      	if(1 + dist[esq][dir] < dist[esq + 1][dir]){
        	dist[esq + 1][dir] = dist[esq][dir] + 1;
            pq.push(pii(esq + 1,dir));
        }

      }

      if(esq - 1 >= 0 && grafo[esq - 1][dir] != '#' && !visited[esq - 1][dir]){

      	if(1 + dist[esq][dir] < dist[esq - 1][dir]){
        	dist[esq - 1][dir] = dist[esq][dir] + 1;
            pq.push(pii(esq - 1,dir));
        }

      }

      if(dir + 1 < m && grafo[esq][dir + 1] != '#' && !visited[esq][dir + 1]){

      	if(1 + dist[esq][dir] < dist[esq][dir + 1]){
        	dist[esq][dir + 1] = dist[esq][dir] + 1;
            pq.push(pii(esq,dir + 1));
        }

      }

      if(dir - 1 >= 0 && grafo[esq][dir - 1] != '#' && !visited[esq][dir - 1]){

      	if(1 + dist[esq][dir] < dist[esq][dir - 1]){
        	dist[esq][dir - 1] = dist[esq][dir] + 1;
            pq.push(pii(esq,dir - 1));
        }

      }


   }

   return 1 << 26;

}

int main(){

	scanf("%d",&t);

	while(t){

		scanf("%d %d",&n,&m);

        fire_pos.clear();

		for(int i = 0 ; i < n ; i++){
			scanf("%s",grafo[i]);
			for(int j = 0 ; j < m ; j++){
				if(grafo[i][j] == 'S'){
					start_x = i;
					start_y = j;
				}
				if(grafo[i][j] == 'F'){
					fire_pos.push_back(pii(i,j));
				}

			}
		}

		fire = person = 1 << 26;

   		for(int i = 0 ; i <= 1000 ; i++){
   			for(int j = 0 ; j <= 1000 ; j++){
   				dist[i][j] = 1 << 26;
   			}
   		}

   		memset(visited,0,sizeof(visited));

		fire = Dijkstra(2);

		for(int i = 0 ; i <= 1000 ; i++){
   			for(int j = 0 ; j <= 1000 ; j++){
   				dist[i][j] = 1 << 26;
   			}
   		}

   		memset(visited,0,sizeof(visited));

		person = Dijkstra(1);

		if(fire <= person)
			printf("N\n");
		else
			printf("Y\n");

		t--;
	}



	return 0;
}
