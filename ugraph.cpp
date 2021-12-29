//All code until line 160 was provided.

#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <queue>
#include <utility>
using namespace std;

#include "ugraph.h"

UGraph::UGraph(int N){
    size = N;
    Adj.resize(size);
    distance.resize(size);
    parents.resize(size);
    colors.resize(size);
    stamps.resize(size);
}
void UGraph::printGraph(){
    for(int u = 0; u < size; u++){
        for(int j = 0; j < (int)Adj[u].size(); j++){
            int neighbor = Adj[u][j].neighbor;
            cout << neighbor << " ";
        }//for adjacency list of u
        cout << endl;
    }//for all nodes u
}
void UGraph::printPath(int v){
    if(distance[v] != INT_MAX){
        printPathRec(v);
        cout << endl;
    }
}
void UGraph::printPathRec(int v){
    if(distance[v] == 0){
        cout << v << " ";
        return;
    }
    printPathRec(parents[v]);
    cout << v << " ";
}
void UGraph::printLevels(int s){
    for(int i = 0; i < size; i++){
        distance[i] = INT_MAX;
        parents[i] = i;
    }//for
    distance[s] = 0;
    queue<pair<int, int>> aq;
    aq.push(make_pair(s, distance[s]));
    int curLevel = 0;

    while(!aq.empty()){
        pair<int, int> apair = aq.front();
        int u = apair.first;
        int curDist = apair.second;
        if(curLevel != curDist){
            cout << endl;
            curLevel = curDist;
        }
        aq.pop();
        cout << u << " ";
        for(int i = 0; i < (int)Adj[u].size(); i++){
            int v = Adj[u][i].neighbor;
            if(distance[v] == INT_MAX){
                distance[v] = distance[u] + 1;
                parents[v] = u;
                aq.push(make_pair(v, distance[v]));
            }
        }//for
    }//while
    cout << endl;
}

void UGraph::bfs(int s){
    for(int i = 0; i < size; i++){
        distance[i] = INT_MAX;
        parents[i] = i;
    }//for
    distance[s] = 0;
    queue<int> aq;
    aq.push(s);
    while(!aq.empty()){
        int u = aq.front();
        aq.pop();
        cout << u << " ";
        for(int i = 0; i < (int)Adj[u].size(); i++){
            int v = Adj[u][i].neighbor;
            if(distance[v] == INT_MAX){
                distance[v] = distance[u] + 1;
                parents[v] = u;
                aq.push(v);
            }
        }//for
    }//while
    cout << endl;
}//bfs

void UGraph::dfs(){
    for(int i = 0; i < size; i++){
        parents[i] = i;
        colors[i] = 'W';
    }	
    int t = 0;

    for(int i = 0; i < size; i++){
        if(colors[i] == 'W'){
            //color[i] = 'G';
            dfsVisit(i, t);
        }//if
    }//for
    cout << endl;
}//dfs

void UGraph::dfsVisit(int u, int &t){
    colors[u] = 'G';
    stamps[u].d = t;
    t++;
    cout << u << " ";
    for(int i = 0; i < (int)Adj[u].size(); i++){
        int v = Adj[u][i].neighbor;
        if(colors[v] == 'W'){
            parents[v] = u;
            colors[v] = 'G';
            dfsVisit(v, t);
        }
    }//for
    colors[u] = 'B';
    stamps[u].f = t;
    t++;
}//dfsVisit	

void UGraph::addEdge(int u, int v){
    Adj[u].push_back(edge(v, 0));
    Adj[v].push_back(edge(u, v));
}

void UGraph::removeEdge(int u, int v){
    int sizeU = (int)Adj[u].size();
    for(int i = 0; i < sizeU; i++){
        if(Adj[u][i].neighbor == v){
            Adj[u][i].neighbor = Adj[u][sizeU-1].neighbor;
            Adj[u].resize(sizeU-1);
            break;
        }//if
    }//for

    int sizeV = (int)Adj[v].size();
    for(int j = 0; j < sizeV; j++){
        if(Adj[v][j].neighbor == u){
            Adj[v][j].neighbor = Adj[v][sizeV-1].neighbor;
            Adj[v].resize(sizeV - 1);
            break;
        }//if
    }//for
}

//All code above was provided to me
//All code below was written by me to solve the assigned problems

bool UGraph::distinctPaths(int u, int v){
    //this for loop is to account for previous function calls that may have changed the weights.
    for(int i = 0; i < size; i++){
        for(int j = 0; j < (int)Adj[i].size(); j++){
            if(Adj[i][j].w != i)
                Adj[i][j].w = i;
        }
    }
    bfsWeighted(u);
    vector<int> path1;
    backtrackParents(v, u, path1);
    bfsWeighted(u);
    if(distance[v] != INT_MAX){
        vector<int> path2;
        backtrackParents(v, u, path2);
        for(int i = (int)path1.size() - 1; i >= 0; i--)
            cout << path1[i] << " ";
        cout << endl;
        for(int j = (int)path2.size() - 1; j >= 0; j--)
            cout << path2[j] << " ";
        cout << endl;
        return true;
    }
    return false;
}

void UGraph::bfsWeighted(int s){
    for(int i = 0; i < size; i++){
        distance[i] = INT_MAX;
        parents[i] = i;
    }//for
    distance[s] = 0;
    queue<int> aq;
    aq.push(s);
    while(!aq.empty()){
        int u = aq.front();
        aq.pop();
        for(int i = 0; i < (int)Adj[u].size(); i++){
            int v = Adj[u][i].neighbor;
            if(distance[v] == INT_MAX && Adj[u][i].w != -1){
                distance[v] = distance[u] + 1;
                parents[v] = u;
                aq.push(v);
            }
        }//for
    }//while
}

void UGraph::backtrackParents(int v, int u, vector<int>& path){    
    path.push_back(v);
    if(parents[v] == v)
        return;
    int p = parents[v];
    for(int i = 0; i < (int)Adj[p].size(); i++){
        int n = Adj[p][i].neighbor;
        if(n == v){
            Adj[p][i].w = -1;
        }
    }
    return backtrackParents(parents[v], u, path);
}

void UGraph::printCC(){
    for(int j = 0; j < size; j++)
        distance[j] = INT_MAX;
    vector<int> ids(size, -1);
    for(int i = 0; i < size; i++){
        if(distance[i] == INT_MAX && ids[i] == -1){
            bfsCC(i, ids);
            for(int k = 0; k < size; k++){
                if(distance[k] != INT_MAX)
                    cout << k << " ";
            }
            cout << endl;
        }
    }
}

void UGraph::bfsCC(int s, vector<int>& ids){
    for(int i = 0; i < size; i++){
        distance[i] = INT_MAX;
        parents[i] = i;
    }//for
    distance[s] = 0;
    queue<int> aq;
    aq.push(s);
    while(!aq.empty()){
        int u = aq.front();
        aq.pop();
        ids[u] = s;
        for(int i = 0; i < (int)Adj[u].size(); i++){
            int v = Adj[u][i].neighbor;
            if(distance[v] == INT_MAX){
                distance[v] = distance[u] + 1;
                parents[v] = u;
                aq.push(v);
            }
        }//for
    }//while

}

bool UGraph::twoColoring(){
    vector<char> twoColors(size, 'P');
    twoColors[0] = 'B';
    int s = 0;
    for(int i = 0; i < size; i++){
        parents[i] = i;
    }//for
    
    queue<int> aq;
    aq.push(s);
    
    while(!aq.empty()){
        int u = aq.front();
        aq.pop();
        for(int i = 0; i < (int)Adj[u].size(); i++){
            int v = Adj[u][i].neighbor;
            if(twoColors[v] == 'P'){
                parents[v] = u;
                aq.push(v);
                if(twoColors[u] == 'B')
                    twoColors[v] = 'R';
                else
                    twoColors[v] = 'B';
            }
        }//for
    }//while

    for(int i = 0; i < size; i++){
        for(int j = 0; j < (int)Adj[i].size(); j++){
            int n = Adj[i][j].neighbor;
            if(twoColors[i] == twoColors[n])
                return false;
        }
    }
    return true;
}

void UGraph::printBridges(){
    for(int i = 0; i < size; i++){
        parents[i] = i;
        colors[i] = 'W';
        stamps[i].f = 0;
    }	
    int t = 0;
    vector<int> tLow(size, -1);

    for(int i = 0; i < size; i++){
        if(colors[i] == 'W'){
            findBridges(i, t, tLow);
        }//if
    }//for   
}

void UGraph::findBridges(int u, int &t, vector<int> &tLow){
    colors[u] = 'G';
    t++;
    tLow[u] = t;
    stamps[u].f = t;
    for(int i = 0; i < (int)Adj[u].size(); i++){
        int v = Adj[u][i].neighbor;
        if(colors[v] == 'W'){
            parents[v] = u;
            colors[v] = 'G';
            findBridges(v, t, tLow);
            tLow[u] = min(tLow[u], tLow[v]);
            if(tLow[v] > stamps[u].f){
                cout << u << " " << v << endl;
            }
        }
        else if(v != parents[u])
            tLow[u] = min(tLow[u], stamps[v].f);    
    }//for
    colors[u] = 'B';
}
