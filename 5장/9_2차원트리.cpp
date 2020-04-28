#include <iostream>
#include "geo_1.h"
using namespace std;

const int N = 16;

struct rect { int x1, y1, x2, y2; };

int insiderect(struct point p, struct rect range) {
	return (p.x >= range.x1&&p.x <= range.x2) && (p.y >= range.y1&&p.y <= range.y2);
}

class Range {
public:
	Range();
	void insert(struct point P);
	int search(rect range);
private:
	struct node { 
		struct point p; struct node *l,*r;
		node(struct point pp, struct node *ll, struct node *rr)
		{
			p = pp; l = ll; r = rr;
		}
	};
	struct node *head,*z;
	struct point dummy;
	int searchr(struct node *t, struct rect range, int d);
};

Range::Range() {
	dummy.x = 0; dummy.y = 0;
	z = new node(dummy, 0, 0);
	z->l = z; z->r = z;
	head = new node(dummy, 0, z);
}

void Range::insert(struct point p) {
	struct node *f_f, *t;
	int d, td;
	for (d = 1, t = head; t != z; d = !d) {
		td = d ? (p.x < t->p.x) : (p.y < t->p.y);
		f_f = t; t = td ? t->l : t->r;
	}
	t = new node(dummy, 0, 0);
	t->p = p; t->l = z; t->r = z;
	if (td) f_f->l = t;
	else f_f->r = t;
}

int Range::search(struct rect range) {
	return searchr(head->r, range, 0);
}

int Range::searchr(struct node *t, struct rect range, int d) {
	int t1, t2, tx1, tx2, ty1, ty2, count = 0;
	if (t == z) return 0;
	tx1 = range.x1 < t->p.x;
	tx2 = t->p.x <= range.x2;
	ty1 = range.y1 < t->p.y;
	ty2 = t->p.y <= range.y2;
	t1 = d ? tx1 : ty1;
	t2 = d ? tx2 : ty2;
	if (t1)count += searchr(t->l, range, !d);
	if (insiderect(t->p, range)) count++;
	if (t2)count += searchr(t->r, range, !d);
	return count;
}

int main() {
	Range r;
	struct point p[N + 1];
	struct rect range;
	int i, result;

	for (i = 1; i <= N; i++) {
		p[i].x = x_value[i - 1];
		p[i].y = y_value[i - 1];
		p[i].c = c_value[i - 1];
	}

	for (i = 1; i <= N; i++) r.insert(p[i]);
	range.x1 = 7; range.y1 = 10; range.x2 = 11; range.y2 = 16;
	result = r.search(range);
	cout << "범위 내에 있는 점의 개수 : " << result << endl;
}
