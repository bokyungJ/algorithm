#include <iostream>
using namespace std;

int EditDistance(char *s, char *t, int m, int n) {
	int N = n;
	int M = m;
	int D[6 + 1][7 + 1];
	int i, j, cost, insertion, deletion, substitution, min;
	D[0][0] = 0;
	for (i = 1; i <= n; i++) {
		D[i][0] = D[i - 1][0] + 1;
	}
	for (j = 1; j <= m; j++) {
		D[0][j] = D[0][j - 1] + 1;
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			cost = (s[i - 1] == t[j - 1]) ? 0 : 1;
			insertion = D[i][j - 1] + 1;
			deletion = D[i - 1][j] + 1;
			substitution = D[i - 1][j - 1] + cost;
			min = insertion;
			if (deletion < min) min = deletion;
			else if (substitution < min) min = substitution;
			D[i][j] = min;
		}
	}
	return D[n][m];
}

int main() {
	char s[6] = "GUMBO";
	char t[7] = "GAMBOL";
	int m, n, result;

	m = strlen(s);
	n = strlen(t);
	result = EditDistance(s, t, m, n);
	cout << "스트링 편집 거리 : " << result << endl;
}