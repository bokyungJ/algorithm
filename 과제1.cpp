#include <iostream>
using namespace std;

const int q = 33554393;
const int d = 32;

int index(char c) {
	if (c == 32) return 0;
	else return (c - 64);
}

int RabinKarp(char *p, char *t) {
	int i, dM = 1, h1 = 0, h2 = 0;
	int M = strlen(p), N = strlen(t);
	for (i = 1; i < M; i++) dM = (d*dM) % q;
	for (i = 0; i < M; i++) {
		h1 = (h1*d + index(p[i])) % q;
		h2 = (h2*d + index(t[i])) % q;
	}
	for (i = 0; h1 != h2; i++) {
		h2 = (h2 + d*q - index(t[i])*dM) % q;
		h2 = (h2 * d + index(t[i + M])) % q;
		if (i > N - M) return N;
	}
	return i;
}

int main() {
	char text[100] = "STRING STARTING CONSISTING";
	char pattern[50] = "STING";
	int M, N, pos, previous = 0, i = 0;
	M = strlen(pattern);
	N = strlen(text);
	while (1) {
		pos = RabinKarp(pattern, text + i);
		pos += previous;
		i = pos + M;
		if (i <= N) cout << "패턴이 발생한 위치 : " << pos << endl;
		else break;
		previous = i;
	}
	cout << "스트링 탐색 종료" << endl;
}
