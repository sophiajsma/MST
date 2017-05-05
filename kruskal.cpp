
#include <cstdio>
#include <cstdlib>
#include <iostream>
#define MAXN 10000 + 10
using namespace std;

int par[MAXN], Rank[MAXN];
typedef struct{
    int x,y,w;
}Node;
Node a[MAXN];

int cmp(const void*a, const void *b){
    return ((Node*)a)->w - ((Node*)b)->w;
}
void Init(int n){
    for(int i = 0; i < n; i++){
        Rank[i] = 0;
        par[i] = i;
    }
}

int find(int x){
    int root = x;
    while(root != par[root]) root = par[root];
    while(x != root){
        int t = par[x];
        par[x] = root;
        x = t;
    }
    return root;
}

void unite(int x, int y){
    x = find(x);
    y = find(y);
    if(Rank[x] < Rank[y]){
        par[x] = y;
    }
    else{
        par[y] = x;
        if(Rank[x] == Rank[y]) Rank[x]++;
    }
}
//n为边的数量，m为村庄的数量
int Kruskal(int n, int m){
    int nEdge = 0, res = 0;
    //将边按照权值从小到大排序
    qsort(a, m, sizeof(a[0]), cmp);
    for(int i = 0; i < m && nEdge != n - 1; i++){
        //判断当前这条边的两个端点是否属于同一棵树
        if(find(a[i].x) != find(a[i].y)){
            cout<< "V"<<a[i].x <<"->" << "V"<<a[i].y<< "=" << a[i].w <<endl;
            unite(a[i].x, a[i].y);
            res += a[i].w;
            nEdge++;
        }
    }
    //如果加入边的数量小于m - 1,则表明该无向图不连通,等价于不存在最小生成树
    if(nEdge < n-1) res = -1;
    return res;
}
int main(){
    int nPoint, mEdge, ans; // n 为 点数 m 为 边数
    // while(scanf("%d%d", &n, &m), n){
        scanf("%d%d", &nPoint, &mEdge);

        // cin >> nPoint >> mEdge;
        Init(nPoint);
        for(int i = 0; i < mEdge; i++){
            scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].w);
            //将村庄编号变为1~m（这个仅仅只是个人习惯，并非必要的）
            // a[i].x;
            // a[i].y;
        }
        ans = Kruskal(nPoint, mEdge);
        if(ans == -1) printf("?\n");
        else printf("%d\n", ans);
    // }
    return 0;
}

// 6 10  
// 1 2 6  
// 1 3 1  
// 1 4 5  
// 2 3 5  
// 2 5 3  
// 3 4 5  
// 3 5 6  
// 3 6 4  
// 4 6 2  
// 5 6 6
