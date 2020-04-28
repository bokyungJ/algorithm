#include <iostream>
using namespace std;

const int scan = -1;
const int TRUE = 1;
const int FALSE = 0;
char ch[10] = { ' ', 'A', ' ', 'B', ' ', ' ', 'A', 'C', 'D', ' ' };
int next1[10] = { 5, 2, 3, 4, 8, 6, 7, 8, 9, 0 };
int next2[10] = { 5, 2, 1, 4, 8, 2, 7, 8, 9, 0 };
class Deque
{
private:
	int* deque;
	int first, last;
public:
	Deque(int size = 100) {
		deque = new int[size];
		first = size / 2; last = size / 2;
		for (int i = 0; i < size; i++) deque[i] = 0;
	}
	~Deque() { delete deque; }
	void insertFirst(int v) { deque[first--] = v; }
	void insertLast(int v) { deque[++last] = v; }
	int deleteFirst() { deque[first] = 0; return deque[++first]; }
	int isEmpty() { if (first == last) return TRUE; else return FALSE; }
	void prDq() {
		for (int i = 0; i < 100; i++) {
			if (deque[i] != 0) {
				cout << deque[i] << " ";
			}
		}
	}
};
int match(char* t)
{
	int n1, n2;
	Deque dq(100);
	int j = 0, N = strlen(t), state = next1[0];

	dq.insertLast(scan);
	while (state) {
		if (state == scan) {
			j++;
			if (dq.isEmpty()) dq.insertFirst(next1[0]);
			dq.insertLast(scan);
		}
		else if (ch[state] == t[j]) {
			dq.insertLast(next1[state]);
		}
		else if (ch[state] == ' ') {
			n1 = next1[state]; n2 = next2[state];
			dq.insertFirst(n1); if (n1 != n2) dq.insertFirst(n2);
		}

		dq.prDq();

		if (dq.isEmpty()) return j;
		if (j > N) return 0;
		state = dq.deleteFirst();
		cout << endl;
	}
	cout << endl;
	return j - 1;
}


int main()
{
	//char text[100] = "CDAABCAAABDDACDAACAAAAAAABD";
	char text[100] = "AABD";
	int N, pos, previous = 0, i = 0;
	N = strlen(text);
	while (1) {
		pos = match(text + i);
		if (pos == 0) break;
		pos += previous;
		i = pos;
		if (i <= N) cout << "패턴이 발생한 위치 : " << pos << endl;
		else break;
		previous = i;
	}
	cout << endl;
	cout << "패턴 매칭 종료." << endl;
}