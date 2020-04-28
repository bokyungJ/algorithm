#include <iostream>
#include "geogeo.h"
using namespace std;

const int N = 12;
void swap(struct point a[], int i, int j)
{
	struct point t = a[i]; a[i] = a[j]; a[j] = t;
}
float theta(struct point p1, struct point p2)
{
	int dx, dy, ax, ay;
	float t;
	dx = p2.x - p1.x; ax = abs(dx);
	dy = p2.y - p1.y; ay = abs(dy);
	t = (ax + ay == 0) ? 0 : (float)dy / (ax + ay);
	if (dx < 0) t = 2 - t; else if (dy < 0) t = 4 + t;
	return t*90.0;
}
int PackageWrapping(point p[], int N)
{
	int i, min, M; float th, v;
	for (min = 0, i = 1; i < N; i++)
		if (p[i].y < p[min].y) min = i;
	p[N] = p[min]; th = 0.0;
	for (M = 0; M < N; M++) {
		swap(p, M, min);
		min = N; v = th; th = 360.0;
		for (i = M + 1; i <= N; i++)
			if (theta(p[M], p[i]) > v)
				if (theta(p[M], p[i]) < th) {
					min = i;
					th = theta(p[M], p[min]);
				}
		if (min == N) return M;
	}
}
int main()
{
	struct point p[N + 1];
	int i, M;
	for (i = 0; i < N; i++) {
		p[i].x = x_value[i];
		p[i].y = y_value[i];
		p[i].c = c_value[i];
	}
	M = PackageWrapping(p, N);
	for (i = 0; i <= M; i++)
		cout << p[i].c << " ";
	cout << endl;
}