#include <iostream>
#include <stdlib.h>
using namespace std;

int cnt = 0;
int bruteForce(char p[], char t[], int k) {
	int M = strlen(p);
	int N = strlen(t);

	int i, j;
	int count = 0;
	for (i = k, j = 0; j < M && i < N; i++, j++) {
		if (t[i] != p[j]) {
			i -= j;
			j = -1;
		}
		count++;
	}

	cnt += count;

	if (j == M) {
		return i - M;
	}
	else {
		return i;
	}

}
int main() {
	char t[] = "ababacabcbababcacacbcaababca";
	char p[] = "ababca";
	int k = -1;
	while (strlen(p) + k < strlen(t)) {
		k = bruteForce(p, t, k + 1);
		cout << "패턴이 나타난 위치 : " << k << endl;
	}
	cout << "총 비교횟수 : " << cnt << endl;
}