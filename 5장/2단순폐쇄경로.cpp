#include <iostream>
#include "geo_1.h"
using namespace std;

const int N = 16;

void swap(struct point a[], int i, int j) {
	struct point t = a[i];
	a[i] = a[j];
	a[j] = t;
}

float theta(struct point p1, struct point p2) {
	int dx, dy, ax, ay;
	float t;
	dx = p2.x - p1.x;
	ax = abs(dx);
	dy = p2.y - p1.y;
	ay = abs(dy);
	t = (ax + ay == 0) ? 0 : (float)dy / float(ax + ay);
	if (dx < 0)t = 2 - t;
	else if (dy < 0) t = 4 + t;
	return t*90.0;
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
	struct point p[N + 1];
	int i, min;
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
	for (i = 1; i <= N; i++) {
		cout << p[i].c << " ";
	}
	cout << p[1].c << endl;

}