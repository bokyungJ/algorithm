#include <iostream>
#include <limits.h>
using namespace std;

const int N = 4;

float OptimalBST(float *p, int r[][N + 1], int n) {
	float A[N + 1][N + 1] = { 0.0 };
	float q, p_sum;
	int h, i, j, k, m;
	for (i = 1; i <= n; i++) {
		A[i][i] = p[i];
		r[i][i] = i;
	}
	for (h = 1; h < n; h++) {
		for (i = 1; i <= n - h; i++) {
			j = i + h;
			A[i][j] = INT_MAX;
			p_sum = 0;
			for (m = i; m <= j; m++)
				p_sum += p[m];
			for (k = i; k <= j; k++) {
				q = A[i][k - 1] + A[k + 1][j] + p_sum;
				if (q < A[i][j]) {
					A[i][j] = q;
					r[i][j] = k;
				}
			}
		}
	}
	return A[1][n];
}

int main() {
	float p[5] = { 0.0,0.1,0.2,0.3,0.4 };
	float result;
	int r[N + 1][N + 1] = { 0 };

	result = OptimalBST(p, r, N);
	cout << "최소 평균 탐색 시간 : " << result << endl;
}