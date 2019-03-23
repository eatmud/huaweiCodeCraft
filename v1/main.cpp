#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <iterator>
//#include "AdjMatrixDirNetwork.h"
//#include "ShortestPathDijkstra.h"
#include "AdjMatrix.h"
#include "Dijkstra.h"
#include "Graph.h"

using namespace std;
void creatRoadIDMatrix(const vector<vector<int> > &pathTable,vector<vector<int> > &roadIDMatrix,const Graph &g);
int main()
{
    Graph g;//读取赛题文件
    getGraph(g);
    vector<vector<int> > netNode;//
    vector<int> path;
    vector<vector<int> > pathTable;
    vector<vector<int> > p;
    vector<vector<int> > pt;
    vector<vector<int> > roadIDMatrix;
    vector<int> vexs;
    int i;
    AdjMatrix graf;
    int crossNum = g.cross.size();
    for(i = 1;i<= crossNum;i++)
        vexs.push_back(i);
    getNetNode(netNode,g.road);
//    coutVector(netNode);
    creatMetrix(graf,vexs,netNode,crossNum);
//    coutVector(graf.matrix);
    shortPathDijkstra(graf,0,pathTable);
    creatRoadIDMatrix(pathTable,roadIDMatrix,g);
    coutVector(roadIDMatrix);
//    coutVector(pathTable);
//    coutVector(path);
    shortPathMatrix(graf,pt);
    creatRoadIDMatrix(pt,p,g);
    coutVector(p);
    coutVector(pt);
	return 0;
}

void creatRoadIDMatrix(const vector<vector<int> > &pathTable,vector<vector<int> > &roadIDMatrix,const Graph &g)
{
    int i,j,w,n;
    bool eq1,eq2;
    int pSize = pathTable.size();
    int rSize = g.road.size();
    vector<int> temp;
    for(i = 0;i < pSize;i++)
    {
        temp.push_back(pathTable[i][0]);
        temp.push_back(pathTable[i][1]);
        n = pathTable[i].size();
        for(w = 2;w < n;w++)
        {
            for(j = 0;j < rSize;j++)
            {
                eq1 = ( (pathTable[i][w] == g.road[j][4]) && (pathTable[i][w+1] == g.road[j][5]) );
                eq2 = ( (pathTable[i][w+1] == g.road[j][4]) && (pathTable[i][w] == g.road[j][5]) );
                if( (eq1 || eq2) && (g.road[j][6] == 1) )
                {
                    temp.push_back(g.road[j][0]);
                }
            }
        }
        roadIDMatrix.push_back(temp);
        temp.clear();
    }
}




