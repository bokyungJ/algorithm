#include <iostream>
using namespace std;

int nexty[50];

void InitNext(char *p) {
	int i, j, M = strlen(p);
	nexty[0] = -1;
	for (i = 0, j = -1; i < M; i++, j++) {
		nexty[i] = (p[i] == p[j]) ? nexty[j] : j;
		while ((j >= 0) && (p[i] != p[j])) j = nexty[j];
	}
}

int KMP(char *p, char *t) {
	int i, j, M = strlen(p), N = strlen(t);
	InitNext(p);
	for (i = 0, j = 0; j < M && i < N; i++, j++)
		while ((j >= 0) && (t[i] != p[j]))j = nexty[j];
	if (j == M) return i - M;
	else return i;
}

int main() {
	char text[100] = "ababababcababababcaabbabababcaab";
	char pattern[50] = "abababca";
	int M, N, pos, previous = 0, i = 0;

	M = strlen(pattern);
	N = strlen(text);
	while (true) {
		pos = KMP(pattern, text + i);
		pos += previous;
		i = pos + M;
		if (i <= N) cout << "패턴이 발생한 위치 : " << pos << endl;
		else break;
		previous = i;
	}
	cout << "스트링 탐색 종료" << endl;
}