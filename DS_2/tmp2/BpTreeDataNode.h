#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_

#include "BpTreeNode.h"

struct compare
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

class BpTreeDataNode : public BpTreeNode
{
private:
	map <string, VaccinationData*> mapData;
	BpTreeNode* pNext;
	BpTreeNode* pPrev;

public:

	BpTreeDataNode(){
		pNext=NULL; pPrev=NULL;
	}
	~BpTreeDataNode(){
		
	}
	void setNext(BpTreeNode* pN){pNext = pN;}
	void setPrev(BpTreeNode* pN){pPrev = pN;}
	BpTreeNode* getNext(){return pNext;}
	BpTreeNode* getPrev(){return pPrev;}

	void insertDataMap(string n, VaccinationData* pN){
		mapData.insert(map<string, VaccinationData*, compare>::value_type(n,pN));
	}

	void deleteMap(string n){
		mapData.erase(n);
	}
	map<string, VaccinationData*> *getDataMap(){return &mapData;}

	virtual bool isdatanode()
	{
		return true;
	}
};

#endif