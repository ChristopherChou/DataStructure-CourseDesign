#ifndef GRAPH_H
#define GRAPH_H

#define LOVERFLOW	-2	//避免与<math.h>中的定义冲突
#define ERROR -1
#define MAX_VERTEX_NUM 40 //最大顶点数
#define MAX_ARC_NUM 40

#define INF 100000

#include<QDialog>
#include<QLabel>
#include<QPushButton>
#include<QPainter>
//#include<QString>

extern int vexnumber;
extern int PrimResults[MAX_VERTEX_NUM][2];
extern int KruskalResults[MAX_VERTEX_NUM][2];


typedef struct {
    //记录代价最小的边的辅助数组定义
    int adjvex;//顶点集U中到该点为最小的顶点序号
    int lowcost;//那个顶点到该点的权值
}miniside[MAX_VERTEX_NUM];
struct side//图的边信息存储结构
{
    int a, b;//两个顶点
    int weight;//边的权重
};
struct arc{
    char a,b;
    int weight;
};

typedef bool PathMatrix2[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//路径矩阵
typedef int ShortPathTable[MAX_VERTEX_NUM];//最短距离表，一维数组
typedef bool PathMatrix3[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int DistanceMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
//图
class Graph {

private:
    int vexnum;//顶点数
    int arcnum;//边数

    int MGraph[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//邻接矩阵

    //邻接表节点
    struct ArcNode {
        int adjvex;//该弧所指向的顶点的位置(序号)
        int weight;
        ArcNode* nextarc;//指向下一条弧的指针
    };
    ArcNode* firstarc[MAX_VERTEX_NUM];//第一个表节点的地址,指向第一条依附该节点的指针
public:
    char vexs[MAX_VERTEX_NUM];      //顶点向量名称，char类型
public:
    Graph();
    ~Graph();
    int LocateVex(char u);
    void CreateGraph(int vex,int arc,struct arc arcinfo[]);
    void CreateGraphDefault();
    void ShowLinkList(QDialog*);
    void DisplayUDN();

    int minimum(miniside SZ);
    void Prim(char u);
    void Kruskal();
    void MakePath(bool P[], int i, int j,QString&);
    void MakePath2(bool P[], int i, int j,QString&);
    void Shortest_DIJ(int v0,PathMatrix2& P,ShortPathTable& D);
    void Shortest_FLOYD(PathMatrix3 P,DistanceMatrix D);
    void DIJPath(int k,QDialog *d);
    void FLOYDPath(QDialog* d);

    void paintEvent(QPaintEvent *event);
};

#endif // GRAPH_H
