#include <iostream>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <ctime>
#define pow2(n) (1 << (n))
using namespace std;

const int N = 9;

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
	Node(int data, struct Node* ll, struct Node* rr) {
		this->data = data, left = ll; right = rr;
	}
	//}*r, *zero_node, *head;
	//} *head, *zero_node, *gg, *g, *p, *x;
} *r, *head, *zero_node, *gg, *g, *p, *x;
class AVL_Tree {
public:
	int height(Node*);
	int difference(Node*);
	Node* rr_rotat(Node*);
	Node* ll_rotat(Node*);
	Node* lr_rotat(Node*);
	Node* rl_rotat(Node*);
	Node* balance(Node*);
	int search(int);
	void insert(int);
	void show(Node*, int);
	void inorder(Node*);
	void preorder(Node*);
	void postorder(Node*);
	void check(int key[]);
	AVL_Tree() {
		//r = NULL;
		zero_node = new Node(0, 0, 0);
		zero_node->left = zero_node; zero_node->right = zero_node;
		head = new Node(0, 0, zero_node);
	}
};
int AVL_Tree::height(Node* t) {
	int h = 0;
	if (t != zero_node) {
		int l_height = height(t->left);
		int r_height = height(t->right);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}
int AVL_Tree::difference(Node* t) {
	int l_height = height(t->left);
	int r_height = height(t->right);
	int b_factor = l_height - r_height;
	return b_factor;
}
Node* AVL_Tree::rr_rotat(Node* parent) {
	Node* t;
	t = parent->right;
	parent->right = t->left;
	t->left = parent;
	cout << "Right-Right Rotation";
	return t;
}
Node* AVL_Tree::ll_rotat(Node* parent) {
	Node* t;
	t = parent->left;
	parent->left = t->right;
	t->right = parent;
	cout << "Left-Left Rotation";
	return t;
}
Node* AVL_Tree::lr_rotat(Node* parent) {
	Node* t;
	t = parent->left;
	parent->left = rr_rotat(t);
	cout << "Left-Right Rotation";
	return ll_rotat(parent);
}
Node* AVL_Tree::rl_rotat(Node* parent) {
	Node* t;
	t = parent->right;
	parent->right = ll_rotat(t);
	cout << "Right-Left Rotation";
	return rr_rotat(parent);
}
Node* AVL_Tree::balance(Node* t) {
	int bal_factor = difference(t);
	if (bal_factor > 1) {
		if (difference(t->left) > 0)
			t = ll_rotat(t);
		else
			t = lr_rotat(t);
	}
	else if (bal_factor < -1) {
		if (difference(t->right) > 0)
			t = rl_rotat(t);
		else
			t = rr_rotat(t);
	}
	return t;
}

int AVL_Tree::search(int search_key) {
	struct Node* x = head->right;
	/*
	if (r == NULL) {
	r = new Node;
	r->data = v;
	r->left = NULL;
	r->right = NULL;
	return r;
	}
	*/
	while (x != zero_node) {
		if (x->data == search_key) return x->data;
		x = (x->data > search_key) ? x->left : x->right;
	}
}

void AVL_Tree::insert(int v) {
	x = head;
	p = head;
	g = head;
	while (x != zero_node) {
		gg = g; g = p; p = x;
		if (x->data == v) return;
		x = (x->data > v) ? x->left : x->right;
	}
	x = new Node(v, zero_node, zero_node);
	if (p->data > v) p->left = x;
	else p->right = x;
	x = balance(x);
}

int AVL_Tree::search(int search_key) {
	struct Node* x = head->right;
	while (x != zero_node) {
		if (x->data == search_key) return x->data;
		x = (x->data > search_key) ? x->left : x->right;
	}
}

void AVL_Tree::check(int key[]) {
	for (int i = 1; i <= N; i++) {
		struct Node* x = head->right;
		int temp_key = x->data; // initialized with head's key
		int find = 0;
		while (x != zero_node) {
			if (x->data == key[i]) {
				find = x->data;
				break;
			}
			else {
				temp_key = x->data;
				x = (x->data > key[i]) ? x->left : x->right;
			}
		}
		
		cout << "key : " << key[i];
		cout << ", parents : " << temp_key << endl;
	}
}

void init(int key[], int search_key[]){
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

void init_right(int key[], int search_key[]){
	int i, index;
	for (i = 1; i <= N; i++) {
		key[i] = i;
		search_key[i] = i;
	}
}

void init_reverse(int key[], int search_key[]){
	int i, index;
	for (i = N; i >= 1; i--) {
		key[i] = i;
		search_key[i] = i;
	}
}

void AVL_Tree::show(Node* p, int l) {
	int i;
	if (p != NULL) {
		show(p->right, l + 1);
		cout << " ";
		if (p == r)
			cout << "Root -> ";
		for (i = 0; i < l && p != r; i++)
			cout << " ";
		cout << p->data;
		show(p->left, l + 1);
	}
}

void AVL_Tree::inorder(Node* t) {
	if (t == NULL)
		return;
	inorder(t->left);
	cout << t->data << " ";
	inorder(t->right);
}
void AVL_Tree::preorder(Node* t) {
	if (t == NULL)
		return;
	cout << t->data << " ";
	preorder(t->left);
	preorder(t->right);
}
void AVL_Tree::postorder(Node* t) {
	if (t == NULL)
		return;
	postorder(t->left);
	postorder(t->right);
	cout << t->data << " ";
}
		/* main for testing normal size of N(randomized array)
int main(){
	AVL_Tree avl;
	int i, result, key[N + 1], search_key[N + 1];
	double start_time;
	init(key, search_key);
	for (i = 1; i <= N; i++) avl.insert(key[i]);
	start_time = clock();
	for (i = 1; i <= N; i++) {
		result = avl.search(search_key[i]);
		if (result == -1 || result != search_key[i]) {
			cout << "탐색 오류." << endl;
		}
	}
	cout << "AVL 트리의 실행 시간 (N = " << N << ") : " <<
		clock() - start_time << endl;
	cout << "탐색 완료." << endl;
}
				*/

		/* main for testing array(size of N) arranged ordered and inordered
int main() {
	AVL_Tree avl;
	int i, result, key[N + 1], search_key[N + 1];
	double start_time;
				init_right(key, search_key);
				for (i = 1; i <= N; i++) avl.insert(key[i]);
				start_time = clock();
				for (i = 1; i <= N; i++) {
				result = avl.search(search_key[i]);
				if (result == -1 || result != search_key[i]) {
				cout << "탐색 오류." << endl;
				}
				}
				cout << "정렬된 배열에 대한 AVL 트리 탐색의 실행 시간 (N = " << N << ") : " <<
				clock() - start_time << endl;
				cout << "탐색 완료." << endl;
				init_reverse(key, search_key);
				for (i = 1; i <= N; i++) avl.insert(key[i]);
				start_time = clock();
				for (i = 1; i <= N; i++) {
				result = avl.search(search_key[i]);
				if (result == -1 || result != search_key[i]) {
				cout << "탐색 오류." << endl;
				}
				}
				cout << "역순 정렬된 배열에 대한 AVL 트리 탐색의 실행 시간 (N = " << N << ") : " <<
				clock() - start_time << endl;
				cout << "탐색 완료." << endl;
				}
				*/


int main(){
	AVL_Tree avl;
	int i, result;
	int exp_search_key[11];
	int exp_key[11] = { 0,2,1,8,9,7,3,6,4,5 };
	double start_time;

	for (int i = 1; i <= 9; i++)
		exp_search_key[i] = i;
	for (i = 1; i <= 9; i++) avl.insert(exp_key[i]);

	cout << "[";
	for (int i = 1; i <= 8; i++) {
		cout << exp_key[i] << ", ";
	}
    cout << exp_key[9] << "]" << endl;

	start_time = clock();

	for (i = 1; i <= 9; i++) {
		result = avl.search(exp_search_key[i]);
		if (result == -1 || result != exp_search_key[i]) {
		cout << "탐색 오류." << endl;
		}
	}
	avl.check(exp_search_key);
	cout << "AVL 트리의 실행 시간 (N = " << N << ") : " <<
	clock() - start_time << endl;
	cout << "탐색 완료." << endl;

}


				/* main for testing
				int main() {
				int c, i;
				AVL_Tree avl;
				int k, result;
				int exp_search_key[11];
				int exp_key[11] = { 0,2,1,8,9,7,3,6,4,5 };
				for (int i = 1; i <= 9; i++)
				exp_search_key[i] = i;
				for (int i = 1; i <= 9; i++) avl.insert(exp_key[i]);
				for (int i = 1; i <= 9; i++) {
				result = avl.search(exp_search_key[i]);
				cout << result << endl;
				if (result == -1 || result != exp_search_key[i]) {
				cout << "Å½»ö ¿À·ù." << endl;
				cout << "정렬오류." << endl;
				}
				}
				return 0;
				}
				}
				*/