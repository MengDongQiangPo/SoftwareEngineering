#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<fstream>

using namespace std;

#define Max 100

typedef struct EDG{//边
	int V1, V2;//从V1指向V2
}*Edge;
typedef struct AdjVNode{//邻接点
	int AdjV;//临接点下标
	AdjVNode* Next;//下一个邻接点
}*PtrToAdjVNode;
typedef struct Vnode{//点
	PtrToAdjVNode FirstEdge;//邻接点地址
	string name;//顶点数据
}AdjList[Max];
typedef struct GNode{//邻接表信息
	int v;//顶点数
	int e;//边数
	AdjList G;//邻接表
}*PtrToGNode,*LGraph;//以邻接表方式存储的图类型
typedef struct QNode{//队列节点
	int data;//结点地址
	struct QNode* Next;//下一个队列节点地址
}QNode;
typedef struct Queue{//队列
	QNode* Front;//头
	QNode* Rear;//尾
}Queue;

QNode* CreateQNode(int data);//创建新的队列节点
Queue CreateQueue(Queue& q);//创建队列并初始化
void AddQ(Queue& q, int v);//入队
int DeleteQ(Queue& q);//出队
bool IsEmpty(Queue& q);//队列判空
void InsertEdge(LGraph Graph, Edge E);//插入边
void DFS(LGraph G, int v);//深度优先搜索
void TopSort(LGraph Graph);//拓扑排序
LGraph CreateLGraphf();//文件创建图
void addE(LGraph Graph);//添加边
void deleteE(LGraph Graph);//删除边
void Output(LGraph Graph);//存储图到文件中
void freeGraph(LGraph Graph);//释放动态内存

int main()
{
	LGraph Graph;//邻接表
	int operation;//操作
	Graph = CreateLGraphf();
	cout << "----------欢迎进入检测数据库死锁等待程序----------" << endl;
	cout << "\t\t操作菜单\n" << "\t1:插入事务的等待情况\n" << "\t2:删除事务的等待情况\n" << "\t3:检测事务是否死锁\n" <<"\t4:将修改后的关系图存储到文件中\n" << "\t0:退出程序" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "请输入0~4进行选择" << endl;
	while (1)
	{
		cin >> operation;
		if (operation == 1)//插入边
			addE(Graph);
		else if (operation == 2)//删除边
			deleteE(Graph);
		else if (operation == 3)//回路判断
			TopSort(Graph);
		else if (operation == 4)//存储
			Output(Graph);
		else
			break;
		cout << "请再次输入操作0~4" << endl;
	}
	freeGraph(Graph);//释放动态内存
	return 0;
}

QNode* CreateQNode(int data)//创建新的队列节点
{
	QNode* pQNode = new QNode;
	if (NULL == pQNode)
	{
		cout << "申请空间失败!" << endl;
			exit(0);
	}
	pQNode->data = data;
	pQNode->Next = NULL;
	return pQNode;
}

Queue CreateQueue(Queue &q)//创建队列并初始化
{
	q.Front = q.Rear = NULL;
	return q;
}

void AddQ(Queue& q, int v)//入队
{
	if (NULL == q.Front)
	{
		q.Front = q.Rear = CreateQNode(v);
		return;
	}
	q.Rear->Next = CreateQNode(v);
	q.Rear = q.Rear->Next;
	return;
}

int DeleteQ(Queue& q)//出队
{
	QNode* p;
	int da;
	p = q.Front;
	da = p->data;
	q.Front = q.Front->Next;
	delete(p);
	return da;
}

bool IsEmpty(Queue &q)//队列判空
{
	return NULL == q.Front;
}

void InsertEdge(LGraph Graph, Edge E)//插入边
{
	PtrToAdjVNode NewNode;
	NewNode = new AdjVNode;
	NewNode->AdjV = E->V2;
	NewNode->Next = Graph->G[E->V1].FirstEdge;//头插入法
	Graph->G[E->V1].FirstEdge = NewNode;
	return;
}

void TopSort(LGraph Graph)//拓扑排序
{
	int Indegree[Max], cnt = 0;
	int V, i;
	PtrToAdjVNode W;
	Queue Q = CreateQueue(Q);
	for (V = 0; V < Graph->v; V++)//初始化Indegree[]
		Indegree[V] = 0;
	for (V = 0; V < Graph->v; V++)//遍历图，得到Indegree[]
		for (W = Graph->G[V].FirstEdge; W; W = W->Next)
			Indegree[W->AdjV]++; //对有向边<V, W->AdjV>累计终点的入度
	for (V = 0; V < Graph->v; V++)//将所有入度为0的顶点入列
		if (Indegree[V] == 0)
			AddQ(Q, V);
	while (!IsEmpty(Q))//拓扑排序
	{
		V = DeleteQ(Q); //弹出一个入度为0的顶点
		cnt++;
		for (W = Graph->G[V].FirstEdge; W; W = W->Next)//对V的每个邻接点W->AdjV
			if (--Indegree[W->AdjV] == 0)//若删除V使得W->AdjV入度为0
				AddQ(Q, W->AdjV); //则该顶点入列
	}
	if (cnt != Graph->v)
	{
		cout << "系统中出现了死锁,造成死锁的事务有：\n";
		for (i = 0; i < Graph->v; i++)
			if (Indegree[i] != 0)
				cout << Graph->G[i].name << ' ';
		cout << '\n';
	}
	else
		cout << "系统中无死锁" << endl;
	return;
}

LGraph CreateLGraphf()//文件创建图
{
	LGraph Graph;
	EDG E;
	int i, j;
	string str1, str2;
	ifstream ifs;
	ifs.open("test.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return NULL;
	}
	cout << "文件打开成功" << endl;
	Graph = new GNode;//申请空间
	ifs >> Graph->v >> Graph->e;
	for (i = 0; i < Graph->v; i++)//赋值并初始化
	{
		ifs >> Graph->G[i].name;//输入顶点名称
		Graph->G[i].FirstEdge = NULL;
	}
	for (i = 0; i < Graph->e; i++)//插入边
	{
		ifs >> str1 >> str2;
		for (j = 0; j < Graph->v; j++)
		{
			if (str1 == Graph->G[j].name)
				E.V1 = j;
			if (str2 == Graph->G[j].name)
				E.V2 = j;
		}
		InsertEdge(Graph, &E);
	}
	cout << "文件内容录入成功" << endl;
	ifs.close();
	return Graph;
}

void addE(LGraph Graph)//添加边
{
	EDG E;//边
	int i, j, n, flag1, flag2;
	string str1, str2;//点的名字
	PtrToAdjVNode p;
	cout << "输入要插入事务等待情况的个数" << endl;
	cin >> n;
	for (i = 0; i < n; i++)//插入边
	{
		while (1)
		{
			cout << "输入两事务" << endl;
			cin >> str1 >> str2;
			flag1 = flag2 = 0;
			for (j = 0; j < Graph->v; j++)
			{
				if (str1 == Graph->G[j].name)
				{
					E.V1 = j;
					flag1 = 1;
				}
				if (str2 == Graph->G[j].name)
				{
					E.V2 = j;
					flag2 = 1;
				}
			}
			if (flag1 == 0 || flag2 == 0)
				cout << "未找到事务名称，请重新输入" << endl;
			else
			{
				p = Graph->G[E.V1].FirstEdge;
				while (p)
				{
					if (p->AdjV == E.V2)
					{
						cout << "此关系已存在" << endl;
						break;
					}
					p = p->Next;
				}
				if (p == NULL)
				{
					InsertEdge(Graph, &E);
					cout << "添加完毕" << endl;
				}
				break;
			}
		}
	}
	Graph->e += n;
	return;
}

void deleteE(LGraph Graph)//删除边
{
	EDG E;//边
	int i, j, n, flag1, flag2, flag;
	string str1, str2;//点的名字
	PtrToAdjVNode p, q;
	cout << "输入要删除事务等待情况的个数" << endl;
	cin >> n;
	for (i = 0; i < n; i++)//插入边
	{
		while (1)
		{
			cout << "输入两事务" << endl;
			cin >> str1 >> str2;
			flag1 = flag2 = 0;
			for (j = 0; j < Graph->v; j++)
			{
				if (str1 == Graph->G[j].name)
				{
					E.V1 = j;
					flag1 = 1;
				}
				if (str2 == Graph->G[j].name)
				{
					E.V2 = j;
					flag2 = 1;
				}
			}
			if (flag1 == 0 || flag2 == 0)
				cout << "未找到事务名称，请重新输入" << endl;
			else
			{
				if (Graph->G[E.V1].FirstEdge == NULL)
				{
					cout << "此事务无等待关系" << endl;
					break;
				}
				else if (Graph->G[E.V1].FirstEdge->AdjV == E.V2)
				{
					p = Graph->G[E.V1].FirstEdge;
					Graph->G[E.V1].FirstEdge = Graph->G[E.V1].FirstEdge->Next;
					delete(p);
					cout << "删除完毕" << endl;
					break;
				}
				else
				{
					p = Graph->G[E.V1].FirstEdge;
					q = p->Next;
					flag = 0;
					while (q != NULL)
					{
						if (q->AdjV = E.V2)
						{
							flag = 1;
							p = p->Next;
							delete(q);
							cout << "删除完毕" << endl;
							break;
						}
					}
					if (flag == 0)
						cout << "未找到此关系，删除失败" << endl;
					break;
				}
			}
		}
	}
	Graph->e -= n;
	return;
}

void Output(LGraph Graph)//录入到文件中
{
	ofstream ofs;
	int i;
	PtrToAdjVNode W;
	ofs.open("end.txt", ios::trunc);
	cout.setf(ios::left);
	ofs << Graph->v << ' ' << Graph->e << endl;
	for (i = 0; i < Graph->v - 1; i++)
		ofs << Graph->G[i].name << ' ';
	ofs << Graph->G[i].name << endl;
	for (i = 0; i < Graph->v; i++)
	{
		W = Graph->G[i].FirstEdge;
		while (W)
		{
			ofs << Graph->G[i].name << ' ' << Graph->G[W->AdjV].name << endl;
			W = W->Next;
		}
	}
	ofs.close();//关闭文件
	cout << "图已存入end.txt文件中" << endl;
	return;
}

void freeGraph(LGraph Graph)//动态内存释放
{
	PtrToAdjVNode W, Q;
	int i;
	for (i = 0; i < Graph->v; i++)
	{
		W = Graph->G[i].FirstEdge;
		while (W)
		{
			Q = W->Next;
			delete(W);
			W = Q;
		}
	}
	delete(Graph);
	return;
}