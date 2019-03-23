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

using namespace std;

void readText(string filePath,vector<vector<int> > &targetVector,int lineNum);
void loadText(vector<vector<int> >&,vector<vector<int> >&,vector<vector<int> >&,const int*,const string*);
void getNetNode(vector<vector<int> >&,const vector<vector<int> >&);
//void InsertArc(AdjMatrixDirNetwork&,const vector<vector<int> >&);
int main()
{
    vector<vector<int> > car;
    vector<vector<int> > cross;
    vector<vector<int> > road;
    vector<vector<int> > netNode;
    vector<int> path;
    vector<int> pathTable;
    vector<int> vexs;
    int i;
    AdjMatrix graf;
    int lineNum[3] = {5,5,7};
    string filePath[3] = {"../config/car.txt","../config/cross.txt","../config/road.txt"};
    loadText(car,cross,road,lineNum,filePath);
    int crossNum = cross.size();
    for(i = 1;i<= crossNum;i++)
        vexs.push_back(i);
    getNetNode(netNode,road);
    coutVector(netNode);
    creatMetrix(graf,vexs,netNode,crossNum);
    coutVector(graf.matrix);
    shortPathDijkstra(graf,0,path,pathTable);
    coutVector(pathTable);
    coutVector(path);
	return 0;
}
void getNetNode(vector<vector<int> > &net,const vector<vector<int> >&road)
{
    int i,length,line,row;
    int roadSize = road.size();
    vector<int> temp(3);
    for(i = 0;i < roadSize;i++)
    {
        length = road[i][2];
        line = road[i][4];
        row = road[i][5];
        net.push_back({line,row,length});
        if(road[i][6] == 1)
            net.push_back({row,line,length});
    }
}
void readText(string filePath,vector<vector<int> > &targetVector,int lineNum)
{
    ifstream inf;
    string s;
    char p;//标点
    vector<int> lane(lineNum);
    inf.open(filePath);
//    if(!inf.is_open())
//        cout << "Can't open this file in the path : " << filePath << endl;
    getline(inf, s);//getline(inf,s)是逐行读取inf中的文件信息,读取第一行，丢掉
    while (!inf.eof())
    {
        inf >> p;
        for(int i = 0;i < lineNum;i++)
            inf >> lane[i] >> p;
        targetVector.push_back(lane);
    }
    targetVector.erase(targetVector.end() - 1 ,targetVector.end());
    inf.close();
}
void loadText(vector<vector<int> > &car,vector<vector<int> > &cross,vector<vector<int> > &road,const int *n,const string *p)
{
    readText(p[0],car,n[0]);
    readText(p[1],cross,n[1]);;
    readText(p[2],road,n[2]);
}

