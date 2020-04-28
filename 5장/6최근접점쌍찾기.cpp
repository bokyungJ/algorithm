#include <iostream>
#include "geo_6.h"
using namespace std;

const int N = 8;
const int max = 1000;
struct node {
	struct point p;
	struct node *next;
};
struct node *z;
struct point cp1, cp2;
float min;
int pass;
int comp(struct node *t)
{
	return (pass == 1) ? t->p.x : t->p.y;
}
struct node *merge(struct node *a, struct node *b)
{
	struct node *c;
	c = z;
	do
		if (comp(a) < comp(b)) {
			c->next = a;
			c = a;
			a = a->next;
		}
		else {
			c->next = b;
			c = b;
			b = b->next;
		}
		while (c != z);
		c = z->next;
		z->next = z;
		return c;
}
void check(struct point p1, struct point p2)
{
	float dist;
	if ((p1.y != z->p.y) && (p2.y != z->p.y)) {
		dist = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
		if (dist < min) {
			min = dist;
			cp1 = p1;
			cp2 = p2;
		}
	}
}
struct node *sort(struct node *c, int N)
{
	int i;
	struct node *a, *b;
	float middle;
	struct point p1, p2, p3, p4;
	if (c->next == z) return c;
	a = c;
	for (i = 2; i <= N / 2; i++) c = c->next;
	b = c->next; c->next = z;
	if (pass == 2) middle = b->p.x;
	c = merge(sort(a, N / 2), sort(b, N - (N / 2)));
	if (pass == 2) {
		p1 = z->p; p2 = z->p; p3 = z->p; p4 = z->p;
		for (a = c; a != z; a = a->next)
			if (fabs(a->p.x - middle) < min) {
				check(a->p, p1);
				check(a->p, p2);
				check(a->p, p3);
				check(a->p, p4);
				p1 = p2; p2 = p3; p3 = p4; p4 = a->p;
			}
	}
	return c;
}
struct node *readlist()
{
	struct node *t, *p, *h;
	int i;
	h = new node;
	p = new node;
	h = p;
	for (i = 0; i < N; i++) {
		t = new node;
		t->p.x = x_value[i];
		t->p.y = y_value[i];
		t->p.c = c_value[i];
		p->next = t;
		p = p->next;
	}
	p->next = z;
	return h;
}
int main()
{
	struct node *h;
	z = new node;
	z->p.x = max;
	z->p.y = max;
	z->next = z;
	h = new node;
	h->next = readlist();
	min = max;
	pass = 1;
	h->next = sort(h->next, N);
	pass = 2;
	h->next = sort(h->next, N);
	cout << "min = " << min << ", ";
	cout << "cp1 = " << cp1.c << ", " << "cp2 = " << cp2.c << endl;
}