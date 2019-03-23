#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>

using namespace std;

typedef struct
{
    int lineNum[3] = {5,5,7};
    vector<vector<int> > car;
    vector<vector<int> > cross;
    vector<vector<int> > road;
}Graph;
void readText(string filePath,vector<vector<int> > &targetVector,int lineNum);
void loadText(vector<vector<int> > &car,vector<vector<int> > &cross,vector<vector<int> > &road,const int *n,const string *p);
void getGraph(Graph &g)
{
    string filePath[3] = {"../config/car.txt","../config/cross.txt","../config/road.txt"};
    loadText(g.car,g.cross,g.road,g.lineNum,filePath);
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
#endif // GRAPH_H_INCLUDED
