#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "timestamp.h"

#ifndef UGRAPH_H
#define UGRAPH_H

struct edge{
    int neighbor;
    int w;
    edge(){
        neighbor = 0;
        w = 0;
    };
    edge (int i, int j){
        neighbor = i;
        w = j;
    }
};

class UGraph{
    public:
            UGraph(int N);
            void printGraph();
            bool isNeighbor(int u, int v);
            void bfs(int s);
            void dfs();
            void dfsVisit(int u, int &atime);
            void printPath(int v);
            void printPathRec(int v);
            void printLevels(int s);
            bool isCycle();
            bool isCycleVisit(int u, int &t);
            void addEdge(int u, int v);
            void removeEdge(int u, int v);
            bool distinctPaths(int u, int v);
            void bfsWeighted(int s);
            void backtrackParents(int u, int v, vector<int>& path);
            void printCC();
            void bfsCC(int s, vector<int>& ids);
            bool twoColoring();
            void printBridges();
            void findBridges(int u, int &t, vector<int> &tLow);
    private:
            vector<vector<edge>> Adj; //adjacency lists of the graph
            vector<int> distance; //BFS
            vector<int> parents; //BFS & DFS
            vector<char> colors; //DFS
            vector<TimeStamp> stamps; //DFS
            int size; //total nodes in graph
};

#endif
