#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "sort.h"
using namespace std;

const int N = 10000;
void ShellSort(int a[], int N)
{
	int i, j, h, v;
	for (h = 1; h < N; h = 3 * h + 1);
	for (; h > 0; h /= 3)
		for (i = h + 1; i <= N; i++) {
			v = a[i]; j = i;
			while (j > h && a[j - h] > v) {
				a[j] = a[j - h]; j -= h;
			}
			a[j] = v;
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
	ShellSort(a, N);
	cout << "쉘 정렬의 실행 시간 (N = " << N << ") : " <<
		clock() - start_time << endl;
	CheckSort(a, N);
}