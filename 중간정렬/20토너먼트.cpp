#include <iostream>
#include <stdlib.h>
#include "TounamentSort.h"

using namespace std;

TournamentSort::TournamentSort(int nSize)
	:m_nIndex(1), m_nSize(nSize), m_nLeafSize(1), m_nLevel(0), m_nStartPos(1)
{
	m_nArr = new int[nSize + 1];
	m_nArr[0] = MIN_NUM;

	for (int i = 1; i<m_nSize; m_nLevel++)
		i *= 2;

	for (int k = 1; k <= m_nLevel; k++)
		m_nLeafSize *= 2;

	m_nBTree = new int[m_nLeafSize * 2];
	for (int i = 0; i <= m_nLeafSize * 2; i++)
		m_nBTree[i] = MIN_NUM;

	for (int i = 1; i <= m_nLevel; i++)
		m_nStartPos *= 2;

	srand(time(NULL));
}

TournamentSort::~TournamentSort()
{
	if (m_nArr)	delete[] m_nArr;
}

void TournamentSort::initRandom()
{
	for (int i = 1; i <= m_nSize; i++) m_nArr[i] = rand();
}

void TournamentSort::initSorted()
{
	for (int i = 1; i <= m_nSize; i++) m_nArr[i] = i;
}

void TournamentSort::initReverse()
{
	for (int i = 1; i <= m_nSize; i++) m_nArr[i] = m_nSize + 1 - i;
}

void TournamentSort::start()
{
	int nPos = m_nStartPos;
	int nUpPos = m_nStartPos >> 1;
	int nSize = m_nLeafSize;
	int nCount = 1;
	int i = 0;
	double fStart = clock();

	copyToLeaf();	//리프 노드로 복사
					//처음 상위레벨로 승자트리 만들기
	for (; i<m_nSize >> 1; ++i)
	{
		if (m_nBTree[nPos + (i << 1)] == MIN_NUM)
			break;
		else if (m_nBTree[nPos + (i << 1)] >= m_nBTree[nPos + (i << 1) + 1])
			m_nBTree[nUpPos + i] = nPos + (i << 1);
		else
			m_nBTree[nUpPos + i] = nPos + (i << 1) + 1;
	}

	//첫번째 데이터 구하기
	while (nUpPos != 1)
	{
		nPos = nPos >> 1;
		nUpPos = nUpPos >> 1;
		nSize = nSize >> 1;
		for (i = 0; i<nSize >> 1; ++i)
		{
			if (m_nBTree[nPos + (i << 1)] == MIN_NUM)
				break;
			else if (m_nBTree[m_nBTree[nPos + (i << 1)]] >= m_nBTree[m_nBTree[nPos + (i << 1) + 1]])
				m_nBTree[nUpPos + i] = m_nBTree[nPos + (i << 1)];
			else
				m_nBTree[nUpPos + i] = m_nBTree[nPos + (i << 1) + 1];
		}
	}

	while (nCount <= m_nSize)
	{
		// 추출된 데이터 원래 배열끝부터 삽입
		m_nArr[m_nSize + 1 - nCount] = m_nBTree[m_nBTree[nUpPos]];
		// 추출한 리프노드에 최소값(-1) 삽입
		m_nBTree[m_nBTree[nUpPos]] = MIN_NUM;

		// 추출된 리프노드만 상위레벨로 다시 승자트리 만들기
		nPos = m_nBTree[nUpPos];
		if ((nPos << 31) ^ 0) --nPos;
		nUpPos = nPos >> 1;

		if (m_nBTree[nPos] >= m_nBTree[nPos + 1])
			m_nBTree[nUpPos] = nPos;
		else
			m_nBTree[nUpPos] = nPos + 1;

		while (nUpPos != 1)
		{
			nPos = nPos >> 1;
			nUpPos = nUpPos >> 1;
			if ((nPos << 31) ^ 0) --nPos;
			if (m_nBTree[m_nBTree[nPos]] >= m_nBTree[m_nBTree[nPos + 1]])
				m_nBTree[nUpPos] = m_nBTree[nPos];
			else
				m_nBTree[nUpPos] = m_nBTree[nPos + 1];
		}
		++nCount;
	}
	m_fSortingTime = clock() - fStart;
}

void TournamentSort::copyToLeaf()
{
	int nPos = m_nStartPos;
	for (int i = 1; i <= m_nSize; i++)
		m_nBTree[nPos++] = m_nArr[i];
}

bool TournamentSort::isSorted()
{
	for (int i = 1; i<m_nSize; i++)
		if (m_nArr[i] > m_nArr[i + 1]) return false;
	return true;
}

int main()
{
	cout << "토너먼트 정렬을 원하는 개수를 입력하세요: ";
	int nNum;
	cin >> nNum;
	TournamentSort TSort(nNum);
	cout << "데이터 삽입 종류를 선택하세요(1번-랜덤, 2번-정렬, 3번-역순): ";
	int nSelect;
	cin >> nSelect;
	char* strNumType = NULL;
	switch (nSelect)
	{
	case 1:
		TSort.initRandom();
		strNumType = "랜덤";
		break;
	case 2:
		TSort.initSorted();
		strNumType = "정렬";
		break;
	case 3:
		TSort.initReverse();
		strNumType = "역순";
		break;
	}
	TSort.start();

	cout << "[" << strNumType << "] 토너먼트 정렬의 실행 시간 (개수 = "
		<< TSort.getSize() << " ) : " << TSort.getTime() << endl;


	if (TSort.isSorted()) cout << "정렬 완료" << endl;
	else cout << "정렬 오류 발생" << endl;

	return 0;
}