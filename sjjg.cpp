#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<fstream>

using namespace std;

#define Max 100

typedef struct EDG{//��
	int V1, V2;//��V1ָ��V2
}*Edge;
typedef struct AdjVNode{//�ڽӵ�
	int AdjV;//�ٽӵ��±�
	AdjVNode* Next;//��һ���ڽӵ�
}*PtrToAdjVNode;
typedef struct Vnode{//��
	PtrToAdjVNode FirstEdge;//�ڽӵ��ַ
	string name;//��������
}AdjList[Max];
typedef struct GNode{//�ڽӱ���Ϣ
	int v;//������
	int e;//����
	AdjList G;//�ڽӱ�
}*PtrToGNode,*LGraph;//���ڽӱ�ʽ�洢��ͼ����
typedef struct QNode{//���нڵ�
	int data;//����ַ
	struct QNode* Next;//��һ�����нڵ��ַ
}QNode;
typedef struct Queue{//����
	QNode* Front;//ͷ
	QNode* Rear;//β
}Queue;

QNode* CreateQNode(int data);//�����µĶ��нڵ�
Queue CreateQueue(Queue& q);//�������в���ʼ��
void AddQ(Queue& q, int v);//���
int DeleteQ(Queue& q);//����
bool IsEmpty(Queue& q);//�����п�
void InsertEdge(LGraph Graph, Edge E);//�����
void DFS(LGraph G, int v);//�����������
void TopSort(LGraph Graph);//��������
LGraph CreateLGraphf();//�ļ�����ͼ
void addE(LGraph Graph);//��ӱ�
void deleteE(LGraph Graph);//ɾ����
void Output(LGraph Graph);//�洢ͼ���ļ���
void freeGraph(LGraph Graph);//�ͷŶ�̬�ڴ�

int main()
{
	LGraph Graph;//�ڽӱ�
	int operation;//����
	Graph = CreateLGraphf();
	cout << "----------��ӭ���������ݿ������ȴ�����----------" << endl;
	cout << "\t\t�����˵�\n" << "\t1:��������ĵȴ����\n" << "\t2:ɾ������ĵȴ����\n" << "\t3:��������Ƿ�����\n" <<"\t4:���޸ĺ�Ĺ�ϵͼ�洢���ļ���\n" << "\t0:�˳�����" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "������0~4����ѡ��" << endl;
	while (1)
	{
		cin >> operation;
		if (operation == 1)//�����
			addE(Graph);
		else if (operation == 2)//ɾ����
			deleteE(Graph);
		else if (operation == 3)//��·�ж�
			TopSort(Graph);
		else if (operation == 4)//�洢
			Output(Graph);
		else
			break;
		cout << "���ٴ��������0~4" << endl;
	}
	freeGraph(Graph);//�ͷŶ�̬�ڴ�
	return 0;
}

QNode* CreateQNode(int data)//�����µĶ��нڵ�
{
	QNode* pQNode = new QNode;
	if (NULL == pQNode)
	{
		cout << "����ռ�ʧ��!" << endl;
			exit(0);
	}
	pQNode->data = data;
	pQNode->Next = NULL;
	return pQNode;
}

Queue CreateQueue(Queue &q)//�������в���ʼ��
{
	q.Front = q.Rear = NULL;
	return q;
}

void AddQ(Queue& q, int v)//���
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

int DeleteQ(Queue& q)//����
{
	QNode* p;
	int da;
	p = q.Front;
	da = p->data;
	q.Front = q.Front->Next;
	delete(p);
	return da;
}

bool IsEmpty(Queue &q)//�����п�
{
	return NULL == q.Front;
}

void InsertEdge(LGraph Graph, Edge E)//�����
{
	PtrToAdjVNode NewNode;
	NewNode = new AdjVNode;
	NewNode->AdjV = E->V2;
	NewNode->Next = Graph->G[E->V1].FirstEdge;//ͷ���뷨
	Graph->G[E->V1].FirstEdge = NewNode;
	return;
}

void TopSort(LGraph Graph)//��������
{
	int Indegree[Max], cnt = 0;
	int V, i;
	PtrToAdjVNode W;
	Queue Q = CreateQueue(Q);
	for (V = 0; V < Graph->v; V++)//��ʼ��Indegree[]
		Indegree[V] = 0;
	for (V = 0; V < Graph->v; V++)//����ͼ���õ�Indegree[]
		for (W = Graph->G[V].FirstEdge; W; W = W->Next)
			Indegree[W->AdjV]++; //�������<V, W->AdjV>�ۼ��յ�����
	for (V = 0; V < Graph->v; V++)//���������Ϊ0�Ķ�������
		if (Indegree[V] == 0)
			AddQ(Q, V);
	while (!IsEmpty(Q))//��������
	{
		V = DeleteQ(Q); //����һ�����Ϊ0�Ķ���
		cnt++;
		for (W = Graph->G[V].FirstEdge; W; W = W->Next)//��V��ÿ���ڽӵ�W->AdjV
			if (--Indegree[W->AdjV] == 0)//��ɾ��Vʹ��W->AdjV���Ϊ0
				AddQ(Q, W->AdjV); //��ö�������
	}
	if (cnt != Graph->v)
	{
		cout << "ϵͳ�г���������,��������������У�\n";
		for (i = 0; i < Graph->v; i++)
			if (Indegree[i] != 0)
				cout << Graph->G[i].name << ' ';
		cout << '\n';
	}
	else
		cout << "ϵͳ��������" << endl;
	return;
}

LGraph CreateLGraphf()//�ļ�����ͼ
{
	LGraph Graph;
	EDG E;
	int i, j;
	string str1, str2;
	ifstream ifs;
	ifs.open("test.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		return NULL;
	}
	cout << "�ļ��򿪳ɹ�" << endl;
	Graph = new GNode;//����ռ�
	ifs >> Graph->v >> Graph->e;
	for (i = 0; i < Graph->v; i++)//��ֵ����ʼ��
	{
		ifs >> Graph->G[i].name;//���붥������
		Graph->G[i].FirstEdge = NULL;
	}
	for (i = 0; i < Graph->e; i++)//�����
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
	cout << "�ļ�����¼��ɹ�" << endl;
	ifs.close();
	return Graph;
}

void addE(LGraph Graph)//��ӱ�
{
	EDG E;//��
	int i, j, n, flag1, flag2;
	string str1, str2;//�������
	PtrToAdjVNode p;
	cout << "����Ҫ��������ȴ�����ĸ���" << endl;
	cin >> n;
	for (i = 0; i < n; i++)//�����
	{
		while (1)
		{
			cout << "����������" << endl;
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
				cout << "δ�ҵ��������ƣ�����������" << endl;
			else
			{
				p = Graph->G[E.V1].FirstEdge;
				while (p)
				{
					if (p->AdjV == E.V2)
					{
						cout << "�˹�ϵ�Ѵ���" << endl;
						break;
					}
					p = p->Next;
				}
				if (p == NULL)
				{
					InsertEdge(Graph, &E);
					cout << "������" << endl;
				}
				break;
			}
		}
	}
	Graph->e += n;
	return;
}

void deleteE(LGraph Graph)//ɾ����
{
	EDG E;//��
	int i, j, n, flag1, flag2, flag;
	string str1, str2;//�������
	PtrToAdjVNode p, q;
	cout << "����Ҫɾ������ȴ�����ĸ���" << endl;
	cin >> n;
	for (i = 0; i < n; i++)//�����
	{
		while (1)
		{
			cout << "����������" << endl;
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
				cout << "δ�ҵ��������ƣ�����������" << endl;
			else
			{
				if (Graph->G[E.V1].FirstEdge == NULL)
				{
					cout << "�������޵ȴ���ϵ" << endl;
					break;
				}
				else if (Graph->G[E.V1].FirstEdge->AdjV == E.V2)
				{
					p = Graph->G[E.V1].FirstEdge;
					Graph->G[E.V1].FirstEdge = Graph->G[E.V1].FirstEdge->Next;
					delete(p);
					cout << "ɾ�����" << endl;
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
							cout << "ɾ�����" << endl;
							break;
						}
					}
					if (flag == 0)
						cout << "δ�ҵ��˹�ϵ��ɾ��ʧ��" << endl;
					break;
				}
			}
		}
	}
	Graph->e -= n;
	return;
}

void Output(LGraph Graph)//¼�뵽�ļ���
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
	ofs.close();//�ر��ļ�
	cout << "ͼ�Ѵ���end.txt�ļ���" << endl;
	return;
}

void freeGraph(LGraph Graph)//��̬�ڴ��ͷ�
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