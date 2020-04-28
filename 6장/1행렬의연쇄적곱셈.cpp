#include <iostream>
#include <limits.h>
using namespace std;

const int N = 6;

int MatrixChainMult(int *d, int p[][N + 1], int n) {
	int M[N + 1][N + 1] = { 0 };
	int h, i, j, k, q;
	for (h = 1; h <= n - 1; h++) {
		for (i = 1; i <= n - h; i++) {
			j = i + h;
			M[i][j] = INT_MAX;
			for (k = i; k < j; k++) {
				q = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
				if (q < M[i][j]) {
					M[i][j] = q;
					p[i][j] = k;
				}
			}
		}
	}
	return M[1][n];
}

int main() {
	int d[7] = { 4,2,3,1,2,2,3 };
	int p[N + 1][N + 1] = { 0 };

	int result;

	result = MatrixChainMult(d, p, N);
	cout << "최소곱셈횟수 : " << result << endl;
}