#include "Manager.h"

using namespace std;
#define THRESHOLD 3;
#define ORDER 3;

int main(void)
{
	Manager manager(3, 3); // first value is threshold of fpgrowth, second value is order of bptree
	manager.run("command.txt");
	return 0;
}
