#include <iostream>
#include "geo_1.h"
using namespace std;

const int N = 16;
const int maxG = 4;
const int size_1 = 4;

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
	struct node { struct point p; struct node *next; };
	struct node *grid[maxG + 1][maxG + 1];
	struct node *z;
};

Range::Range() {
	int i, j;
	z = new node;
	for (i = 0; i <= maxG; i++) {
		for (j = 0; j <= maxG; j++)
			grid[i][j] = z;
	}
}

void Range::insert(struct point p) {
	struct node *t = new node;
	t->p = p;
	t->next = grid[p.x / size_1][p.y / size_1];
	grid[p.x / size_1][p.y / size_1] = t;
}

int Range::search(struct rect range) {
	struct node *t;
	int i, j, count = 0;
	for (i = range.x1 / size_1; i <= range.x2 / size_1; i++) {
		for (j = range.y1 / size_1; j <= range.y2 / size_1; j++) {
			for (t = grid[i][j]; t != z; t = t->next)
				if (insiderect(t->p, range))count++;
		}
	}
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
	range.x1 = 7;
	range.y1 = 10;
	range.x2 = 11;
	range.y2 = 16;
	result = r.search(range);
	cout << "범위 내에 있는 점의 개수 : " << result << endl;
}
