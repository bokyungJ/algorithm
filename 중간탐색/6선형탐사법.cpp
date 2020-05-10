#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

const int N = 10000;
const int M = 10391;
int hash_1(int v, int M);

class Dict
{
public:
	Dict() {
		a = new int[M];
		for (int i = 0; i < M; i++) a[i] = -1;
	}
	void insert(int v);
	int search(int v);
	void print();
private:
	int *a;
};

int Dict::search(int v)
{
	int x;
	x = hash_1(v, M);
	while (a[x] != -1) {
		if (v == a[x])
			return a[x];
		else
			x = (x + 1) % M;
	}
	return -1;
}
void Dict::insert(int v)
{
	int x;
	x = hash_1(v, M);
	while (a[x] != -1)
		x = (x + 1) % M;
	a[x] = v;
}
void Dict::print()
{
	for (int i = 0; i < M; i++) {
		if (a[i] != -1) cout << '#';
		else cout << ' ';
		if ((i + 1) % 70 == 0) cout << endl;
	}
	cout << endl;
} void init(int key[], int search_key[])
{
	int i;
	srand(time(NULL));
	for (i = 0; i < N; i++) {
		key[i] = search_key[i] = rand();
	}
}
int hash_1(int v, int M)
{
	return (v % M);
}
int main()
{
	Dict d;
	int i, result, key[N], search_key[N];
	double start_time;
	init(key, search_key);
	for (i = 0; i < N; i++) d.insert(key[i]);
	d.print();
	start_time = clock();
	for (i = 0; i < N; i++) {
		result = d.search(search_key[i]);
		if (result == -1 || result != search_key[i]) {
			cout << "탐색 오류." << result << " " << i << endl;
		}
	}
	cout << "선형 탐사법의 실행 시간 (N = " << N << ") : " <<
		clock() - start_time << endl;
	cout << "탐색 완료." << endl;
}