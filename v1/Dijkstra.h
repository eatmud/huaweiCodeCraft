#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include "AdjMatrix.h"
#include "Graph.h"

using namespace std;
void shortPathDijkstra(const AdjMatrix &g,int start,vector<vector<int> > &pathPlan);
void shortPathMatrix(const AdjMatrix &g,vector<vector<int> > &pathTable);
void shortPathDijkstra(const AdjMatrix &g,int start,vector<vector<int> > &pathPlan)
{//path存放路径顶点下标
//pathTable存放路径最短长度
    int v,w,k,minValue;
    vector<int> path;
    vector<int> pathTable;
    vector<int> final;
    for(v = 0;v < g.vertexNum;v++)
    {
        final.push_back(0);
        pathTable.push_back(g.matrix[start][v]);
        path.push_back(-1);
    }
    pathTable[start] = 0;
    final[start] = 0;

    for(v = 1;v < g.vertexNum;v++)
    {
        minValue = INFINITY;
        for(w = 0;w < g.vertexNum;w++)
        {
            if(!final[w] && pathTable[w] < minValue)
            {
                k = w;
                minValue = pathTable[w];
            }
        }
        final[k] = 1;
        for(w = 0;w < g.vertexNum;w++)
        {
            if(!final[w] && (minValue + g.matrix[k][w]) < pathTable[w])
            {
                pathTable[w] =  minValue + g.matrix[k][w];
                path[w] = k;
            }
        }
    }
    for(v = 0;v < g.vertexNum;v++)
    {//生成路径矩阵
        vector<int> pathPlanTemp;
        if((v+1) != g.vexs[start])
        {
            k = v;
            if(pathTable[v] == INFINITY)
            {
                pathPlanTemp.push_back(g.vexs[start]);
                pathPlanTemp.push_back(g.vexs[v]);
                pathPlanTemp.push_back(-1);
                continue;
            }
            pathPlanTemp.push_back(g.vexs[v]);
            while(path[k] != -1)
            {
                k = path[k];
                pathPlanTemp.push_back(g.vexs[k]);
            }
            pathPlanTemp.push_back(g.vexs[start]);
            pathPlanTemp.push_back(g.vexs[v]);
            pathPlanTemp.push_back(g.vexs[start]);
            reverse(pathPlanTemp.begin(),pathPlanTemp.end());
            pathPlan.push_back(pathPlanTemp);
            pathPlanTemp.clear();
        }
    }
//    coutVector(pathPlan);
//    for(v = 0;v < g.vertexNum;v++)
//    {//打印路径
//        vector<int> pathPlanTemp;
//        if((v+1) != g.vexs[start])
//        {
//            cout << "From " << g.vexs[start] << " to " << g.vexs[v]
//                 << " pathLength: " << pathTable[v] << " path is: ";
//            k = v;
//            if(pathTable[v] == INFINITY)
//            {
//                cout << "NO path !" << endl;
//                continue;
//            }
//            cout << g.vexs[v];
//            while(path[k] != -1)
//            {
//                k = path[k];
//                cout << "<-" << g.vexs[k];
//            }
//            cout << "<-" << g.vexs[start];
//            cout << endl;
//        }
//    }
}
void shortPathMatrix(const AdjMatrix &g,vector<vector<int> > &pathTable)
{
    int i = 0,j = 0,n;
    int gSize = g.vertexNum;
    vector<vector<int> > pathTemp;
    for(;i < gSize;i++)
    {
        shortPathDijkstra(g,i,pathTemp);
        n = pathTemp.size();
        for(j = 0;j < n;j++)
            pathTable.push_back(pathTemp[j]);
        pathTemp.clear();
    }
}
#endif // DIJKSTRA_H_INCLUDED
