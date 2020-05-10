#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

const int N = 10000;
class Dict
{
public:
	Dict(int max) { a = new node[max]; n = 0; }
	~Dict() { delete a; }
	int search(int search_key);
	void insert(int v);
private:
	struct node {
		int key;
	};
	struct node *a;
	int n;
};
int Dict::search(int search_key)
{
	int i;
	i = 1;
	while (i <= n && a[i].key != search_key) i++;
	if (i == n + 1) return -1;
	else return i;
}
void Dict::insert(int v)
{
	a[++n].key = v;
}
void init(int key[], int search_key[])
{
	int i, index, temp[N + 1];
	for (i = 1; i <= N; i++) {
		key[i] = i;
		search_key[i] = i;
		temp[i] = 0;
	}
	srand(time(NULL));
	for (i = 1; i <= N; i++) {
		index = rand() % N + 1;
		if (temp[index] == 0)
			temp[index] = key[i];
		else {
			while (temp[index] != 0)
				index = (index % N) + 1;
			temp[index] = key[i];
		}
	}
	for (i = 1; i <= N; i++) {
		key[i] = temp[i];
	}
}
int main()
{
	Dict d(N + 1);
	int i, result, key[N + 1], search_key[N + 1];
	double start_time;
	init(key, search_key);
	for (i = 1; i <= N; i++) d.insert(key[i]);
	start_time = clock();
	for (i = 1; i <= N; i++) {
		result = d.search(search_key[i]);
		if (result == -1 || key[result] != search_key[i]) {
			cout << "탐색 오류." << endl;
		}
	}
	cout << "순차 탐색의 실행 시간 (N = " << N << ") : " <<
		clock() - start_time << endl;
	cout << "탐색 완료." << endl;
}