#ifndef ADJMATRIX_H_INCLUDED
#define ADJMATRIX_H_INCLUDED

#include <iostream>
#include <vector>

#define INFINITY 65535
#define DEFAULT_SIZE 10
#define MAXNUM 100

using namespace std;

void coutVector(vector<vector<int> > a);
void coutVector(vector<int> a);
typedef struct
{
    int vertexNum,edgeNum;//
    vector<int> vexs;//
    vector<vector<int> > matrix;
}AdjMatrix;
void coutVector(vector<vector<int> > a);
void creatMetrix(AdjMatrix &g,vector<int> v,vector<vector<int> > m,int n);
void creatMetrix(AdjMatrix &g,vector<int> v,vector<vector<int> > m,int num)
{
    int i,j,k,w;
    g.edgeNum = m.size();
    g.vertexNum = num;
    cout << g.edgeNum << " " << g.vertexNum << endl;
    g.vexs.insert(g.vexs.end(),v.begin(),v.end());
//    for(k = 0;k < g.vexs.size();k++)
//        cout << g.vexs[k] << " ";
//    cout << endl;
    for(i = 0;i < g.vertexNum;i++)
    {
        vector<int> temp(g.vertexNum);
        for(j = 0;j < g.vertexNum;j++)
            temp[j] = INFINITY;
        g.matrix.push_back(temp);
    }
//    coutVector(g.matrix);
    for(k = 0;k < g.edgeNum;k++)
    {
        i = m[k][0]-1;
        j = m[k][1]-1;
        w = m[k][2];
        g.matrix[i][j] = w;
        cout << g.matrix[i][j] << " ";
    }
    cout << endl;
//    coutVector(g.matrix);
}
void coutVector(vector<vector<int> > a)
{
    int lineNum = a.size();
    int rowNum = a[0].size();
//    cout << rowNum << " " << lineNum << endl;
    for(int i = 0;i< lineNum;i++)
    {
        for(int j = 0;j < rowNum;j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}
void coutVector(vector<int> a)
{
    int i;
    int num = a.size();
    for(i = 0;i < num;i++)
        cout << a[i] << " ";
    cout << endl;
}
//class AdjMatrix
//{
//private:
//    vector<int> vex;//顶点表
//    vector<vector<int> > matrix;//邻接矩阵
//    int vertexNum,edgeNum;//顶点数与边数
//public:
//    AdjMatrix(int vNum = DEFAULT_SIZE,int eNum = DEFAULT_SIZE);
//    AdjMatrix(vector<int> v, vector<vector<int> > m);
//    ~AdjMatrix() {};
//    void dispAdjMatrix();
//};
//
//AdjMatrix::AdjMatrix(int vNum,int eNum)
//{
//    vex = {0};
//    vertexNum = vNum;
//    edgeNum = eNum;
//    for(int i = 0;i < vertexNum;i++)
//    {
//        for(int j = 0;j < vertexNum;j++)
//            matrix[i][j] = DEFAULT_INFINITY;
//    }
//}
//AdjMatrix::AdjMatrix(vector<int> v, vector<vector<int> > m)
//{
//    vex = v;
//    edgeNum = vertexNum = m.size();
//    for(int i = 0;i < vertexNum;i++)
//    {
//        int j = m[i][1];
//        int w = m[i][2];
//        matrix[i][j] = w;
//    }
//}
////void AdjMatrix::insertAdjMatrix(vector<int> node)
////{
////    int a = node[0];
////    int b = node[1];
////    int length = node[2];
////    matrix[a][b] = length;
////}
//void AdjMatrix::dispAdjMatrix()
//{
//    int lineNum = matrix.size();
//    int rowNum = matrix[0].size();
////    cout << rowNum << " " << lineNum << endl;
//    for(int i = 0;i< lineNum;i++)
//    {
//        for(int j = 0;j < rowNum;j++)
//            cout << matrix[i][j] << " ";
//        cout << endl;
//    }
//}
#endif // ADJMATRIX_H_INCLUDED
