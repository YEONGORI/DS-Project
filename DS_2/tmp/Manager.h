#pragma once
#include "VaccinationData.h"
#include "AVLTree.h"
#include "BpTree.h"
#include <algorithm>

using namespace std;
class Manager
{
private:
	AVLTree *avl; // AVL tree
	BpTree *bp;	  // B+ tree
	bool done;
	vector<VaccinationData *> Print_vector;

public:
	Manager(int bpOrder); //b+ node map size == bpOrder
	~Manager();			  //memory free only on newly allocated avl and bp

	void run(const char *command_txt);
	bool LOAD();							  //load data in input_data file to bp tree
	bool VLOAD();							  //load data in avl to print vector
	bool ADD(char *);						  //add data to bptree
	bool SEARCH_BP(string name);			  //search data in bptree by name
	bool SEARCH_BP(string start, string end); //search data in bptree by alpabet range
	bool SEARCH_AVL(string name);			  //search data in bptree
	bool VPRINT(string type_);				  //print data in printvector with type
	bool PRINT_BP();						  //print all data in bptree
	void printErrorCode(int n);				  //print error code

	//sorting type
	static bool typeA(VaccinationData *a, VaccinationData *b);
	static bool typeB(VaccinationData *a, VaccinationData *b);

	bool duplicate(VaccinationData *);							//check it is duplicated
	int FindSpace(string);										//find white space word
	bool numofdata(string);										//check there is enough data
	bool FindDataError(string, string, string, string);			//check data is proper
	bool FindDataError(string, string, string, string, string); //check data is proper
};
