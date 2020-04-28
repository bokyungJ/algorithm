#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "sort.h"
using namespace std;

const int N = 20000;
const int M = 20;
void SelectionSort(int a[], int N) {
	int i, j, min;
	for (i = 1; i < N; i++) {
		min = i;
		for (j = i + 1; j <= N; j++) {
			if (a[j] < a[min]) min = j;
		}
		swap(a, min, i);
	}
}

void BubbleSort(int a[], int N) {
	int i, j;
	for (i = N; i >= 1; i--) {
		for (j = 1; j < i; j++) {
			if (a[j] > a[j + 1]) swap(a, j, j + 1);
		}
	}
}

void InsertionSort(int a[], int N) {
	int i, j, v;
	for (i = 2; i <= N; i++) {
		v = a[i];
		j = i;
		while (a[j - 1] > v) {
			a[j] = a[j - 1];
			j--;
		}
		a[j] = v;
	}
}

void ShellSort(int a[], int N) {
	int i, j, h, v;
	for (h = 1; h < N; h = 3 * h + 1);
	for (; h > 0; h /= 3) {
		for (i = h + 1; i <= N; i++) {
			v = a[i];
			j = i;
			while (j > h && a[j - h] > v) {
				a[j] = a[j - h];
				j -= h;
			}
			a[j] = v;
		}
	}
}

void QuickSort(int a[], int l, int r) {
	int i, j, v;
	if (r > l) {
		v = a[r];
		i = l - 1;
		j = r;
		for (;;) {
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
/*
int partition(int a[], int l, int r) {
int i, j, v;
v = a[r];
i = l - 1;
j = r;
for (;;) {
do {
i++;
} while (a[i] < v);
do {
j--;
} while (a[j] > v);
if (i >= j) break;
swap(a, i, j);
}
swap(a, i, r);
return i;
}

void qs(int a[], int l, int r) {
int i;
if (r > l) {
i = partition(a, l, r);
qs(a, l, i - 1);
qs(a, i + 1, r);
}
}
*/


void Ipartfile(int a[], int l, int r) {
	int i, j, v;
	for (i = l + 1; i <= r; i++) {
		v = a[i];
		j = i;
		while (a[j - 1] > v) {
			a[j] = a[j - 1];
			j--;
		}
		a[j] = v;
	}
}

void Qpartfile(int a[], int l, int r) {
	int i, j, v;
	if (r - l <= M) Ipartfile(a, l, r);
	else {
		v = a[r];
		i = l - 1;
		j = r;
		for (;;) {
			while (a[++i] < v);
			while (a[--j] > v);
			if (i >= j) break;
			swap(a, i, j);
		}
		swap(a, i, r);
		Qpartfile(a, l, i - 1);
		Qpartfile(a, i + 1, r);
	}
}

void Qmiddle(int a[], int l, int r) {
	int i, j, m, v;
	if (r - l > 1) {
		m = (l + r) / 2;
		if (a[l] > a[m]) swap(a, l, m);
		if (a[l] > a[r]) swap(a, l, r);
		if (a[m] > a[r]) swap(a, m, r);
		swap(a, m, r - 1);
		v = a[r - 1];
		i = l;
		j = r - 1;
		for (;;) {
			while (a[++i] < v);
			while (a[--j] > v);
			if (i >= j) break;
			swap(a, i, j);
		}
		swap(a, i, r - 1);
		Qmiddle(a, l, i - 1);
		Qmiddle(a, i + 1, r);
	}
	else if (a[l] > a[r]) swap(a, l, r);
}

int main() {
	int i, a[N + 1];
	double start_time;

	//삽입 정렬, 쉘정렬의 경우 감시키
	a[0] = -1;

	//랜덤 배열
	srand(time(NULL));
	for (i = 1; i <= N; i++) a[i] = rand();


	//정렬 배열
	//for (int i = 1; i <= N; i++) a[i] = i;


	//역순 배열
	/*
	int n = N;
	for (i = 1; i <=N; i++) {
	a[i] = n;
	n--;
	}*/


	//qs는 빼도 될거 같음

	start_time = clock();
	//SelectionSort(a, N);
	//BubbleSort(a, N);
	//InsertionSort(a, N);
	//ShellSort(a, N);
	//QuickSort(a, 1, N);
	//Qpartfile(a, 1, N);
	//qs(a, 1, N);
	Qmiddle(a, 1, N);
	cout << "정렬의 실행시간 (N=" << N << ") : " << clock() - start_time << endl;
	CheckSort(a, N);
}