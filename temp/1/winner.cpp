#include <iostream>
#include <algorithm>
using namespace std;

class Winner
{
private:
	int *winner;
	int k; // winner의 size k개의 run이 있다.

public:
	Winner(){};
	Winner(Element *, int){};
}

Winner::Winner(Element *R, int szTreeSize = sz) // run 배열과 k 값
{
	k = sz;
	winner = new int[k];
	for (int i = 1; i < k; i++)
		winner[i] = -1; // internal node를 저장하고 있는 배열
						// run의 index를 담고있다.
	int j = k;			// run에 대해서 루프를 돈다.
	for (int i = k - 1; i >= k / 2 && j != 1; i--)
	{ // leaf노드에서 토너먼트를돈다.
		if (R[j].key > R[j - 1].key)
			winner[i] = j - 1;
		else
			winner[i] = j;
		j -= 2;
	}

	if (j == 1)
	{
		winner[k / 2] = 1;
		int challenger = winner[k / 2 * 2];
		if (R[challenger].key < R[1].key)
			winner[k / 2] = challenger;
	}
	for (int i = k / 2 - 1; i >= 1; i--)
	{
		j = 2 * i;
		if (R[winner[j]].key > R[winner[j + 1]].key)
			winner[i] = winner[j + 1];
		else
			winner[i] = winner[j];
	}
}

int main(void)
{

	return 0;
}