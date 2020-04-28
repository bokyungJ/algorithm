#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "sort.h"
using namespace std;

const int M = 5;
const int N = 100000;
class Queue
{
public:
	Queue();
	~Queue();
	void enqueue(int v);
	int dequeue();
	int empty();
private:
	struct node {
		int data;
		struct node *link;
	};
	struct node *front, *rear;
};
Queue::Queue()
{
	front = new node;
	rear = new node;
	front = NULL;
	rear = NULL;
}
Queue::~Queue()
{
	struct node *t = front;
	while (t != NULL) {
		front = t; t->link = t; delete front;
	}
}
void Queue::enqueue(int v)
{
	struct node *t = new node;
	t->data = v;
	t->link = NULL;
	if (front == NULL) {
		front = t;
		rear = t;
	}
	else {
		rear->link = t;
		rear = t;
	}
}
int Queue::dequeue()
{
	int x;
	struct node *t = front;
	if (front == NULL) {
		cout << "큐가 공백임." << endl;
		exit(1);
	}
	else {
		x = t->data;
		front = t->link;
		if (front == NULL) rear = NULL;
		delete t;
		return x;
	}
}
int Queue::empty()
{
	return front == NULL;
}
int digit(int d, int k)
{
	int i, temp = 1;
	for (i = 1; i < k; i++) temp *= 10;
	d /= temp;
	d %= 10;
	return d;
}
void RadixSort(int a[], int n, int m, Queue q[])
{
	int k, i, p, kd;
	for (k = 1; k <= m; k++) {
		for (i = 1; i <= n; i++) {
			kd = digit(a[i], k);
			q[kd].enqueue(a[i]);
		}
		p = 0;
		for (i = 0; i <= 9; i++)
			while (!q[i].empty())
				a[++p] = q[i].dequeue();
	}
}
int main()
{
	int i, a[N + 1];
	double start_time;
	Queue Q[10];
	srand(time(NULL));
	for (i = 1; i <= N; i++) a[i] = rand();
	start_time = clock();
	RadixSort(a, N, M, Q);
	cout << "기수 정렬의 실행 시간 (N = " << N << ") : " <<
		clock() - start_time << endl;
	CheckSort(a, N);
}