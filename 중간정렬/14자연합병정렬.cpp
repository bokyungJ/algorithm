#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "sort.h"
using namespace std;

const int N = 20000;
int b[N + 1];

void merge(int a[], int l, int m, int r)
{
	int i, j, k;
	for (i = m + 1; i > l; i--) b[i - 1] = a[i - 1];
	for (j = m; j < r; j++) b[r + m - j] = a[j + 1];
	for (k = l; k <= r; k++) a[k] = (b[i] < b[j]) ? b[i++] : b[j--];
}

int makeRun(int a[], int run[])
{
	int i = 1, j = 1;
	for (i = 1; i <= N; i++) {
		if (a[i] > a[i + 1]) {
			run[j++] = i;
		}
	}
	return j - 1;
}
int moveRun(int run[], int cnt)
{
	int i, j = 1;
	for (i = 2; i <= cnt; i += 2) run[j++] = run[i];
	if ((cnt % 2) != 0) run[j] = run[i - 1]; // cnt가 홀수일때 마지막 run처리
	else j--;
	return j;
}
void NaturalMergeSort(int a[], int n)
{
	int i, num;
	int cnt; // number of runs
	int run[N + 1];
	run[0] = 0;
	cnt = makeRun(a, run);
	while (cnt > 1) {
		if ((cnt % 2) != 0) num = cnt - 1; // cnt가 홀수일 때눈 cnt 값을 하나 감소
		else num = cnt;
		for (i = 1; i <= num; i += 2)
			merge(a, run[i - 1] + 1, run[i], run[i + 1]);
		cnt = moveRun(run, cnt);
	}
}

void heapify(int a[], int h, int m)
{
	int j, v;
	v = a[h];
	for (j = 2 * h; j <= m; j *= 2) {
		if (j < m && a[j] < a[j + 1]) j++;
		if (v >= a[j]) break;
		else a[j / 2] = a[j];
	}
	a[j / 2] = v;
}

void HeapSort(int a[], int n) {
	int i;
	for (i = n / 2; i >= 1; i--)
		heapify(a, i, n);
	for (i = n - 1; i >= 1; i--) {
		swap(a, 1, i + 1);
		heapify(a, 1, i);
	}
}
void MergeSort(int a[], int l, int r)
{
	int i, j, k, m;
	if (r > l) {
		m = (r + l) / 2;
		MergeSort(a, l, m);
		MergeSort(a, m + 1, r);
		for (i = m + 1; i > l; i--) b[i - 1] = a[i - 1];
		for (j = m; j < r; j++) b[r + m - j] = a[j + 1];
		for (k = l; k <= r; k++)
			a[k] = (b[i] < b[j]) ? b[i++] : b[j--];
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
	//for (i = 1; i <= N; i++) a[i] = i;

	//역순정렬배열
	/*int n = N;
	for (i = N; i >= 1; i--) {
	a[i] = n;
	n++;
	}*/

	start_time = clock();
	//NaturalMergeSort(a, N);
	//MergeSort(a, 1, N);
	HeapSort(a, N);

	cout << "정렬의 실행 시간 (N = " << N << ") : " <<
		clock() - start_time << endl;
	CheckSort(a, N);
}