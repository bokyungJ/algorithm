#include <iostream>

using namespace std;

const int N= 8;
class Dict {
public:
	Dict() {
		z = new node(0, 0, 0);
		z->l = z;
		z->r = z;
		head = new node(0, 0, z);
	}
	void insert(int v);
	int range(int v1, int v2);
private:
	struct node {
		int key;
		struct node *l, *r;
		node(int k, struct node *ll, struct node *rr)
		{
			key = k; l = ll; r = rr;
		}
	};
	struct node *head, *z;
	int ranger(struct node *t, int v1, int v2);
};

void Dict::insert(int v) {
	struct node *p, *x;
	p = head;
	x = head->r;
	while (x != z) {
		p = x;
		if (x->key == v) return;
		x = (x->key > v) ? x->l : x->r;
	}
	x = new node(v, z, z);
	if (p->key > v) p->l = x;
	else p->r = x;
}

int Dict::range(int v1, int v2) {
	return ranger(head->r, v1, v2);
}
int Dict::ranger(struct node *t, int v1, int v2) {
	int count = 0;
	if (t == z) return 0;
	if (t->key >= v1) count += ranger(t->l, v1, v2);
	if (t->key >= v1 && t->key <= v2) count++;
	if (t->key <= v2) count += ranger(t->r, v1, v2);
	return count;
}

int main() {
	Dict d;
	int key[8] = { 2,1,7,8,6,3,5,4 };
	int i, result;

	for (i = 0; i < N; i++) d.insert(key[i]);
	result = d.range(3, 7);
	cout << "방문 노드의 개수 : " << result << endl;
}