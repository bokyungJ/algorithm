#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

const int N = 10000;
class Dict
{
public:
	Dict() {
		z = new node(0, 0, 0);
		z->l = z; z->r = z;
		head = new node(0, 0, z);
	}
	int search(int search_key);
	void insert(int v);
private:
	struct node {
		int key;
		struct node *l, *r;
		node(int k, struct node *ll, struct node *rr)
		{
			key = k; l = ll, r = rr;
		}
	};
	struct node *head, *z;
};
int Dict::search(int search_key)
{
	struct node *x = head->r;
	while (x != z) {
		if (x->key == search_key) return x->key;
		x = (x->key > search_key) ? x->l : x->r;
	}
	return -1;
}
void Dict::insert(int v)
{
	struct node *p, *x;
	p = head; x = head->r;
	while (x != z) {
		p = x;
		if (x->key == v) return;
		x = (x->key > v) ? x->l : x->r;
	}
	x = new node(v, z, z);
	if (p->key > v) p->l = x;
	else p->r = x;
}
void init(int key[], int search_key[])
{
	int i, index, temp[N + 1];
	for (i = 1; i <= N; i++) {
		key[i] = i;
		search_key[i] = i;
		temp[i] = 0;
	}
	srand(time(NULL));
	for (i = 1; i <= N; i++) {
		index = rand() % N + 1;
		if (temp[index] == 0)
			temp[index] = key[i];
		else {
			while (temp[index] != 0)
				index = (index % N) + 1;
			temp[index] = key[i];
		}
	}
	for (i = 1; i <= N; i++) {
		key[i] = temp[i];
	}
}
int main()
{
	Dict d;
	int i, result, key[N + 1], search_key[N + 1];
	double start_time;
	init(key, search_key);
	for (i = 1; i <= N; i++) d.insert(key[i]);
	start_time = clock();
	for (i = 1; i <= N; i++) {
		result = d.search(search_key[i]);
		if (result == -1 || result != search_key[i]) {
			cout << "탐색 오류." << endl;
		}
	}
	cout << "이진 트리 탐색의 실행 시간 (N = " << N << ") : " <<
		clock() - start_time << endl;
	cout << "탐색 완료." << endl;
}