#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "sort.h"
using namespace std;

const int N = 100000;
void QuickSort(int a[], int l, int r)
{
	int i, j, v;
	if (r > l) {
		v = a[r]; i = l - 1; j = r;
		for (; ; ) {
			while (a[++i] < v);
			while (a[--j] > v);
			if (i >= j) break;
			swap(a, i, j);
		}
		swap(a, i, r);
		QuickSort(a, l, i - 1);
		QuickSort(a, i + 1, r);
	}
}
int main()
{
	int i, a[N + 1];
	double start_time;
	a[0] = -1; // 감시 키

	//랜덤배열
	srand(time(NULL));
	for (i = 1; i <= N; i++) a[i] = rand();

	//정렬배열
	//for (int i = 1; i <= N; i++) a[i] = i;

	//역순배열
	/*
	int n = N;
	for (i = 1; i <= N; i++) {
	a[i] = n;
	n--;
	}*/

	start_time = clock();
	QuickSort(a, 1, N);
	cout << "퀵 정렬의 실행 시간 (N = " << N << ") : " <<
		clock() - start_time << endl;
	CheckSort(a, N);
}