#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "sort.h"
using namespace std;

const int N = 10000;

void cocktailShaker(int a[], int n) {
	int i, start = 1, end = n;
	while (start < end) {
		for (i = start; i < end; i++) {
			if (a[i] > a[i + 1]) swap(a, i, i + 1);
		}
		for (i = end - 1; i >= start; i--) {
			if (a[i] < a[i - 1]) swap(a, i, i - 1);
		}
		start++;
		end--;
	}
}

void exchangeSort(int a[], int n) {
	int i, j;
	for (i = 1; i <= N; i++) {
		for (j = i; j <= N - 1; j++) {
			if (a[i] < a[j + 1]) swap(a, i, j + 1);
		}
	}
}
/*
void exchangeSort(int a[], int n) {
	int i, j;
	for (i = 1; i <= N-1; i++) {
		for (j = i + 1; j <= n; j++) {
			if (a[j] < a[i]) swap(a, i, j);
		}
	}
}*/

void checkReverse(int a[], int n) {
	int i, Sorted;
	Sorted = TRUE;
	for (i = 1; i < n; i++) {
		if (a[i] < a[i + 1])
			Sorted = FALSE;
		if (!Sorted) break;
	}
	if (Sorted) cout << "역순 정렬 완료." << endl;
	else cout << "역순 정렬 오류 발생." << endl;
}

int main() {
	int i;
	int a[N + 1];
	double start_time;

	//랜덤 배열
	srand(time(NULL));
	for (i = 1; i <= N; i++) a[i] = rand();

	//정렬 배열
	//for (i = 1; i <= N; i++) a[i] = i;


	//역순 배열
	/*
	int n = 1;
	for (i = N; i >= 1; i--) {
		a[i] = n;
		n++;
	}*/

	start_time = clock();
	//cocktailShaker(a, N);
	exchangeSort(a, N);
	cout << "정렬의 실행시간 (N=" << N << ") : " << clock() - start_time << endl;
	//CheckSort(a, N);
	checkReverse(a, N);
}
