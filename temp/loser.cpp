#include <iostream>
#include <algorithm>
using namespace std;

class Loser
{
private:
	int *loser;
	int k;

public:
	Loser(Element *, int);
}

Loser::Loser(Element *R, int sz = TreeSize)
{
	k = sz;
	int winner, l;

	loser = new int[k];
	for (int i = 0; i < k; i++)
		loser[i] = -1;
	int j = k;
	for (int i = k - 1; i >= k / 2 && j != 1; i--)
	{
		if (R[j].key > R[j - 1].key)
		{
			loser[i] = j;
			winner = j - 1;
		}
		else
		{
			loser[i] = j - 1;
			winner = j;
		}

		j -= 2;
		l = i / 2;
		while (loser[l] != -1)
		{
			if (R[loser[l]].key < R[winner].key)
			{
				int temp = winner;
				winner = loser[l];
				loser[l] = temp;
			}
			l / 2;
		}
		loser[l] = winner;
	}
	if (j == 1)
	{
		winner = 1;
		l = k / 2;
		while (loser[l] != -1)
		{
			if (R[loser[l]].key < R[winner].key)
			{
				int temp = winner;
				winner = loser[l];
				loser[l] = temp;
			}
			l / 2;
		}
		loser[l] = winner;
	}
}

int main(void)
{

	return 0;
}