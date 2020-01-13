#include "graph.h"
#include<iostream>
#include<iomanip>
#include<QObject>
#include<windows.h>
//#include<QString>
using namespace std;

Graph::Graph()
{

}


Graph::~Graph()
{

}

int Graph::LocateVex(char u)
{
    //若图G中存在顶点u，返回该顶点在图中位置，否则返回 - 1
    int i;
    for (i = 0; i < vexnum; i++)//对所有顶点依次查找
    {
        if (u == vexs[i])
            return i;
    }
    return ERROR; //图G中不存在与u有相同名称的顶点
}

void Graph::CreateGraph(int vex,int arc,struct arc arcinfo[])
{
    vexnum = vex;
    arcnum = arc;

    vexnumber=vex;


    //构造无向网
    int i, j, k;
    int w;//顶点关系类型
    char v1, v2;//顶点
                      //构造顶点向量,输入名称
    ArcNode* p;

    //输入顶点
    for (i = 0; i <vexnum; i++)
    {
        vexs[i]=char('A'+i);
        firstarc[i] = nullptr;
    }

    //初始化二维邻接矩阵
    for (i = 0; i < vexnum; i++)
        for (j = 0; j < vexnum; j++)
            MGraph[i][j]= INF;

    for (k = 0; k <arcnum; k++)
    {
        v1=arcinfo[k].a;
        v2=arcinfo[k].b;
        w=arcinfo[k].weight;
        i = LocateVex( v1);
        j = LocateVex( v2);
        MGraph[i][j] = w;//无向图
        MGraph[j][i] = w;

        p = new ArcNode;
        p->adjvex = j;
        p->weight = w;
        p->nextarc = firstarc[i];
        firstarc[i] = p;

        p = new ArcNode;
        p->adjvex = i;
        p->weight = w;
        p->nextarc = firstarc[j];
        firstarc[j] = p;

    }
}

void Graph::CreateGraphDefault()//default
{
    vexnum = 8;
    arcnum = 10;

    vexnumber=8;


    //构造无向网
    int i, j, k;
    int w;//顶点关系类型
    char v1, v2;//顶点
                      //构造顶点向量,输入名称
    ArcNode* p;

    //输入顶点
    for (i = 0; i <vexnum; i++)
    {
        vexs[i]=char(65+i);
        firstarc[i] = nullptr;
    }

    //初始化二维邻接矩阵
    for (i = 0; i < vexnum; i++)
        for (j = 0; j < vexnum; j++)
            MGraph[i][j]= INF;

    arc* sides=new arc[arcnum];
    sides[0]={'A','B',3};
    sides[1]={'A','C',5};
    sides[2]={'A','E',8};
    sides[3]={'A','H',1};
    sides[4]={'B','C',6};
    sides[5]={'B','D',7};
    sides[6]={'D','H',5};
    sides[7]={'E','F',10};
    sides[8]={'E','G',15};
    sides[9]={'A','G',8};

    for (k = 0; k <arcnum; k++)
    {
        v1=sides[k].a;
        v2=sides[k].b;
        w=sides[k].weight;
        i = LocateVex( v1);
        j = LocateVex( v2);
        MGraph[i][j] = w;//无向图
        MGraph[j][i] = w;

        p = new ArcNode;
        p->adjvex = j;
        p->weight = w;
        p->nextarc = firstarc[i];
        firstarc[i] = p;

        p = new ArcNode;
        p->adjvex = i;
        p->weight = w;
        p->nextarc = firstarc[j];
        firstarc[j] = p;

    }
    delete [] sides;
}


void Graph::ShowLinkList(QDialog* d)
{
    d->setWindowTitle("LinkList");
    int i;
    ArcNode* p;
    QLabel *ListLabel[MAX_VERTEX_NUM];
    QLabel *LabelTask1=new QLabel(d);
    LabelTask1->setText("1.Show LinkList");
    LabelTask1->setGeometry(50,20,600,50);
    LabelTask1->show();

    for (i = 0; i < vexnum; i++)
    {
        ListLabel[i]=new QLabel(d);
        QString ListString;
        ListString+="[";
        ListString+=QString(vexs[i]);
        ListString+="]";
        ListString+=" --> ";
        p = firstarc[i];
        while (p)
        {
            ListString+="[";
            ListString+=QString(vexs[p->adjvex]);
            ListString+="][";
            ListString+=QString::number(p->weight);
            ListString+="]-->";
            p = p->nextarc;
        }
        ListString+=" NULL ";

        ListLabel[i]->setText(ListString);
        ListLabel[i]->setGeometry(50,100+i*50,1800,50);
        ListLabel[i]->show();
    }

}

void Graph::DisplayUDN( )
{
    //输出无向网
    int i, j;
    for (i = 0; i < vexnum; i++)
        cout << vexs[i] << ' ';
    cout << endl;

    for (i = 0; i < vexnum; i++)
    {
        for (j = 0; j < vexnum; j++)
            cout <<
            setw(4) << MGraph[i][j];
        cout << endl;
    }

    ArcNode* p;
    for (i = 0; i < vexnum; i++)
    {
        cout << vexs[i] << "-->";
        p = firstarc[i];
        while (p)
        {
            cout << vexs[p->adjvex] << "," << p->weight << " ";
            p = p->nextarc;
        }
        cout << endl;
    }

}


int Graph::minimum(miniside SZ)
{
    //求SZ.lowcost的最小正值，并返回其在SZ中的序号
    int i = 0, j, k, min;
    while (!SZ[i].lowcost)//找到第一个值不为0的
        i++;
    min = SZ[i].lowcost;//min标记第一个不为0的值
    k = i;
    for(j=i+1;j<vexnum;j++)
        if (SZ[j].lowcost > 0 && SZ[j].lowcost < min)//找到新的更小的正值
        {
            min = SZ[j].lowcost;//min标记此正值
            k = j;
        }
    return k;
}

void Graph::Prim(char u)
{//Prim算法从顶点u出发构造最小生成树，输出树的各条边

    int i, j, k;
    miniside closedge;
    k = LocateVex(u);//顶点u的序号
    for (j = 0; j < vexnum; j++)//辅助数组初始化
    {
        closedge[j].adjvex = k;
        closedge[j].lowcost = MGraph[k][j];//顶点u到该点的权值
    }
    closedge[k].lowcost = 0;

    //cout << "最小生成树各条边为" << endl;

    for (i = 1; i < vexnum; i++)
    {
        k = minimum(closedge);//求出最小生成树的下一个结点
        PrimResults[i][0]=closedge[k].adjvex;
        PrimResults[i][1]=k;
      //  cout << vexs[closedge[k].adjvex] << "-" << vexs[k]<<" ";//输出最小生成树的边
        closedge[k].lowcost = 0;//第k顶点并入u集
        for(j=0;j<vexnum;j++)
            if (MGraph[k][j] < closedge[j].lowcost)
            {
                closedge[j].adjvex = k;
                closedge[j].lowcost = MGraph[k][j];
            }
    }
}


void Graph::Kruskal()
{
    //Kruskal算法求最小生成树
    int set[MAX_VERTEX_NUM], senumber = 0, sb, i, j, k;
    side se[MAX_VERTEX_NUM * (MAX_VERTEX_NUM - 1) / 2];//存储边信息的一维数组
    for(i=0;i<vexnum;i++)//查找所有的边，并根据权值升序插入到se中
        for(int j=i+1;j<vexnum;j++)//无向网，只在上三角查找
            if (MGraph[i][j] <INF)//有边
            {
                k = senumber - 1;//k指向se的最后一条边
                while (k >= 0)//k仍指向se的边
                    if (se[k].weight > MGraph[i][j])
                    {
                        //k所指的边权值大于刚才找到的边
                        se[k + 1] = se[k];//k所指的边向后移
                        k--;//k指向前一条边
                    }
                    else//k所指的边的权值不大于刚才找到的权值
                        break;
                se[k + 1].a = i;
                se[k + 1].b = j;
                se[k + 1].weight = MGraph[i][j];
                senumber++;//se的边数++
            }
    //cout << se[i].a << " " << se[i].b << " " << se[i].weight << endl;

   // for(i=0;i<senumber;i++)
   //     cout<<i<<" " << se[i].a << " " << se[i].b << " " << se[i].weight << endl;

    for (i = 0; i < vexnum; i++)
        set[i] = i;
   // cout << "最小生成树的各条边为\n";
    j = 0;//j指示se当前要并入的最小生成树的边序号
    k = 0;//k指示当前最小生成树的边数
    while (k < vexnum - 1)
    {
        if (set[se[j].a] != set[se[j].b])//j所指边的两个顶点不属于同一集合
        {
            KruskalResults[k][0]=se[j].a;
            KruskalResults[k][1]=se[j].b;
            //cout << vexs[se[j].a] << "--" << vexs[se[j].b] << endl;
            sb = set[se[j].b];//将该边的顶点se[j].b当前所在的集合赋给sb
            for (i = 0; i < vexnum; i++)//对所有顶点
                if (set[i] == sb)//与se[j].b在同一个集合之中
                    set[i] = set[se[j].a];//将此顶点并入顶点se[j].a所在的集合中
            k++;//当前构成的最小生成树的边数+1
        }
        j++;//j指示se下一条边要并入最小生成树的边的序号
    }

}

void Graph::MakePath(bool P[],int i,int j,QString& str)
{//求由图G的起点i到终点j最短路径沿途所经过的点
    int k, MinNum, begin = i;//起点序号赋给begin
    int Min;//存[begin]到可能经过的顶点之间的最短路径
    P[i]=false;
    while (begin != j)//当前起点还不是终点
    {
        Min = INF;
        for(k=0;k<vexnum;k++)//查找顶点[begin]的所有邻接顶点
            if (MGraph[begin][k] < Min && P[k])
            {
                //begin到k有较短的直接通路，且k在i到j的最短路径上
                Min = MGraph[begin][k];
                MinNum = k;
            }
        if (Min == INF)//起点[i]到[j]之间没有通路
            break;

        str+=vexs[MinNum];
        //cout << vexs[MinNum];//输出最短路径的顶点

        if (MinNum != j)//MinNum不是终
            str=str+"->";
        P[MinNum] = false;//缩短路径
        begin = MinNum;//经过的顶点序号赋给begin,作为当前的起点继续查找

    }
    //cout << endl;

}

void Graph::MakePath2(bool P[], int i, int j, QString &str)
{
    //求由图G的起点i到终点j最短路径沿途所经过的点
        int k, MinNum, begin = i;//起点序号赋给begin
        int Min;//存[begin]到可能经过的顶点之间的最短路径
        P[i]=false;
        while (begin != j)//当前起点还不是终点
        {
            Min = INF;
            for(k=0;k<vexnum;k++)//查找顶点[begin]的所有邻接顶点
                if (MGraph[begin][k] < Min && P[k])
                {
                    //begin到k有较短的直接通路，且k在i到j的最短路径上
                    Min = MGraph[begin][k];
                    MinNum = k;
                }
            if (Min == INF)//起点[i]到[j]之间没有通路
                break;

            str+=vexs[MinNum];
            //cout << vexs[MinNum];//输出最短路径的顶点

            if (MinNum != j)//MinNum不是终
                str=str+"->";
            P[MinNum] = false;//缩短路径
            begin = MinNum;//经过的顶点序号赋给begin,作为当前的起点继续查找

        }
}

void Graph::Shortest_DIJ(int v0, PathMatrix2& P, ShortPathTable& D)
{//迪杰斯特拉算法求v0到其余各顶点的最短路径P[v]以及带权长度D[v]
    //若P[v][w]==true,w是从v0到v当前求得最短路径上的顶点
    //final[v]==true,当且仅当v属于S，即已求得从v0到v的最短路径
    int v, w, i, j;
    int min;
    bool final[MAX_VERTEX_NUM];//辅助矩阵，为真表示该顶点到v0的最短距离已求出，初值为假
    for (v = 0; v < vexnum; ++v)
    {
        final[v] = false;
        D[v] = MGraph[v0][v];//D[]存放v0到v的最短距离，初值为直接距离
        for (w = 0; w < vexnum; ++w)
            P[v][w] = false;//设P[v][w]初值为false,没有路径
        if (D[v] < INF)//v0到v有直接路径
        {P[v][v0] = true;P[v][v] = true;}
    }
    D[v0] = 0;
    final[v0] = true;//v0并入S集
    for (i = 1; i < vexnum; ++i)//对其余vexnum-1个点
    {
        //开始主循环，每次求得从v0到v的最短路径，将v并入S集
        min = INF;
        for(w=0;w<vexnum;++w)//对所有顶点检查
            if (!final[w] && D[w] < min)
            {
                v = w;
                min = D[w];
            }
        final[v] = true;
        for(w=0;w<vexnum;w++)
            if (!final[w] && min < INF && MGraph[v][w] < INF && (min + MGraph[v][w] < D[w]))
            //if (!final[w] &&   (min + MGraph[v][w] < D[w]))
            {
                //
                D[w] = min + MGraph[v][w];//更新
                for (j = 0; j < vexnum; j++)
                    //修改P[w],
                    P[w][j] = P[v][j];
                P[w][w] = true;
            }

    }
}


void Graph::Shortest_FLOYD(PathMatrix3 P, DistanceMatrix D)
{
    //用Floyd算法求图中各对顶点v和w之间的最短路径P[v][w][]及其带权长度D[v][w]
    //P[v][w][u]==true,则u是从v到w当前求得最短路径上的顶点
    int u, v, w, i;
    for(v=0;v<vexnum;v++)//对各对顶点之间已知初始路径和距离
        for (w = 0; w < vexnum; w++)
        {
            D[v][w] = MGraph[v][w];//顶点v到w的直接距离
            for (u = 0; u < vexnum; u++)
                P[v][w][u] = false;
            if (D[v][w] < INF)//有直接路径
                P[v][w][v] = P[v][w][w] = true;//由v到w的路径经过v和w两点
        }
    for(u=0;u<vexnum;u++)
        for(v=0;v<vexnum;v++)
            for(w=0;w<vexnum;w++)
                if (u != v && u != w && v != w && D[v][u] < INF && D[u][w] < INF && D[v][u] + D[u][w] < D[v][w])
                {
                    //从v经过u到w的一条路径更短
                    D[v][w] = D[v][u] + D[u][w];//更新最短距离
                    for (i = 0; i < vexnum; i++)
                        P[v][w][i] = P[v][u][i] || P[u][w][i];
                        //从v到w的路径经过从v到u和从u到w的所有路径
                }
}

void Graph::DIJPath(int k,QDialog*d5)
{
    int i, j;
    PathMatrix2 p;
    ShortPathTable d;
    bool* path;

    path = new bool[vexnum];
    Shortest_DIJ(k, p, d);
    //最短路径数组p[i][j]
    //for(i=0;i<vexnum;i++)
    //{
    //    for(j=0;j<vexnum;j++)
    //        cout<<p[i][j]<<" ";
    //    cout<<endl;

    //}

    QLabel* labelDIJ[MAX_VERTEX_NUM];

    //最短路径经过的顶点
    for (i = 0; i < vexnum; i++)
    {
        QString str;
        if (i != k && d[i] < INF)
        {
            str+=vexs[k];
            str+="->";
            str+=vexs[i];
            str+=" ";
            QString temp=QString::number(d[i]);
            str+=temp;
            str+=" ";

            str+=vexs[k];
            str+="->";
            //cout << vexs[k] << vexs[i] << d[i];
            //cout << vexs[k];
            for (j = 0; j < vexnum; j++)
                path[j] = p[i][j];
            MakePath(path, k, i,str);
        }
        labelDIJ[i]=new QLabel(d5);
        labelDIJ[i]->setText(str);
        labelDIJ[i]->setGeometry(50,100+i*50,1000,50);
        labelDIJ[i]->show();
    }
    delete[]path;
}

void Graph::FLOYDPath(QDialog*d6)
{
    QLabel* labelFloyd[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int i, j;
    bool* path;
    int k = 0;//源点的序号
    path = new bool[vexnum];
    //各对顶点之间的最短路径
    PathMatrix3 p;
    DistanceMatrix d;
    for (i = 0; i < vexnum; i++)
        MGraph[i][i] = 0;//FLOYD算法要求对角线元素为0
    Shortest_FLOYD(p, d);


    for (i = 0; i < vexnum; i++)
    {
        for (j = 0; j < vexnum; j++)
        {
            QString str;

            if (i != j)
            {
                str+=vexs[i];
                str+="->";
                str+=vexs[j];
                str+=" Distance:";
                str+=QString::number(d[i][j]);
                str+=" Past ";
                //cout << vexs[i] << "->" << vexs[j];
                for (k = 0; k < vexnum; k++)
                {
                //    cout << p[i][j][k];
                    path[k] = p[i][j][k];
                }

                MakePath2(path, i, j,str);
            }
            labelFloyd[i][j]=new QLabel(d6);
            labelFloyd[i][j]->setText(str);
            labelFloyd[i][j]->setGeometry(50,100+j*40+i*vexnum*40,1000,40);
            labelFloyd[i][j]->show();

        }
    }

    delete []path;
}

