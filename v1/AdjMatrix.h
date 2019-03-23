#ifndef ADJMATRIX_H_INCLUDED
#define ADJMATRIX_H_INCLUDED

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>



#define INFINITY 65535
#define DEFAULT_SIZE 10
#define MAXNUM 100

using namespace std;

typedef struct
{
    int vertexNum,edgeNum;//顶点数，边数（连接的边数）
    vector<int> vexs;//顶点数组
    vector<vector<int> > matrix;//邻接矩阵
}AdjMatrix;

void coutVector(vector<vector<int> > a);//打印vector
void coutVector(vector<int> a);
void creatMetrix(AdjMatrix &g,vector<int> v,vector<vector<int> > m,int n);//生成邻接矩阵
void getNetNode(vector<vector<int> > &net,const vector<vector<int> >&road);//将road中的路口信息提取出路口ID及长度


void creatMetrix(AdjMatrix &g,vector<int> v,vector<vector<int> > m,int num)
{//生成邻接矩阵，m为路口ID及长度组成的矩阵，v为顶点数组，num为路口数
    int i,j,k,w;
    g.edgeNum = m.size();//边数
    g.vertexNum = num;
//    cout << g.edgeNum << " " << g.vertexNum << endl;
    g.vexs.insert(g.vexs.end(),v.begin(),v.end());
//    coutVector(g.vexs);
    for(i = 0;i < g.vertexNum;i++)//初始化邻接矩阵
    {
        vector<int> temp(g.vertexNum);
        for(j = 0;j < g.vertexNum;j++)
            temp[j] = INFINITY;
        g.matrix.push_back(temp);
    }
//    coutVector(g.matrix);
    for(k = 0;k < g.edgeNum;k++)//邻接矩阵赋值
    {
        i = m[k][0] - 1;
        j = m[k][1] - 1;
        w = m[k][2];
        g.matrix[i][j] = w;
//        cout << g.matrix[i][j] << " ";
    }
//    cout << endl;
//    coutVector(g.matrix);
}
void coutVector(vector<vector<int> > a)
{
    int lineNum = a.size();
//    cout << rowNum << " " << lineNum << endl;
    for(int i = 0;i< lineNum;i++)
    {
        int rowNum = a[i].size();
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
void getNetNode(vector<vector<int> > &net,const vector<vector<int> >&road)
{//将road中的路口信息提取出路口ID及长度
    int i,length,line,row;
    int roadSize = road.size();
    vector<int> temp(3);
    for(i = 0;i < roadSize;i++)
    {
        length = road[i][1];
        line = road[i][4];
        row = road[i][5];
        net.push_back({line,row,length});
        if(road[i][6] == 1)
            net.push_back({row,line,length});
    }
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
