#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <iterator>
#include <algorithm>

#define INFINITY 65535
#define DEFAULT_SIZE 10
#define MAXNUM 100
using namespace std;
typedef struct
{
    int lineNum[3] = {5,5,7};
    vector<vector<int> > car;
    vector<vector<int> > cross;
    vector<vector<int> > road;
}Graph;
void getGraph(Graph &g,string filePath[3]);
void readText(string filePath,vector<vector<int> > &targetVector,int lineNum);
void loadText(vector<vector<int> > &car,vector<vector<int> > &cross,vector<vector<int> > &road,const int n[3],const string *p);
void writeToTxt(const vector<vector<int> > &sorce,string filePath);

void getGraph(Graph &g,string filePath[3])
{
//    cout << "getGraph" << endl;
//    string filePath[3] = {"../config/car.txt","../config/cross.txt","../config/road.txt"};
    loadText(g.car,g.cross,g.road,g.lineNum,filePath);
}
void readText(string filePath,vector<vector<int> > &targetVector,int lineNum)
{
//    cout << "readText" << filePath << endl;
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
//        cout << "readText" << endl;
        inf >> p;
        for(int i = 0;i < lineNum;i++)
        {
//            cout << "readTextinwhielloop " << i << endl;
            inf >> lane[i] >> p;
        }
        targetVector.push_back(lane);
    }
    targetVector.erase(targetVector.end() - 1 ,targetVector.end());
    inf.close();
}
void loadText(vector<vector<int> > &car,vector<vector<int> > &cross,vector<vector<int> > &road,const int n[3],const string *p)
{
//    cout << "loadText" << endl;
    readText(p[0],car,n[0]);
    readText(p[1],cross,n[1]);
    readText(p[2],road,n[2]);
}

void writeToTxt(const vector<vector<int> > &sorce,string filePath)
{
    int i,j,rowNum;
    int lineNum = sorce.size();
//    cout << lineNum << endl;
    ofstream outf;
    outf.open(filePath);
    for(i = 0;i < lineNum;i++)
    {
        j = 0;
        rowNum = sorce[i].size();
        outf << "(" << sorce[i][j];
        for(j = 1;j < rowNum;j++)
        {
            outf << "," << sorce[i][j];
        }
        outf << ")" << endl;
    }
    outf.close();
}

typedef struct
{
    int vertexNum,edgeNum;//顶点数，边数（连接的边数）
    vector<int*> vexs;//顶点数组
    vector<vector<int> > matrix;//邻接矩阵
}AdjMatrix;
void coutVector(vector<vector<int> > a);//打印vector
void coutVector(vector<int> a);
void coutVector(vector<int*> a);
void creatMetrix(AdjMatrix &g,vector<int> &v,vector<vector<int> > m,int n);//生成邻接矩阵
void getNetNode(vector<vector<int> > &net,const vector<vector<int> >&road);//将road中的路口信息提取出路口ID及长度

void creatMetrix(AdjMatrix &g,vector<int> &v,vector<vector<int> > m,int num)
{//生成邻接矩阵，m为路口ID及长度组成的矩阵，v为顶点数组，num为路口数
    int i,j,k;
    g.edgeNum = m.size();//边数
    g.vertexNum = num;
//    cout << g.edgeNum << " " << g.vertexNum << endl;
    for(i = 0;i < g.vertexNum;i++)
    {
        g.vexs.push_back(&v[i]);
//        cout << *(g.vexs.back()) << " ";
    }
//    g.vexs.insert(g.vexs.end(),v.begin(),v.end());
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
        for(i = 0;i < g.vertexNum;i++)
        {
            if(m[k][0] == *(g.vexs[i]))
                break;
        }
        for(j = 0;j < g.vertexNum;j++)
        {
            if(m[k][1] == *(g.vexs[j]))
                break;
        }
        g.matrix[i][j] = m[k][2];
//        cout << "(i,j) = " << i << " " << j << endl;
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
void coutVector(vector<int*> a)
{
    int i;
    int num = a.size();
    for(i = 0;i < num;i++)
        cout << *a[i] << " ";
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


void shortPathDijkstra(const AdjMatrix &g,int start,vector<vector<int> > &pathPlan);
void shortPathMatrix(const AdjMatrix &g,vector<vector<int> > &pathTable);
void creatRoadIDMatrix(const vector<vector<int> > &pathTable,vector<vector<int> > &roadIDMatrix,const Graph &g);
void carRunTime(const Graph &g, vector<vector<int> > &roadIDMatrix,vector<vector<int> > &carRunTime);
void creatCarRunOrder(const vector<vector<int> > &carRunTime,vector<vector<int> > &CarRunOrder);

bool comp(vector<int> &a,vector<int> &b);

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
//    coutVector(path);
//    coutVector(pathTable);
    for(v = 0;v < g.vertexNum;v++)
    {//生成路径矩阵
//        cout << "pathpalnstart" << endl;
        vector<int> pathPlanTemp;
        if(*(g.vexs[v]) != *(g.vexs[start]))
        {
//            cout << "pathpaln1" << endl;
            k = v;
            if(pathTable[v] == INFINITY)
            {
                pathPlanTemp.push_back(*(g.vexs[start]));
                pathPlanTemp.push_back(*(g.vexs[v]));
                pathPlanTemp.push_back(-1);
                continue;
            }
            pathPlanTemp.push_back(*(g.vexs[v]));
            while(path[k] != -1)
            {
//                cout << "pathpaln2" << endl;
                k = path[k];
                pathPlanTemp.push_back(*(g.vexs[k]));
            }
            pathPlanTemp.push_back(*(g.vexs[start]));
            pathPlanTemp.push_back(*(g.vexs[v]));
            pathPlanTemp.push_back(*(g.vexs[start]));
            reverse(pathPlanTemp.begin(),pathPlanTemp.end());
            pathPlan.push_back(pathPlanTemp);
//            coutVector(pathPlanTemp);
            pathPlanTemp.clear();
        }
    }
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
        n = pathTable[i].size() - 1;
        for(w = 2;w < n;w++)
        {
            for(j = 0;j < rSize;j++)
            {
                eq1 = ( (pathTable[i][w] == g.road[j][4]) && (pathTable[i][w+1] == g.road[j][5]) );
                eq2 = ( (pathTable[i][w+1] == g.road[j][4]) && (pathTable[i][w] == g.road[j][5]) );
                if( eq1 || (eq2 && (g.road[j][6] == 1))  )//(eq1 || eq2) && (g.road[j][6] == 1)
                {
                    temp.push_back(g.road[j][0]);
                }
            }
        }
        roadIDMatrix.push_back(temp);
        temp.clear();
    }
}
void carRunTime(const Graph &g, vector<vector<int> > &roadIDMatrix,vector<vector<int> > &carRuntime)
{
//    cout << "carRunTime" << endl;
    int i,j,k,n,m;
    int carID,carFrom, carTo,carV,carPlanTime;
    int roadLength,roadV;
    int runTime,runV;
    int carNum = g.car.size();
    int roadMNum = roadIDMatrix.size();
    int roadNum = g.road.size();
    vector<int> temp;
//    cout << roadMNum << endl;
//    cout << "run1" << endl;
    for(i = 0;i < carNum;i++)
    {
//        cout << "run2" << endl;
        runTime = 0;
        carID = g.car[i][0];
        carFrom = g.car[i][1];
        carTo = g.car[i][2];
        carV = g.car[i][3];
        carPlanTime = g.car[i][4];
        if(carFrom == carTo)//出发点和终点重合，行驶时间为0
        {
            carRuntime.push_back({carID,carFrom,carTo,runTime,carPlanTime,-1});
            break;
        }
        for(j = 0;j < roadMNum;j++)//roadIDMatrix中找起点和终点匹配的路径
        {
//            cout << "run3 " << " " << carFrom << " " << carTo<< " "  << roadIDMatrix[j][0] << " " << roadIDMatrix[j][1]<< " "  << j <<endl;
            if(carFrom == roadIDMatrix[j][0] && carTo == roadIDMatrix[j][1])
            {
//                cout << "find" << endl;
                break;
            }
        }
        if(roadIDMatrix[j][2] == -1) //路径不存在
        {
            runTime = 0;
        }
        else
        {
            n = roadIDMatrix[j].size();
            for(int k = 2;k < n;k++)//起点终点匹配之后，循环计算每条道路所花时间
            {
//                cout << "run4" << endl;
                for(m = 0;m < roadNum;m++)//对每条道路进行匹配，得到道路长度与最高速度
                {
//                    cout << "run4.5 "<< roadIDMatrix[j][k]<< " " << g.road[m][0]
//                         << " k m" << k << " " << m << endl;

                    if((roadIDMatrix[j][k]) == (g.road[m][0]))
                    {
//                        cout << "run5" << endl;
                        roadLength = g.road[m][1];
                        roadV = g.road[m][2];
                        break;
                    }
                }
                runV = ( (carV > roadV) ? roadV:carV );
                runTime += ((roadLength + 1) / runV );
            }
        }

//        carRuntime.push_back({carID,carFrom,carTo,runTime});
//        cout << i <<" " << j << " " << k << endl;
//        coutVector(roadIDMatrix[j]);
        temp.push_back(carID);
        temp.push_back(carFrom);
        temp.push_back(carTo);
        temp.push_back(runTime);
        temp.push_back(carPlanTime);
//        coutVector(temp);
//        cout << "roadIDMatrix[j][b]  ";
        for(int b = 2;b < roadIDMatrix[j].size();b++ )
        {
            temp.push_back(roadIDMatrix[j][b]);
//            cout << roadIDMatrix[j][b] << " ";
        }
//        cout << endl;
//        temp.insert(temp.end(),roadIDMatrix[j].begin() + 2, roadIDMatrix[j].end());
        carRuntime.push_back(temp);
        temp.clear();
    }
}
//void creatCarRunOrder(const vector<vector<int> > &carRunTime,vector<vector<int> > &CarRunOrder)
//{
//    int i,j;
//    int startTime = 1;
//    int timeTemp = 0;
//    int carID,carRuntime,carPlantime;
//    int carNum = carRunTime.size();
//    vector<int> temp;
//    carID = carRunTime[0][0];
//    carRuntime = carRunTime[0][3];
//    carPlantime = carRunTime[0][4];
//    startTime = (startTime > carPlantime)?startTime:carPlantime;
//    temp.push_back(carID);
//    temp.push_back(startTime);
//    for(int j = 5;j < carRunTime[0].size();j++ )
//    {
//        temp.push_back(carRunTime[0][j]);
//    }
//    CarRunOrder.push_back(temp);
//    temp.clear();
//    for(i = 1;i < carNum;i++)
//    {
//        carID = carRunTime[i][0];
//        carRuntime = carRunTime[i][3];
//        carPlantime = carRunTime[i][4];
//        if(carRuntime == 0)
//        {
//            timeTemp = startTime;
//            startTime = carPlantime;
//            CarRunOrder.push_back({carID,startTime});
//        }
//        else
//        {
//            startTime += (timeTemp + 0.1*carRunTime[i][3] + carPlantime);
//            temp.push_back(carID);
//            temp.push_back(startTime);
//            for(int j = 5;j < carRunTime[i].size();j++ )
//            {
//                temp.push_back(carRunTime[i][j]);
//            }
//            CarRunOrder.push_back(temp);
//            temp.clear();
//        }
//    }
//}
//

//void creatCarRunOrder(const vector<vector<int> > &carRunTime,vector<vector<int> > &CarRunOrder)
//{
//    int i,j,k,n;
//    int startTime = 1;
//    int timeTemp = 0;
//    int runNum = 200;//同时跑的车辆为  runNum
//    int carID,carRuntime;
//    int carPlantime = 0;
//    int carNum = carRunTime.size();
//    int frontNum = carNum % runNum;
//    int maxTime = 100;
//    int maxDt = 10;
//    int a = -4*maxDt/(maxTime*maxTime);
//    int b = 4*maxDt/maxTime;
//    vector<int> temp;
//    for(i = 0;i < frontNum;i++)
//    {
//        carPlantime = (carPlantime > carRunTime[i][4] ? carPlantime:carRunTime[i][4]);
//    }
//    startTime = (startTime > carPlantime)?startTime:carPlantime;
////    cout << "startTime: " << startTime << "  carPlantime: " << carPlantime << endl;
//    for(k = 0;k < frontNum;k++)
//    {
//        carID = carRunTime[k][0];
//        carRuntime = carRunTime[k][3];
//        carPlantime = carRunTime[k][4];
//        temp.push_back(carID);
//        temp.push_back(startTime);
//        for(int j = 5;j < carRunTime[k].size();j++ )
//        {
//            temp.push_back(carRunTime[k][j]);
//        }
//        CarRunOrder.push_back(temp);
//        temp.clear();
//    }
//    for(k = frontNum;k < carNum;k += runNum )
//    {
//        timeTemp = 0;
//        n = k + runNum;
//        for(i = k;i < n;i++)
//        {
//            timeTemp = ( timeTemp > carRunTime[i][3]? timeTemp:carRunTime[i][3] );
//            carPlantime = (carPlantime > carRunTime[i][4] ? carPlantime:carRunTime[i][4]);
//        }
//        startTime = 0.9999*startTime + carPlantime +  a* timeTemp*timeTemp + b*timeTemp;
////        cout << "startTime: " << startTime << "  carPlantime: " << carPlantime << endl;
//        for(i = k;i < n;i++)
//        {
//            carID = carRunTime[i][0];
//            carRuntime = carRunTime[i][3];
//            carPlantime = carRunTime[i][4];
//            temp.push_back(carID);
//            temp.push_back(startTime);
//            for(int j = 5;j < carRunTime[i].size();j++ )
//            {
//                temp.push_back(carRunTime[i][j]);
//            }
//            CarRunOrder.push_back(temp);
//            temp.clear();
//        }
//    }
//}

//version3
void creatCarRunOrder(const vector<vector<int> > &carRunTime,vector<vector<int> > &CarRunOrder)
{

    int i,j,k,n;
    float dt;
    float dt1 = 0.6;
    float dt2 = 0.4;
    float dn = 1.5;
    int dcar = 30;
    int cnum = 4;
    int startTime = 1;
    int timeTemp = 0;
    int carID,carRuntime;
    int carPlantime = 0;
    int carNum = carRunTime.size();
    int runNum = 200;//同时跑的车辆为  runNum
    int num1 = 200;
    int frontNum = 0;//行驶车辆数目
    int timeCount = 0;
    vector<vector<int> > timeAnum;//统计每辆车行驶时间及其时间出现的次数
    vector<int> temp;
    n = carNum-1;
    for(i = 0;i < carNum;++i)
    {
        timeCount = 1;
        carRuntime = carRunTime[i][3];
        for(;i < n;++i)
        {
            if(carRunTime[i][3] != carRunTime[i+1][3])
                break;
            ++timeCount;
        }
        timeAnum.push_back({carRuntime,timeCount});


    }
//     writeToTxt2(timeAnum,"../config/timeAnum.txt");
    timeCount = 0;
//    coutVector(timeAnum);
    for(i = 0;i < cnum;i++)//前 cnum 组车辆数量frontNum
        frontNum += timeAnum[i][1];
//    cout << "frontNum : " << frontNum << endl;
    for(i = 0;i < frontNum;i++)//前 frontNum 车按计划时间跑
    {

        carPlantime = (carPlantime > carRunTime[i][4] ? carPlantime:carRunTime[i][4]);
        carID = carRunTime[i][0];
        startTime = carRunTime[i][4];
        temp.push_back(carID);
        temp.push_back(startTime);
//        cout << "start i : " << i << " " << endl;
        for(int j = 5;j < carRunTime[i].size();j++ )
        {
            temp.push_back(carRunTime[i][j]);
//            cout << "i : " << i << " ";
//            coutVector(temp);
        }
        CarRunOrder.push_back(temp);
//        cout << "i : " << i << " ";
//        coutVector(temp);
        temp.clear();
    }
//    coutVector(CarRunOrder);
    startTime = carPlantime;//取最大计划出发时间
    for(i = frontNum;i < carNum;i += runNum)
    {
//        cout << "start i : " << i << " " << endl;
        runNum = num1;
        carRuntime = carRunTime[i][3];
        for(j = 0;j < timeAnum.size();j++)
        {
//            cout << "start j : " << j << " " << endl;
            if(carRuntime == timeAnum[j][0])
            {
//                cout << carRuntime << " " << timeAnum[j][0] <<endl;
                timeCount = timeAnum[j][1];
                break;
            }
        }
        if( (timeCount < runNum) && (carRuntime < dcar) )//车少时间短
        {
            dt = dt1;
        }
        else if((timeCount < runNum) && (carRuntime >= dcar))//车少时间长
        {
            dt = dt2;
        }
        else if((timeCount >= runNum) && (carRuntime < dcar))//车多时间短
        {
            runNum /= dn;
            dt = dt2;
        }
        else //if((timeCount >= runNum) && (carRuntime >= 50))//车多时间长
        {
            runNum /= dn;
            dt = dt2;
        }
        startTime += dt * carRuntime;
        n = i + runNum;
        for(k = i;(k < n) && (k < carNum);k++)
        {

            carID = carRunTime[k][0];
            carRuntime = carRunTime[k][3];
            carPlantime = carRunTime[k][4];
            temp.push_back(carID);
            temp.push_back(startTime);
            for(int j = 5;j < carRunTime[k].size();j++ )
            {
                temp.push_back(carRunTime[k][j]);
            }
            CarRunOrder.push_back(temp);
//            cout << "k: " << k << " n " << n << endl;
//            coutVector(temp);
            temp.clear();
        }
//        cout << "2 k: " << k << " n " << n << " runNum " << runNum<< endl;
    }
//    cout <<"end" << endl;
//    coutVector(CarRunOrder);
    if(i < carNum)
    {
        carRuntime = carRunTime[i][3];
        startTime += dt * carRuntime;
        for(;i < carNum;i++)
        {
            carID = carRunTime[i][0];
            carRuntime = carRunTime[i][3];
            carPlantime = carRunTime[i][4];
            temp.push_back(carID);
            temp.push_back(startTime);
            for(int j = 5;j < carRunTime[i].size();j++ )
            {
                temp.push_back(carRunTime[i][j]);
            }
            CarRunOrder.push_back(temp);
            temp.clear();
        }
    }
}



bool comp3(vector<int> &a,vector<int> &b)
{
    return (a[3] < b[3]);
}
bool comp4(vector<int> &a,vector<int> &b)
{
    return (a[4] > b[4]);
}
int main(int argc, char *argv[])
//int main()
{
    cout << "Begin" << endl;

    if(argc < 5){
		cout << "please input args: carPath, roadPath, crossPath, answerPath" << endl;
		exit(1);
	}

	string carPath(argv[1]);
	string roadPath(argv[2]);
	string crossPath(argv[3]);
	string answerPath(argv[4]);

	cout << "carPath is " << carPath << endl;
	cout << "roadPath is " << roadPath << endl;
	cout << "crossPath is " << crossPath << endl;
	cout << "answerPath is " << answerPath << endl;


//    string carPath = {"../config/car.txt"};
//    string roadPath = {"../config/road.txt"};
//    string crossPath = {"../config/cross.txt"};
//    string answerPath = {"../config/answer.txt"};
    string filePath[3] = {carPath,crossPath,roadPath};
	Graph g;//读取赛题文件
	int i;
    AdjMatrix graf;//邻接矩阵
    vector<vector<int> > netNode;       //将road中的路口信息提取出路口ID及长度
    vector<vector<int> > path;                   //最短路径矩阵，存放路口ID
    vector<vector<int> > pathTable;     //最短路径矩阵，存放道路ID
    vector<vector<int> > carRuntime;    //车辆在最短路径上行驶时间
    vector<vector<int> > CarRunOrder;   //车辆出发时间顺序
    vector<int> vexs;
    getGraph(g,filePath);
    int crossNum = g.cross.size();           //获取路口ID数量
    for(i = 0;i<= crossNum;i++)              //获取路口ID
        vexs.push_back(g.cross[i][0]);
    getNetNode(netNode,g.road);             //将road中的路口信息提取出路口ID及长度
    creatMetrix(graf,vexs,netNode,crossNum);//邻接矩阵
    shortPathMatrix(graf,path);              //最短路径矩阵，存放路口ID
    creatRoadIDMatrix(path,pathTable,g);    //最短路径矩阵，存放道路ID
    carRunTime(g,pathTable,carRuntime);             //车辆在最短路径上行驶时间

//    writeToTxt(carRuntime,"../config/carRuntime.txt");
//    sort(carRuntime.begin(),carRuntime.end(),comp4);
    sort(carRuntime.begin(),carRuntime.end(),comp3);//根据车辆在最短路径上行驶时间进行排序
    creatCarRunOrder(carRuntime,CarRunOrder);       //车辆出发时间顺序
    writeToTxt(CarRunOrder,answerPath);             //写入answer.txt

//    writeToTxt(pathTable,"../config/RoadIDMatrix.txt");
//    writeToTxt(path,"../config/RoadID.txt");


//    coutVector(carRuntime);
	// TODO:read input filebuf
	// TODO:process
	// TODO:write output file

	return 0;
}


