#include "FPGrowth.h"
#include <map>
#include <string>
#include <cstring>

FPGrowth::~FPGrowth() {
}

void FPGrowth::createFPtree(FPNode* root, HeaderTable* table, vector<vector<string> > item_array, vector<pair<int, string> > freq){
	
	for(int i=0;i<item_array.size();i++){
		FPNode* p = root;
		map<string, FPNode*> curNode = root->children;

		for(int j=0;j<item_array[i].size();j++){

			auto tmp = curNode.find(item_array[i][j]);

			if(curNode.empty()){ 
				FPNode* new_node = new FPNode;
				new_node->frequency = 1;
				new_node->parent=p;
				// curNode.insert(item_a)
				// curNode[item_array[i][j]] = new_node;
				curNode.insert(make_pair(item_array[i][j], new_node));
			}
			else{				
				if(tmp != curNode.end()){
					tmp->second->frequency++;
				}
				else{
					FPNode* new_node = new FPNode;
					new_node->frequency = 1;
					new_node->parent = p;
					curNode.insert(make_pair(item_array[i][j], new_node));
				}
			}
			p = tmp->second;
			curNode = tmp->second->children;
		}
	}
}

// void FPGrowth::createFPtree(FPNode* root, HeaderTable* table, vector<vector<string> > item_array, vector<int, string> freq){
// 	for(int i=0;i<item_array.size();i++){
// 		if (root != NULL) {

// 		}
// 		else {
// 			root->children
// 		}
// 	}
// }

void FPGrowth::connectNode(HeaderTable* table, string item, FPNode* node) {

}

bool FPGrowth::contains_single_path(FPNode* pNode) {
	if (pNode->getChildren().size() == 0) return true;
	else if (pNode->getChildren().size() > 1) return false;
	return contains_single_path(pNode->getChildren().begin()->second);
}

// map<set<string>, int> FPGrowth::getFrequentPatterns(HeaderTable* pTable, FPNode* pTree) {

// 	return;
// }



void FPGrowth::powerSet(map<set<string>, int>* FrequentPattern, vector<string> data, string item, int frequency, int* ptr, int depth) {
	if (data.size() == depth) {
		set<string> set; set.insert(item);
		for (int i = 0; i < data.size(); i++) { if (ptr[i] == 1) set.insert(data[i]); }
		FrequentPattern->insert(make_pair(set, frequency)); return;
	}
	ptr[depth] = 1;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
	ptr[depth] = 0;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
}

bool FPGrowth::printList() {

	return true;
}
bool FPGrowth::printTree() {
	return true;
}
void FPGrowth::saveFrequentPatterns(){

}
