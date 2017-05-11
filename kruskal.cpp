#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>


#define MAXN 200000 + 10
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
            //cout<< "V"<<a[i].x <<"->" << "V"<<a[i].y<< "=" << a[i].w <<endl;
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
    int n, m,degree, ans; // n 为 点数 m 为 边数
    
    
    string filename;
    string prefix = "mst_";
    string arr[11] = {"100_200_","100_1000_","100_4500_","500_1000_","500_10000_","500_50000_","1000_5000_","1000_20000_","1000_200000_","5000_20000_","5000_100000_"};
    
    ofstream ofs("result/kruskal.csv",ofstream::out); // output result to the test.csv csv file
    ofs << "filename , node, edge, degree, min_weight, time_in_sec " << endl;
    for ( int index = 0; index < 11; ++index){
        int upper = 100;
        if (index == 8)
            upper = 51;
        else if (index > 8)
            upper = 10;
        for (int suffix = 0; suffix < upper; ++suffix){
            filename = prefix + arr[index] + to_string(suffix);
            ifstream ifs(filename + ".txt",ifstream::in);
            char buffer[50];
            int k = 0;
            ifs.getline(buffer, 50);
            istringstream iss((string(buffer)));
            string sn, sm, sk;
            iss >> sn >> sm >> sk;
            n = stoi(sn);
            m = stoi(sm);
            degree = stoi(sk);
            cout << filename << endl;
            Init(n);
            while( ifs.getline(buffer, 50) ){
                stringstream iss((string(buffer)));
                string sx, sy, sw;
                iss >> sx >> sy >> sw; // get substrings seperated by blank
                a[k].x = stoi(sx);
                a[k].y = stoi(sy);
                a[k].w = stoi(sw);
                if(++k == m){
                    clock_t start, end;
                    start = clock();
                    //cout << "flag" << endl;
                    //求解最小生成树
                    ans = Kruskal(n, m);
                    //输出最小权值和
                    cout << "最小权值和=" << ans << endl;
                    // system("pause");
                    end = clock();
                    float execution_time = (float(end) - float(start)) / CLOCKS_PER_SEC;
                    cout << "total time :" <<  execution_time << " secs" << endl;
                    ofs << filename << "," << n << "," << m << "," << degree << "," << ans << "," << execution_time << endl;
                }
                
            }
            
        }
    }
    
    return 0;
}

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>


#define MAXN 200000 + 10
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
            //cout<< "V"<<a[i].x <<"->" << "V"<<a[i].y<< "=" << a[i].w <<endl;
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
    int n, m,degree, ans; // n 为 点数 m 为 边数
    
    
    string filename;
    string prefix = "mst_";
    string arr[11] = {"100_200_","100_1000_","100_4500_","500_1000_","500_10000_","500_50000_","1000_5000_","1000_20000_","1000_200000_","5000_20000_","5000_100000_"};
    
    ofstream ofs("result/kruskal.csv",ofstream::out); // output result to the test.csv csv file
    ofs << "filename , node, edge, degree, min_weight, time_in_sec " << endl;
    for ( int index = 0; index < 11; ++index){
        int upper = 100;
        if (index == 8)
            upper = 51;
        else if (index > 8)
            upper = 10;
        for (int suffix = 0; suffix < upper; ++suffix){
            filename = prefix + arr[index] + to_string(suffix);
            ifstream ifs(filename + ".txt",ifstream::in);
            char buffer[50];
            int k = 0;
            ifs.getline(buffer, 50);
            istringstream iss((string(buffer)));
            string sn, sm, sk;
            iss >> sn >> sm >> sk;
            n = stoi(sn);
            m = stoi(sm);
            degree = stoi(sk);
            cout << filename << endl;
            Init(n);
            while( ifs.getline(buffer, 50) ){
                stringstream iss((string(buffer)));
                string sx, sy, sw;
                iss >> sx >> sy >> sw; // get substrings seperated by blank
                a[k].x = stoi(sx);
                a[k].y = stoi(sy);
                a[k].w = stoi(sw);
                if(++k == m){
                    clock_t start, end;
                    start = clock();
                    //cout << "flag" << endl;
                    //求解最小生成树
                    ans = Kruskal(n, m);
                    //输出最小权值和
                    cout << "最小权值和=" << ans << endl;
                    // system("pause");
                    end = clock();
                    float execution_time = (float(end) - float(start)) / CLOCKS_PER_SEC;
                    cout << "total time :" <<  execution_time << " secs" << endl;
                    ofs << filename << "," << n << "," << m << "," << degree << "," << ans << "," << execution_time << endl;
                }
                
            }
            
        }
    }
    
    return 0;
}

