#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <iterator>
#include <algorithm>

#include "AdjMatrix.h"
#include "Dijkstra.h"
#include "Graph.h"
using namespace std;
int main(int argc, char *argv[])
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
//    coutVector(roadIDMatrix);
//    coutVector(pathTable);
//    coutVector(path);
    shortPathMatrix(graf,pt);
    creatRoadIDMatrix(pt,p,g);
//    coutVector(p);
//    coutVector(pt);
    vector<vector<int> > carRuntime;
    carRunTime(g,p,carRuntime);
//    coutVector(carRuntime);
    sort(carRuntime.begin(),carRuntime.end(),comp);
//    coutVector(carRuntime);
    vector<vector<int> > CarRunOrder;
    creatCarRunOrder(carRuntime,CarRunOrder);
//    coutVector(CarRunOrder);
    writeToTxt(CarRunOrder,answerPath);
	// TODO:read input filebuf
	// TODO:process
	// TODO:write output file
	
	return 0;
}
