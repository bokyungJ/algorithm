#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int maxb = 5;
const int N = 7;

class bitskey
{
private:
	int x;
public:
	int get() { return x; }
	bitskey& operator=(int i) { x = i; return *this; }
	unsigned bits(int k, int j) {
		return (x >> k) & ~(~0 << j);
	}
};
struct node {
	bitskey key;
	struct node* l;
	struct node* r;
	bool external; // true : 외부 노드, false : 내부 노드
	node(bitskey v) {
		if (v.get() == 0) {
			key = 0;
			external = false;
		}
		else {
			key = v;
			external = true;
		}
		l = r = 0;
	}
};

class Dict {
private:
	struct node* head;
	bool head_check;
	bitskey itemMin;
	node* insertR(node* h, bitskey v, int d);
	node* split(node* p, node* q, int d);
	bitskey searchR(node* h, bitskey v, int d);
	void checkR(node* h, bitskey v, int d);
public:
	Dict() { head = 0; head_check = false; itemMin = 0; }
	void insert(bitskey v) { insertR(head, v, maxb - 1); }
	bitskey search(bitskey v) { return searchR(head, v, maxb - 1); }
	void check(bitskey v) {
		cout << v.get() << " ";
		checkR(head, v, maxb - 1);
	}
};

node* Dict::insertR(node* h, bitskey v, int d)
{
	if (h == 0) {
		h = new node(v);
		if (!head_check) head = h;
		return h;
	}
	if (h->external) {
		node* leaf = new node(v);
		h = split(leaf, h, d);
		if (!head_check) {
			head = h;
			head_check = true;
		}
		return h;
	}
	if (v.bits(d, 1) == 0)
		h->l = insertR(h->l, v, d - 1);
	else h->r = insertR(h->r, v, d - 1);
	return h;
}

node* Dict::split(node* p, node* q, int d)
{
	node* t = new node(itemMin);
	switch ((p->key.bits(d, 1)) * 2 + (q->key.bits(d, 1))) {
	case 0: t->l = split(p, q, d - 1); break;
	case 1: t->l = p; t->r = q; break;
	case 2: t->r = p; t->l = q; break;
	case 3: t->r = split(p, q, d - 1); break;
	}
	return t;
}

bitskey Dict::searchR(node* h, bitskey v, int d)
{
	if (h == 0) return itemMin;
	if (h->external) {
		if (v.get() == h->key.get()) return v;
		return v = -1; // 탐색 실패
		return v = -1; // 탐색 실패
	}
	else {
		if (v.bits(d, 1) == 0) return searchR(h->l, v, d - 1);
		else return searchR(h->r, v, d - 1);
	}
}

void Dict::checkR(node* h, bitskey v, int d)
{
	if (h == 0) return;
	if (h->external) {
		if (v.get() == h->key.get()) {
			cout << endl;
			return;
		}
		return;//v = -1; // 탐색 실패
		return;//v = -1; // 탐색 실패
	}
	else {
		if (v.bits(d, 1) == 0) {
			cout << "left ";
			return checkR(h->l, v, d - 1);
		}

		else {
			cout << "right ";
			return checkR(h->r, v, d - 1);
		}
	}
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
	int i;
	double start_time;
	int key[N + 1] = { 0, 1, 19, 5, 18, 3, 26, 9 };
	int search_key[N + 1] = { 0, 1, 3, 5, 9, 18, 19, 26 };
	// init(key, search_key);
	
	cout << "[";
	for (int n = 1; n <= N; n++) {
		if (n != N)
			cout << key[n] << ", ";
		else cout << key[n] << "]";
	}

	for (i = 1; i <= N; i++) {
		bitskey tmp;
		tmp = key[i];
		d.insert(tmp);
	}
	cout << "[";
	for (int i = 1; i < N; i++)
		cout << key[i] << ", ";
	cout << key[N] << "]" << endl;
	start_time = clock();
	for (i = 1; i <= N; i++) {
		bitskey search_tmp;
		search_tmp = search_key[i];
		d.search(search_tmp);
		d.check(search_tmp);
	}
	cout << "Search completed." << endl;
	return 0;
}