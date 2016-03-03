#include <bits/stdc++.h>
#define pii pair<int,int>
using namespace std;

char grafo[1001][1001];
bool visited[1001][1001];
int dist[1001][1001];
int fire,person;
int t,n,m,start_x,start_y,fire_x,fire_y;

int Dijkstra(int x , int y){

   queue <pii> pq;

   pq.push(pii(x,y));

   dist[x][y] = 0;

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

		vector <pii> fire_pos;

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

		for(int i = 0 ; i < fire_pos.size() ; i++){
			fire = min(fire,Dijkstra(fire_pos[i].first , fire_pos[i].second));
		}

		for(int i = 0 ; i <= 1000 ; i++){
   			for(int j = 0 ; j <= 1000 ; j++){
   				dist[i][j] = 1 << 26;
   			}
   		}

   		memset(visited,0,sizeof(visited));

		person = Dijkstra(start_x,start_y);


		cout << fire << " " << person << endl;

		if(fire <= person)
			printf("N\n");
		else
			printf("Y\n");

		t--;
	}



	return 0;
}
