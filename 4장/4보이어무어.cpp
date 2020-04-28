#include <iostream>
using namespace std;

const int NUM = 27;
int skip[NUM];

int index(char c) {
	if (c == 32) return 0;
	else return (c - 64);
}

void InitSkip(char *p) {
	int i, j, M = strlen(p);
	for (i = 0; i < NUM; i++) skip[i] = M;
	for (i = 0; i < M; i++) skip[index(p[i])] = M - i - 1;
}

int MisChar(char *p, char *t) {
	int i, j, k, M = strlen(p), N = strlen(t);
	InitSkip(p);
	for (i = M - 1, j = M - 1; j >= 0; i--, j--) {
		while (t[i] != p[j]) {
			k = skip[index(t[i])];
			i += (M - j > k) ? M - j : k;
			if (i >= N)return N;
			j = M - 1;
		}
	}
	return i + 1;
}

int main() {
	char text[100] = "VISION QUESTION ONION CAPTION GRADUATION EDUCATION";
	char pattern[50] = "ATION";
	int M, N, pos, previous = 0, i = 0;

	M = strlen(pattern);
	N = strlen(text);
	while (1) {
		pos = MisChar(pattern, text + i);
		pos += previous;
		i = pos + M;
		if (i <= N) cout << "패턴이 발생한 위치 : " << pos << endl;
		else break;
		previous = i;
	}
	cout << "스트링 탐색 종료 " << endl;

}