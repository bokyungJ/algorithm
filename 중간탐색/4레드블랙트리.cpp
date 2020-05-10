#include <iostream.h>
#include <time.h>
#include <stdlib.h>
const int black = 0;
const int red = 1;
const int N = 20000;
struct node {
	int b;
	int key;
	struct node *l, *r;
	node(int bb, int k, struct node *ll, struct node *rr)
	{
		b = bb, key = k; l = ll, r = rr;
	};
} *head, *z, *gg, *g, *p, *x;
void split(int v);
struct node *rotate(int v, struct node *y);
class Dict
{
public:
	Dict() {
		z = new node(black, 0, 0, 0);
		z->l = z; z->r = z;
		head = new node(black, 0, 0, z);
	}
	int search(int search_key);
	void insert(int v);
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
	x = head; p = head; g = head;
	while (x != z) {
		gg = g; g = p; p = x;
		if (x->key == v) return;
		x = (x->key > v) ? x->l : x->r;
		if (x->l->b && x->r->b) split(v);
	}
	x = new node(red, v, z, z);
	if (p->key > v) p->l = x;
	else p->r = x;
	split(v); head->r->b = black;
}
void split(int v)
{
	x->b = red; x->l->b = black; x->r->b = black;
	if (p->b) {
		g->b = red;
		if (g->key > v != p->key > v) p = rotate(v, g);
		x = rotate(v, gg);
		x->b = black;
	}
}
struct node *rotate(int v, struct node *y)
{
	struct node *gc, *c;
	c = (y->key > v) ? y->l : y->r;
	if (c->key > v) {
		gc = c->l; c->l = gc->r; gc->r = c;
	}
	else {
		gc = c->r; c->r = gc->l; gc->l = c;
	}
	if (y->key > v) y->l = gc;
	else y->r = gc;
	return gc;
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
	cout << "레드 블랙 트리의 실행 시간 (N = " << N << ") : " <<
		clock() - start_time << endl;
	cout << "탐색 완료." << endl;
}