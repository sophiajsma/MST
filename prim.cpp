#include<iostream>  
#include<fstream>  
using  namespace std;  
  
#define MAX 100  
#define MAXCOST 0x7fffffff  
  
int graph[MAX][MAX];  
  
int prim(int graph[][MAX], int n)  
{  
    //n is the num of point
    bool isU[MAX];
    isU[1] = true;
    for (int i = 2; i <= n;++i){
        isU[i] = false;
    }

    int lowcost[MAX];  
    int mst[MAX];  
    int i, j, min, minid, sum = 0;  

    for (int i = 2; i <= n; i++)  
    {  
        lowcost[i] = graph[1][i];  
        mst[i] = 1;  
    }  
    mst[1] = 0;  
    for (int i = 2; i<=n; ++i){
        min = MAXCOST;
        minid = 0;
        for(j = 2; j <=n ;++j){
            if(isU[j] == true)
                continue;
            if(lowcost[j] < min){
                min = lowcost[j];
                minid = j;
            }
        }
        cout << "V" << mst[minid] << "->" << minid << "=" << min << endl;
        sum += min;
        isU[minid] = true;
        for( int j = 2;j <=n ; ++j){
            if(graph[minid][j] < lowcost[j]){
                lowcost[j] = graph[minid][j];
                mst[j] = minid;
            }
        }
    }

    
    return sum;  
}  
  
int main()  
{  
    int i, j, k, m, n;  
    int x, y, cost;  
    // ifstream in("input.txt");  
    // in >> m >> n;//n=顶点的个数，m=边的个数  
    //初始化图G  
    cin >> n >> m;
    for (i = 1; i <= n; i++)  
    {  
        for (j = 1; j <= n; j++)  
        {  
            graph[i][j] = MAXCOST;  
        }  
    }  
    //构建图G  
    for (k = 1; k <= m; k++)  
    {  
        // in >> i >> j >> cost;
        cin >> i >> j >> cost;  
        graph[i][j] = cost;  
        graph[j][i] = cost;  
    }  
    //求解最小生成树  
    cost = prim(graph, n);  
    //输出最小权值和  
    cout << "最小权值和=" << cost << endl;  
    // system("pause");  
    return 0;  
}  