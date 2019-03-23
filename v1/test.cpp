//#include <iostream>
//#include <vector>
//#include <string>
//#include <iterator>
//#include <algorithm>
//
//#include "AdjMatrix.h"
//
//using namespace std;
//
////#define INFINITY 500
////#define DEFAULT_SIZE 10
////#define MAXNUM 5
////typedef struct
////{
////    int vertexNum,edgeNum;//
////    vector<int> vexs;//
////    vector<vector<int> > matrix;
////}AdjMatrix;
////void coutVector(vector<vector<int> > a);
////void creatMetrix(AdjMatrix g,vector<int> v,vector<vector<int> > m,int n);
////void creatMetrix(AdjMatrix g,vector<int> v,vector<vector<int> > m,int num)
////{
////    int i,j,k,w;
////    g.edgeNum = num;
////    g.vertexNum = num;
////    cout << g.edgeNum << " " << g.vertexNum << endl;
////    g.vexs.insert(g.vexs.end(),v.begin(),v.end());
////    for(k = 0;k < g.vexs.size();k++)
////        cout << g.vexs[k] << " ";
////    cout << endl;
////    for(i = 0;i < g.vertexNum;i++)
////    {
////        vector<int> temp(g.vertexNum);
////        for(j = 0;j < g.vertexNum;j++)
////            temp[j] = INFINITY;
////        g.matrix.push_back(temp);
////    }
////    coutVector(g.matrix);
////    for(k = 0;k < g.vertexNum;k++)
////    {
////        i = m[k][0]-1;
////        j = m[k][1]-1;
////        w = m[k][2];
////        g.matrix[i][j] = w;
////    }
////    coutVector(g.matrix);
////}
//int main()
//{
//    cout << "start!" << endl;
//    int i;
//    AdjMatrix g;
//    int num = 5;
//    vector<int> v(num);
//    v = {1,2,3,4,5};
//    for(i = 0;i < v.size();i++)
//        cout << v[i] << " ";
//    cout << endl;
//    vector<vector<int> > m(num);
//    m = {{1,2,3},{2,3,3},{3,4,3},{3,1,3},{4,5,3}};
//    coutVector(m);
//    creatMetrix(g,v,m,num);
//    return 0;
//}
//
//
