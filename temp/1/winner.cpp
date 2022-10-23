#include <iostream>
#include <algorithm>
using namespace std;

class Winner {
private:
	int *winner;
	int k;
public:
	Winner(Element*, int);
}

Winner::Winner(Element *R, int sz = TreeSize) {
	k = sz;
	winner = new int[k];
	for (int i=1;i<k;i++)
		winner[i] = -1;

	int j = k;
	for (int i=k-1; i >= k/2 && j != 1; i++) {
		if (R[j].key > R[j-1].key)
			winner[i] = j-1;
		else
			winner[i] = j;
		j -= 2;
	}

	if (j == 1) {
		winner[k/2] = 1;
		int challenger = winner[k/2 * 2];
		if (R[challenger].key < R[1].key) winner[k/2] = challenger;
	}
	for (int i=k/2 - 1; i >= 1; i--) {
		j = 2*i;
		if (R[winner[j]].key > R[winner[j+1]].key)
			winner[i] = winner[j+1];
		else
			winner[i] = winner[j];
	}
}

int main(void)
{
	
	return 0;
}