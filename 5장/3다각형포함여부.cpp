#include <iostream>
#include "geo_1.h"
using namespace std;

const int N = 16;

void swap(struct point a[], int i, int j) {
	struct point t = a[i];
	a[i] = a[j];
	a[j] = t;
}
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

float theta(struct point p1, struct point p2) {
	int dx, dy, ax, ay;
	float t;
	dx = p2.x - p1.x;
	ax = abs(dx);
	dy = p2.y - p1.y;
	ay = abs(dy);
	t = (ax + ay == 0) ? 0 : (float)dy / (ax + ay);
	if (dx < 0)t = 2 - t;
	else if (dy < 0) t = 4 + t;
	return t*90.0;
}

int inside(struct point t, struct point p[], int N) {
	int i, count = 0, j = 0;
	struct line lt, lp;
	p[0] = p[N];
	p[N + 1] = p[1];
	lt.p1 = t;
	lt.p2 = t;
	lt.p2.x = 1000;
	for (i = 1; i <= N; i++) {
		lp.p1 = p[i];
		lp.p2 = p[i];
		if (!intersect(lp, lt)) {
			lp.p2 = p[j];
			j = i;
			if (intersect(lp, lt)) count++;
		}
	}
	return count & 1;
}
void SelectionSort(struct point p[], int N) {
	int i, j, min;
	for (i = 1; i < N; i++) {
		min = i;
		for (j = i + 1; j <= N; j++) {
			if (theta(p[1], p[j]) < theta(p[1], p[min]))min = j;
		}
		swap(p, min, i);
	}
}

int main() {
	struct point t, p[N + 1];
	float angle[N + 1];
	int i, min,result;

	for (i = 1; i <= N; i++) {
		p[i].x = x_value[i - 1];
		p[i].y = y_value[i - 1];
		p[i].c = c_value[i - 1];
	}

	for (min = 1, i = 2; i <= N; i++) {
		if (p[i].y < p[min].y)min = 1;
	}
	
	swap(p, 1, min);
	SelectionSort(p, N);
	
	while (1) {
		cout << "좌표값 입력 " << endl;
		cout << "x = ";
		cin >> t.x;
		cout << "y = ";
		cin >> t.y;
		if (t.x <= 0 && t.y <= 0) break;
		result = inside(t, p, N);
		if (result) cout << "다각형 내부의 점입니다";
		else cout << "다각형 외부의 점입니다";
		cout << endl;
		cout << endl;
	}

}