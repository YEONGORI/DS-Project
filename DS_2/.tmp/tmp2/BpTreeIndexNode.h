#ifndef _BPTREEINDEXNODE_H_
#define _BPTREEINDEXNODE_H_

#include "BpTreeNode.h"
struct compare1
{
   bool operator()(const string& a,const string& b) const
   {
      int minsize = 0;
      char a_1;
      char b_1;
      minsize = min(a.length(), b.length());
      for (int i = 0; i < minsize; i++)
      {
         a_1 = a[i];
         b_1 = b[i];


         if (a_1<b_1){
            return true;
         }
         else if (a_1==b_1){
            continue;
         }
         else{
            return false;
         }
      }
      if (a.length() < b.length()){return true;}
      else{return false;}
   }
};
class BpTreeIndexNode : public BpTreeNode{
private:
	map <string, BpTreeNode*> mapIndex;
	
public:
	BpTreeIndexNode(){}
	
	~BpTreeIndexNode() {
      
   }

	void insertIndexMap(string n, BpTreeNode* pN){
		mapIndex.insert(map<string, BpTreeNode*, compare1>::value_type(n, pN));
	}

	void deleteMap(string n){
		mapIndex.erase(n);
	}

	map <string, BpTreeNode*>* getIndexMap(){return &mapIndex;}

	virtual bool isdatanode()
	{
		return false;
	}
};

#endif