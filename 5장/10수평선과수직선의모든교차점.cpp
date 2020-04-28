#include <iostream>
#include "geo_1.h"
using namespace std;

const int Nmax = 10;
struct line lines[Nmax];
int count = 0;

class Dict {
public:
	Dict() {
		z = new node(0, 0, 0, 0);
		z->l = z; z->r = z;
		head = new node(0, 0, 0, z);
	}
	void insert(int v, int info);
	void remove(int v);
	int range(int v1, int v2);
	void traverse();
private:
	struct node {
		int key;
		int info;
		struct node *l, *r;
		node(int k, int i, struct node *ll, struct node *rr) {
			key = k; info = i; l = ll; r = rr;
		}
	};
	struct node *head, *z;
	int ranger(struct node *t, int v1, int v2);
	void inorder(struct node *t);
	void visit(int v, int info);
};

Dict Xtree, Ytree;

void Dict::insert(int v, int info) {
	struct node *p, *x;
	p = head; x = head->r;
	while (x != z) {
		p = x;
		if (x->key == v) return;
		x = (x->key > v) ? x->l : x->r;
	}
	x = new node(v, info, z, z);
	if (p->key > v) p->l = x;
	else p->r = x;
}

void Dict::remove(int v) {
	struct node *c, *p, *x, *t;
	z->key = v;
	p = head; x = head->r;
	while (v != x->key) {
		p = x;
		x = (v < x->key) ? x->l : x->r;
	}
	t = x;
	if (t->r == z)x = x->l;
	else if (t->r->l == z) {
		x = x->r; x->l = t->l;
	}
	else {
		c = x->r;
		while (c->l->l != z) c = c->l;
		x = c->l; c->l = x->r;
		x->l = t->l; x->r = t->r;
	}
	delete t;
	if (v < p->key) p->l = x;
	else p->r = x;
}
int Dict::range(int v1, int v2) {
	return ranger(head->r, v1, v2);
}
int Dict::ranger(struct node *t, int v1, int v2) {
	int count = 0;
	if (t == z) return 0;
	if (t->key >= v1) count += ranger(t->l, v1, v2);
	if (t->key >= v1&&t->key <= v2) count++;
	if (t->key <= v2)count += ranger(t->r, v1, v2);
	return count;
}

void Dict::traverse() {
	inorder(head->r);
}

void Dict::inorder(struct node *t) {
	if (t != z) {
		inorder(t->l);
		visit(t->key, t->info);
		inorder(t->r);
	}
}

void Dict::visit(int v, int info) {
	int t, x1, y1, x2, y2;
	x1 = lines[info].p1.x; y1 = lines[info].p1.y;
	x2 = lines[info].p2.x; y2 = lines[info].p2.y;
	if (x2 < x1) { t = x2; x2 = x1; x1 = t; }
	if (y2 < y1) { t = y2; y2 = y1; y1 = t; }
	if (v == y1) {
		Xtree.insert(x1, info);
	}
	if (v == y2) {
		Xtree.remove(x1);
		count += Xtree.range(x1, x2);
	}
}

int intersections() {
	int y1, y2, N;
	for (N = 1; N < Nmax; N++) {
		y1 = lines[N].p1.y;
		y2 = lines[N].p2.y;
		Ytree.insert(y1, N);
		if (y2 != y1) Ytree.insert(y2, N);
	}
	Ytree.traverse();
	return count;
}

void init(int x1, int y1, int x2, int y2, int N) {
	lines[N].p1.x = x1;
	lines[N].p1.y = y1;
	lines[N].p2.x = x2;
	lines[N].p2.y = y2;
}

int main() {
	int result;

	init(12, 7, 12, 16, 1);
	init(2, 9, 15, 9, 2);
	init(8, 4, 16, 4, 3);
	init(1, 3, 1, 14, 4);
	init(11, 2, 11, 11, 5);
	init(3, 1, 3, 12, 6);
	init(9, 6, 9, 8, 7);
	init(5, 5, 5, 15, 8);
	init(7, 13, 13, 13, 9);
	result = intersections();
	cout << "모든교차점의 개수 : " << result << endl;
}