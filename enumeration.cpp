//
//  main.cpp
//  enumeration
//
//  A spanning tree has exact n vertices and n-1 edges
//  It is connected and doesn't have cycles
//
//  Step1: Get all possible combinations of n-1 edges
//  Step2: Filter out non-spanning tree (it is connected and every node has occured) and update the minimum weight
//
//  note: leverage a Union-Find alike method to determine whether a graph is connected or not
//
//  Created by alicehzheng on 06/05/2017.
//  Copyright © 2017 alicehzheng. All rights reserved.
//

#include<iostream>
#include<fstream>
#include<map>

using  namespace std;

#define MAXEDGES 100 //define the potential maximun number of edges in a graph
#define MAXVERTICES 100 //define the potential maximun number of vertices in a graph
#define MAXCOST 0x7fffffff

typedef struct{
    int x,y,w;
}Edge; //structure of the edge of the graph
Edge edge[MAXEDGES];

map<int,int> vertices;//map to track a vertex's connection with another vertex

int minWeight = MAXCOST;
int stEdge[MAXVERTICES];
int mstEdge[MAXVERTICES];
int n, m;

int getParent(int v){
    if(vertices[v] == v)
        return v;
    int parent = getParent(vertices[v]);
    vertices[v] = parent;
    return parent;
}// trace the ancestor of a vertex and shorten the path

void enumeration(int ll, int rr, int k){
    if (k >= n - 1) {
        int tmpWeight = 0;
        for (int i = 0; i < n - 1; ++i) {
            int edgeIndex = stEdge[i];
            int nx = edge[edgeIndex].x;
            int ny = edge[edgeIndex].y;
            int weight = edge[edgeIndex].w;
            int px = getParent(nx);
            int py = getParent(ny);
            if(px < py){ // make the smaller vertex the ancestor of the bigger one
                vertices[py] = px;
                vertices[ny] = px;
            }
            else{
                vertices[px] = py;
                vertices[nx] = py;
            }
            tmpWeight += weight;
        }
        bool isSpanning = true;
        
        // check whether the graph is connected
        auto it = vertices.begin();
        int root = getParent(it->first);
        ++it;
        for (; it != vertices.end(); ++it) {
            if (getParent(it->first) != root) {// if the graph is not connected, it must not be a spanning tree
                isSpanning = false;
                break;
            }
        }
        if (isSpanning && tmpWeight < minWeight) {
            minWeight = tmpWeight;
            for (int j = 0; j < n - 1; ++j) {
                mstEdge[j] = stEdge[j];
            }
        } // update MST and min weight
        for (auto it = vertices.begin(); it != vertices.end(); ++it) {
            it -> second = it -> first;
        }// reset vertices map
        return;
    }// when it comes to the end of iteration, check whether the edges in the stEdge meets the requirement
    
    if ( k >= 0 && k < n - 1 ) {
        for (int t = ll; t <= rr; ++t) {
            stEdge[k] = t;
            enumeration(t+1, rr, k+1);
        }
    }
    return;
} // pick an index from [ll,rr] and put it in the stEdge[k]




int main(int argc, const char * argv[]) {
    
    cin >> n >> m; // input the vertex number (n) and edge number (m)
    
    //set up edges and vertices
    int vx, vy, weight;
    for(int k = 0; k < m; ++k){
        cin >> vx >> vy >> weight; // input info of each edge
        edge[k].x = vx;
        edge[k].y = vy;
        edge[k].w = weight;
        vertices[vx] = vx;//set up initial parent of vertices
        vertices[vy] = vy;
        mstEdge[k] = 0; //initialize MST edge
    }
    enumeration(0,m-1,0);
    
    cout << "MST with minimal weight of " << minWeight << "is as follows:" << endl;
    for(int k = 0; k < n - 1; ++k){
        cout << "Edge(" << edge[mstEdge[k]].x << "," << edge[mstEdge[k]].y <<"," <<edge[mstEdge[k]].w << ")" << endl;
    }
    
    /*
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        cout << it->first << "=>" << it->second << endl;
    }
     */
    
    
    return 0;
}
