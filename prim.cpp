#include<iostream>  
#include<fstream>  
using  namespace std;  
  
#define MAX 200000 + 10  
#define MAXCOST 0x7fffffff  

int graph[MAX][MAX];  
  
int prim(int graph[][MAX], int n)  
{  
    //n is the num of point
    int cnt = 0;
    bool isU[MAX];
    isU[0] = true;
    for (int i = 1; i < n;++i){
        isU[i] = false;
    }

    int lowcost[MAX];  
    int mst[MAX];  
    int i, j, min, minid, sum = 0;  

    for (int i = 1; i < n; i++)  
    {  
        lowcost[i] = graph[0][i];  
        mst[i] = 0;  
    }  
    mst[0] = -1; 
    for (int i = 1; i<n; ++i){
        min = MAXCOST;
        minid = 1;
        for(j = 1; j <n ;++j){
            if(isU[j] == true)
                continue;
            // cout << lowcost[j]<<"&_&"<<endl;
            if(lowcost[j] < min){
                cout << "*_*"<<endl;
                min = lowcost[j];
                minid = j;
            }
        }
        // cout << minid
        cout << "V" << mst[minid] << "-> V" << minid << "=" << min << endl;
        cnt += 1;
        cout << "cnt is "<< cnt << endl;
        sum += min;
        isU[minid] = true;
        for(j = 1;j <n ; ++j){
            if(graph[minid][j] < lowcost[j]){
                lowcost[j] = graph[minid][j];
                mst[j] = minid;
            }
        }
    }

    for(int i=0;i<n;++i){
        if(isU[i] == false){
            cout  << "i is "<< i << endl;

        }
    }
    return sum;  
}  
  
int main()  
{  
    // int **graph=new int*[MAX];       //分配一个指针数组，将其首地址保存在b中                                                    
    //        for(int i=0;i<MAX;i++)             //为指针数组的每个元素分配一个数组
    //            graph[i]=new int[MAX];  
    int i, j, k, m, n,aa;  
    int x, y, cost;  
    // ifstream in("input.txt");  
    // in >> m >> n;//n=顶点的个数，m=边的个数  
    //初始化图G 
     ifstream in("mst_1000_200000_0.txt");  
        // in >> 
    in >> n >> m >> aa; 
    // cout << n << m << aa;
    // cin >> n >> m;
    for (i = 0; i <n; i++)  
    {  
        for (j = 0; j < n; j++)  
        {  
            graph[i][j] = MAXCOST;  
        }  
    }  
    //构建图G  
    for (k = 1; k <= m; k++)  
    {  
        in >> i >> j >> cost;
        // cin >> i >> j >> cost; 
        // cout <<"cost is "<<cost<<endl; 
        graph[i][j] = cost;  
        graph[j][i] = cost; 
        // cout << graph[i][j]<<endl; 
    }
    // for(i = 1;i<=100;++i){
    //     for (k=1;k<=100;++k){
    //         if(graph[i][k] != MAXCOST)
    //             cout <<graph[i][k]<<' ';
    //     }
    //     // cout<<endl;
    // }  
    //求解最小生成树  
    cost = prim(graph, n);  
    //输出最小权值和  
    cout << "最小权值和=" << cost << endl;  
    // system("pause");  
    return 0;  
}  
