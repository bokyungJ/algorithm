#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "sort.h"
using namespace std;

const int N = 10000;
void BubbleSort(int a[], int N)
{
	int i, j;
	for (i = N; i >= 1; i--) {
		for (j = 1; j < i; j++)
			if (a[j] > a[j + 1]) swap(a, j, j + 1);
	}
}
int main()
{
	int i, a[N + 1];
	double start_time;

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
	BubbleSort(a, N);
	cout << "버블 정렬의 실행 시간 (N = " << N << ") : " <<
		clock() - start_time << endl;
	CheckSort(a, N);
}
