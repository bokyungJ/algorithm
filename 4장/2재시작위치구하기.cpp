#include <iostream>
#include <stdlib.h>
using namespace std;

void initNext(char p[]) {
	int M = strlen(p);
	int next[20];
	next[0] = -1;

	int i, j;
	for (i = 0, j = -1; j < M; i++, j++) {
		next[i] = j;
		while ((j >= 0) && (p[i] != p[j])) {
			j = next[j];
		}
	}
	int k;
	for (k = 1; k<20; k++) {
		cout << next[k] << endl;
	}
}

int main() {
	char p[] = "abababca";
	initNext(p);
}
