#include <bits/stdc++.h>

using namespace std;

#define MAXP 100100
#define INF 4000000000000000000LL
#define ll long long

typedef pair<ll,ll> point;
typedef pair<point,point> pp;

bool compareX(point a,point b){
if(a.first<b.first) return true;
return false;
}

bool compareY(point a,point b){
if(a.second<b.second) return true;
return false;
}

ll dist(point a,point b){
return (b.second-a.second)*(b.second-a.second) + (b.first-a.first)*(b.first-a.first);
}

pp BruteForce(point P[],int n){
ll dist_min=INF;
pp choosed;

for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
        if(dist(P[i],P[j])<dist_min){
            dist_min=dist(P[i],P[j]);
            choosed=make_pair(P[i],P[j]);
        }
    }
}

return choosed;
}

pp stripClosest(point strip[],int s,pp upper){
ll dist_min=dist(upper.first,upper.second);
pp choosed=upper;

for(int i=0;i<s;i++){
    for(int j=i+1;j<s && (strip[j].second-strip[i].second)<dist_min;j++){
        if(dist(strip[i],strip[j])<dist_min){
            dist_min=dist(strip[i],strip[j]);
            choosed=make_pair(strip[i],strip[j]);
        }
    }
}

return choosed;
}

pp closestUtil(point Px[],point Py[],int n){
if(n<=3) return BruteForce(Px,n);

int mid=n/2;
point midPoint=Px[mid];

point Pyl[mid+1],Pyr[n-mid-1];
int li=0,ri=0;

for(int i=0;i<n;i++){
    if(Py[i].first <= midPoint.first) Pyl[li++]=Py[i];
    else Pyr[ri++]=Py[i];
}

pp pl=closestUtil(Px,Pyl,mid);
pp pr=closestUtil(Px+mid,Pyr,n-mid);

pp pmin;
ll dist_min;
if(dist(pl.first,pl.second)<dist(pr.first,pr.second)){
  pmin=pl;
  dist_min=dist(pl.first,pl.second);
}
else{
  pmin=pr;
  dist_min=dist(pr.first,pr.second);
}

point* strip=new point[n];
int j=0;
for(int i=0;i<n;i++){
    if(abs(Py[i].first-midPoint.first)<dist_min) strip[j++]=Py[i];
}

return stripClosest(strip,j,pmin);
}

pp closest(point P[],int n){
point* Px=new point[n];
point* Py=new point[n];

for(int i=0;i<n;i++){
    Px[i]=P[i];
    Py[i]=P[i];
}

sort(Px,Px+n,compareX);
sort(Py,Py+n,compareY);

return closestUtil(Px,Py,n);
}

int main(){
    int n;
    ll x,y;
    point P[MAXP];

    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%lld %lld",&x,&y);
        P[i]=make_pair(x,y);
    }

    pp choosed=closest(P,n);
    printf("%lld %lld\n", choosed.first.first, choosed.first.second);
    printf("%lld %lld\n", choosed.second.first, choosed.second.second);

    return 0;
}
