#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "sort.h"
using namespace std;

const int N = 10000;

void isPerfect(int a) {
	int i;
	int sum = 0;
	for (i = 1; i <= a / 2; i++) {
		if (a%i == 0) {
			sum += i;
		}
	}
	if (sum == a) cout << a << "는 완전수입니다" << endl;
	else if (sum > a) cout << a << "는 과잉수입니다" << endl;
	else cout << a << "는 부족수입니다" << endl;
}

void isPrime(int a) {
	int i, flag = 0;
	for (i = 2; i <= a / 2; i++) {
		if (a%i == 0) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) cout << a << "는 소수가 아닙니다" << endl;
	else cout << a << "는 소수입니다" << endl;
}

void printNum(int N) {
	int i, j, k = 1, sum = 0, n = 1;
	while (true) {
		sum += pow(2, n - 1);
		if (sum >= N) break;
		n++;
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= pow(2, i - 1); j++) {
			cout << k << " ";
			k++;
			if (k > N) break;
		}
		cout << "\n";
	}
}

int main() {
	int a = 10;
	isPerfect(a);
	isPrime(a);
	printNum(a);
}