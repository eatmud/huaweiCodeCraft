#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include "AdjMatrix.h"
using namespace std;

void shortPathDijkstra(const AdjMatrix &g,int start,vector<int> &path,vector<int> &pathTable)
{
    int v,w,k,minValue;
    vector<int> final;
    for(v = 0;v < g.vertexNum;v++)
    {
        final.push_back(0);
        pathTable.push_back(g.matrix[start][v]);
        path.push_back(0);
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
}

#endif // DIJKSTRA_H_INCLUDED
