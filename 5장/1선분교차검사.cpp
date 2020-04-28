#include <iostream>
#include "geo_1.h"
using namespace std;

const int N = 16;

int ccw(struct point p0, struct point p1, struct point p2) {
	int dx1, dx2, dy1, dy2;
	dx1 = p1.x - p0.x;
	dy1 = p1.y - p0.y;
	dx2 = p2.x - p0.x;
	dy2 = p2.y - p0.y;

	if (dx1*dy2 > dy1*dx2) return +1;
	if (dx1*dy2 < dy1*dx2) return -1;
	if ((dx1 == 0) && (dy1 == 0)) return 0;
	if ((dx1*dx2 < 0) || (dy1*dy2 < 0)) return -1;
	if ((dx1*dx1 + dy1*dy1) < (dx2*dx2 + dy2*dy2)) return +1;
	return 0;
}

int intersect(struct line l1, struct line l2) {
	return((ccw(l1.p1, l1.p2, l2.p1)*ccw(l1.p1, l1.p2, l2.p2)) <= 0) &&
		((ccw(l2.p1, l2.p2, l1.p1)*ccw(l2.p1, l2.p2, l1.p2)) <= 0);
}

void print(struct line l1, struct line l2, int result) {
	if (result)cout << "선분 " << l1.p1.c << l1.p2.c << "와 선분 " <<
		l2.p1.c << l2.p2.c << "는 교차함." << endl;
	else cout << "선분 " << l1.p1.c << l1.p2.c << "와 선분 " <<
		l2.p1.c << l2.p2.c << "는 교차하지 않음." << endl;
}

int main() {
	point p[N + 1];
	line l1, l2;
	int i, result;

	for (i = 1; i <= N; i++) {
		p[i].x = x_value[i - 1];
		p[i].y = y_value[i - 1];
		p[i].c = c_value[i - 1];
	}

	l1.p1 = p[1]; //A
	l1.p2 = p[15]; //O
	l2.p1 = p[3]; //C
	l2.p2 = p[14]; //N
	result = intersect(l1, l2);
	print(l1, l2, result);

	l1.p1 = p[4]; //D
	l1.p2 = p[8]; //H
	l2.p1 = p[5]; //E
	l2.p2 = p[9]; //I
	result = intersect(l1, l2);
	print(l1, l2, result);

	l1.p1 = p[1]; //A
	l1.p2 = p[15]; //O
	l2.p1 = p[4]; //D
	l2.p2 = p[7]; //G
	result = intersect(l1, l2);
	print(l1, l2, result);

	l1.p1 = p[9]; //I
	l1.p2 = p[16]; //P
	l2.p1 = p[10]; //J
	l2.p2 = p[14]; //N
	result = intersect(l1, l2);
	print(l1, l2, result);
}