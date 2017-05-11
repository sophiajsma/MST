//
//  main.cpp
//  circle
//
//  Created by alicehzheng on 10/05/2017.
//  Copyright © 2017 alicehzheng. All rights reserved.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>

using  namespace std;

#define MAX 200000+10
#define MAXCOST 0x7fffffff

typedef struct{
    int x,y,w;
}Node;
Node a[MAX];

int cmp(const void*a, const void *b){//从小到大
    return ((Node*)a)->w - ((Node*)b)->w;
}

int cmp2(const void*a, const void *b){//从大到小
    return ((Node*)b)->w - ((Node*)a)->w;
}

int graph[MAX][MAX];

int Wshall(int array[][MAX],int n){
    // cout << "it is in Wshall"<<endl;
    int i,j,k,m = 0;
    int r[n+1][n+1], B[n+1][n+1];
    for(i = 1; i<=n ; ++i){
        for(j = 1; j <= n; ++j){
            r[i][j] = 0;
            if(array[i][j] != 0)
                B[i][j] = 1;
            else
                B[i][j] = 0;
            // B[i][j] = array[i][j];
            // if(B[i][j] < 0)
            // cout <<array[i][j]<<endl;
            
        }
    }
    // cout << "it is in Wshall 2"<<endl;
    
    for(j = 1; j <= n; ++j){
        for(i = 1; i<=n ; ++i){
            if(B[i][j] >= 1){
                for(k = 1; k <= n; k++){
                    B[i][k] = B[i][k] + B[j][k] > 0 ? 1:0;
                    // if(B[i][j] == 0)
                    // B[i][j] = B[i][k] + B[k][j];
                    // cout << i << ' '<<k<<' '<<B[i][k]<<endl;
                    
                }
            }
        }
    }
    // // cout << "it is in Wshall 3"<<endl;
    
    for(i = 1; i <= n; i++){
        for( j = 1; j <= n; j++){
            r[i][j] = B[i][j];
            if(r[i][j] >= 1 || i==j){
                m = m+1;
            }
        }
    }
    // // cout << "it is in Wshall 4"<<endl;
    // cout << "m = "<< m << "n*n = "<<n*n<<endl;
    if(m == n*n) return 1;
    else return 0;
}

int circle(int graph[][MAX], int n, int m)
{
    int max, p, q, am;
    for(int i =0; i<m; ++i){
        p = a[i].x;
        q = a[i].y;
        // cout << p << " "<<q <<  " "<< a[i].w << endl;
        // am = a[i].w;
        graph[p][q] = 0;
        graph[q][p] = 0;
        if(Wshall(graph,n) == 1){
            //cout << "delete V" << p << "-> V" << q << "=" << a[i].w <<endl;
        }else{
            // cout << "*+*"<<p << " "<<q <<  " "<< a[i].w << endl;
            graph[p][q] = a[i].w;
            graph[q][p] = a[i].w;
        }
    }
    int ans = 0;
    int cnt = 0;
    for(int i = 1; i <= n; ++i){
        for(int j = 0; j < i; ++j){
            if(graph[i][j] != 0){
                cnt +=1;
                // cout << "V" << i << "-> V" << j << "=" << graph[i][j] <<endl;
                ans+= graph[i][j];
            }
        }
    }
    // cout <<"cnt is "<<cnt << endl;
    return ans;
}

int main()
{
    int i, j, m, n, degree;// n 为 点数 m 为 边数
    int cost;
    
    string filename;
    string prefix = "mst_";
    string arr[11] = {"100_200_","100_1000_","100_4500_","500_1000_","500_10000_","500_50000_","1000_5000_","1000_20000_","1000_200000_","5000_20000_","5000_100000_"};
    
    ofstream ofs("result/circle.csv",ofstream::out); // output result to the test.csv csv file
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
            for (i = 1; i <= n; i++)
            {
                for (j = 1; j <= n; j++)
                {
                    graph[i][j] = 0;
                }
            }
            a[0].w = MAXCOST;
            while( ifs.getline(buffer, 50) ){
                stringstream iss((string(buffer)));
                string sx, sy, sw;
                iss >> sx >> sy >> sw; // get substrings seperated by blank
                i = stoi(sx);
                j = stoi(sy);
                cost = stoi(sw);
                a[k].x = i+1;
                a[k].y = j+1;
                a[k].w = cost;
                graph[i+1][j+1] = cost;
                graph[j+1][i+1] = cost;
                if(++k == m){
                    clock_t start, end;
                    start = clock();
                    //cout << "flag" << endl;
                    //求解最小生成树
                    qsort(a, m, sizeof(a[0]), cmp2);
                    cost = circle(graph, n, m);
                    //输出最小权值和
                    cout << "最小权值和=" << cost << endl;
                    // system("pause");
                    end = clock();
                    float execution_time = (float(end) - float(start)) / CLOCKS_PER_SEC;
                    cout << "total time :" <<  execution_time << " secs" << endl;
                    ofs << filename << "," << n << "," << m << "," << degree << "," << cost << "," << execution_time << endl;
                }
                
            }
            
        }
    }
    
    
    
    
    return 0;
}
