//
//  main.cpp
//  prim
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
                //cout << "*_*"<<endl;
                min = lowcost[j];
                minid = j;
            }
        }
        // cout << minid
        //cout << "V" << mst[minid] << "-> V" << minid << "=" << min << endl;
        cnt += 1;
        //cout << "cnt is "<< cnt << endl;
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
            //cout  << "i is "<< i << endl;
            
        }
    }
    return sum;
}

int main()
{
    
    int i, j, m, n,degree;
    int cost;
    
    //初始化图G
    
    string filename;
    string prefix = "mst_";
    string arr[11] = {"100_200_","100_1000_","100_4500_","500_1000_","500_10000_","500_50000_","1000_5000_","1000_20000_","1000_200000_","5000_20000_","5000_100000_"};
    
    ofstream ofs("result/prim.csv",ofstream::out); // output result to the test.csv csv file
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
            for (i = 0; i <n; i++)
            {
                for (j = 0; j < n; j++)
                {
                    graph[i][j] = MAXCOST;
                }
            }
            while( ifs.getline(buffer, 50) ){
                stringstream iss((string(buffer)));
                string sx, sy, sw;
                iss >> sx >> sy >> sw; // get substrings seperated by blank
                i = stoi(sx);
                j = stoi(sy);
                cost = stoi(sw);
                graph[i][j] = cost;
                graph[j][i] = cost;
                if(++k == m){
                    clock_t start, end;
                    start = clock();
                    //cout << "flag" << endl;
                    //求解最小生成树
                    cost = prim(graph, n);
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

